#version 330 core

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexture;

uniform bool IsGouraudShading;

// Gouraud Shading
out vec4 lightColor;

// Phong Shading
// output values that will be interpolated per-fragment
out vec3 fN;
out vec3 fE;
out vec3 fL;

uniform vec4 AmbientProduct;
uniform vec4 DiffuseProduct;
uniform vec4 SpecularProduct;
uniform mat4 Projection;
uniform mat4 ModelView;
uniform vec4 LightPosition;
uniform float Shininess;

out vec2 textureCoord;

void main()
{
    vec4 v4Position = vec4(vPosition, 1.f);
    if (IsGouraudShading) {
        // Transform vertex position into eye coordinates
        vec3 pos = (ModelView * v4Position).xyz;
        vec3 L = normalize( LightPosition.xyz - pos );
        vec3 E = normalize( -pos );
        vec3 H = normalize( L + E );

        // Transform vertex normal into eye coordinates
        vec3 N = normalize( ModelView * vec4(vNormal, 0.0) ).xyz;

        // Compute the terms in the illumination equation
        vec4 ambient = AmbientProduct;
        float Kd = max( dot(L, N), 0.0 );
        vec4 diffuse = Kd * DiffuseProduct;
        float Ks = pow( max(dot(N, H), 0.0), Shininess );
        vec4 specular = Ks * SpecularProduct;
        if ( dot(L, N) < 0.0 )
            specular = vec4(0.0, 0.0, 0.0, 1.0);
        lightColor = ambient + diffuse + specular;
        lightColor.a = 1.0;
    } else {
        fN = vNormal;
        fE = vPosition.xyz;
        fL = LightPosition.xyz;
        if ( LightPosition.w != 0.0 ) {
            fL = LightPosition.xyz - vPosition.xyz;
        }
		lightColor = vec4(1.0);
    }
    gl_Position = Projection * ModelView * v4Position;
	textureCoord = vTexture;
}
