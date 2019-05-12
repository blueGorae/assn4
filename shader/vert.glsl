#version 330 core

#define DIRECTIONAL_LIGHTS 1
#define POINT_LIGHTS 1

layout (location = 0)in vec3 vPosition;
layout (location = 1)in vec2 vTexture;
layout (location = 2)in vec3 vNormal;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform bool IsGouraudShading;

// Gouraud Shading
out vec4 lightColor;

// Phong Shading
// output values that will be interpolated per-fragment
out vec3 fN[DIRECTIONAL_LIGHTS];
out vec3 fE[DIRECTIONAL_LIGHTS];
out vec3 fL[DIRECTIONAL_LIGHTS];
out vec3 pfN[POINT_LIGHTS];
out vec3 pfE[POINT_LIGHTS];
out vec3 pfL[POINT_LIGHTS];
out float pAttenuation[POINT_LIGHTS];

uniform vec4 AmbientProduct[DIRECTIONAL_LIGHTS];
uniform vec4 DiffuseProduct[DIRECTIONAL_LIGHTS];
uniform vec4 SpecularProduct[DIRECTIONAL_LIGHTS];
uniform vec4 LightPosition[DIRECTIONAL_LIGHTS];
uniform float Shininess[DIRECTIONAL_LIGHTS];

uniform vec4 pAmbientProduct[POINT_LIGHTS];
uniform vec4 pDiffuseProduct[POINT_LIGHTS];
uniform vec4 pSpecularProduct[POINT_LIGHTS];
uniform vec4 pLightPosition[POINT_LIGHTS];
uniform float pShininess[POINT_LIGHTS];

out vec2 textureCoord;

void main()
{
    vec4 v4Position = vec4(vPosition, 1.0);
	mat4 ModelView = View * Model;
	vec3 pos = (ModelView * v4Position).xyz;
    lightColor = vec4(0.0);
    if (IsGouraudShading) {
        // Transform vertex position into eye coordinates
        for (int i = 0; i < DIRECTIONAL_LIGHTS; i++) {
            vec3 L = normalize( LightPosition[i].xyz - pos );
            vec3 E = normalize( -pos );
            vec3 H = normalize( L + E );

            // Transform vertex normal into eye coordinates
            vec3 N = normalize( ModelView * vec4(vNormal, 0.0) ).xyz;

            // Compute the terms in the illumination equation
            vec4 ambient = AmbientProduct[i];
            float Kd = max( dot(L, N), 0.0 );
            vec4 diffuse = Kd * DiffuseProduct[i];
            float Ks = pow( max(dot(N, H), 0.0), Shininess[i] );
            vec4 specular = Ks * SpecularProduct[i];
            if ( dot(L, N) < 0.0 )
                specular = vec4(0.0, 0.0, 0.0, 1.0);
            lightColor += ambient + diffuse + specular;
        }

        for (int i = 0; i < POINT_LIGHTS; i++) {
            vec3 toLight = pLightPosition[i].xyz - pos;
            float d = length(toLight);
            vec3 L = normalize( toLight );
            vec3 E = normalize( -pos );
            vec3 H = normalize( L + E );

            // Transform vertex normal into eye coordinates
            vec3 N = normalize( ModelView * vec4(vNormal, 0.0) ).xyz;

            // Compute the terms in the illumination equation
            vec4 ambient = pAmbientProduct[i];
            float Kd = max( dot(L, N), 0.0 );
            vec4 diffuse = Kd * pDiffuseProduct[i];
            float Ks = pow( max(dot(N, H), 0.0), pShininess[i] );
            vec4 specular = Ks * pSpecularProduct[i];
            if ( dot(L, N) < 0.0 )
                specular = vec4(0.0, 0.0, 0.0, 1.0);

            float attenuation = min(2 / d, 1.0);

            lightColor += attenuation * (ambient + diffuse + specular);
        }
        lightColor.a = 1.0;
    } else {
        for (int i = 0; i < DIRECTIONAL_LIGHTS; i++) {
            fN[i] = vNormal;
            fE[i] = vPosition.xyz;
            fL[i] = LightPosition[i].xyz;
            if ( LightPosition[i].w != 0.0 ) {
                fL[i] = LightPosition[i].xyz - vPosition.xyz;
            }
        }

        for (int i = 0; i < POINT_LIGHTS; i++) {
            pfN[i] = vNormal;
            pfE[i] = vPosition.xyz;
            pfL[i] = pLightPosition[i].xyz;
            if ( pLightPosition[i].w != 0.0 ) {
                pfL[i] = pLightPosition[i].xyz - vPosition.xyz;
            }
            vec3 toLight = pLightPosition[i].xyz - pos;
            float d = length(toLight);
            pAttenuation[i] = min(2 / d, 1.0);
        }

        lightColor = vec4(1.0);
    }
    gl_Position = Projection * ModelView * v4Position;
	textureCoord = vTexture;
}
