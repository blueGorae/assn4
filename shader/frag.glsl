#version 330 core

#define DIRECTIONAL_LIGHTS 1
#define POINT_LIGHTS 1

uniform sampler2D Texture;
in vec2 textureCoord;
in vec4 lightColor;

uniform bool IsGouraudShading;
uniform bool IsNoLight;

in vec3 fN[DIRRECTIONAL_LIGHTS];
in vec3 fE[DIRRECTIONAL_LIGHTS];
in vec3 fL[DIRRECTIONAL_LIGHTS];
in vec3 pfN[POINT_LIGHTS];
in vec3 pfE[POINT_LIGHTS];
in vec3 pfL[POINT_LIGHTS];
in float pAttenuation[POINT_LIGHT];

uniform vec4 AmbientProduct[DIRRECTIONAL_LIGHTS];
uniform vec4 DiffuseProduct[DIRRECTIONAL_LIGHTS];
uniform vec4 SpecularProduct[DIRRECTIONAL_LIGHTS];
uniform float Shininess[DIRRECTIONAL_LIGHTS];

uniform vec4 pAmbientProduct[POINT_LIGHTS];
uniform vec4 pDiffuseProduct[POINT_LIGHTS];
uniform vec4 pSpecularProduct[POINT_LIGHTS];
uniform float pShininess[POINT_LIGHTS];

void main()
{
	vec4 textureColor = texture(Texture, textureCoord);
	vec4 finalLightColor = vec4(0.0);
	if (IsGouraudShading) {
		finalLightColor = lightColor;
	} else {
		for (int i = 0; i < DIRECTIONAL_LIGHTS; i++) {
			// Normalize the input lighting vectors
			vec3 N = normalize(fN[i]);
			vec3 E = normalize(fE[i]);
			vec3 L = normalize(fL[i]);

			vec3 H = normalize( L + E );
			vec4 ambient = AmbientProduct[i];

			float Kd = max(dot(L, N), 0.0);
			vec4 diffuse = Kd * DiffuseProduct[i];
			float Ks = pow(max(dot(N, H), 0.0), Shininess[i]);
			vec4 specular = Ks * SpecularProduct[i];

			// discard the specular highlight if the light's behind the vertex
			if ( dot(L, N) < 0.0 )
				specular = vec4(0.0, 0.0, 0.0, 1.0);
			finalLightColor += ambient + diffuse + specular;
		}

		for (int i = 0; i < DIRECTIONAL_LIGHTS; i++) {
			// Normalize the input lighting vectors
			vec3 N = normalize(pfN[i]);
			vec3 E = normalize(pfE[i]);
			vec3 L = normalize(pfL[i]);

			vec3 H = normalize( L + E );
			vec4 ambient = pAmbientProduct[i];

			float Kd = max(dot(L, N), 0.0);
			vec4 diffuse = Kd * pDiffuseProduct[i];
			float Ks = pow(max(dot(N, H), 0.0), pShininess[i]);
			vec4 specular = Ks * pSpecularProduct[i];

			// discard the specular highlight if the light's behind the vertex
			if ( dot(L, N) < 0.0 )
				specular = vec4(0.0, 0.0, 0.0, 1.0);
			finalLightColor += pAttenuation[i] * (ambient + diffuse + specular);
		}
		finalLightColor.a = 1.0;
	}

	if (IsNoLight) {
		gl_FragColor = textureColor;
	} else {
		gl_FragColor = finalLightColor * textureColor;
		gl_FragColor.a = 1.0;
	}
}