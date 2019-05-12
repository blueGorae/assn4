#version 330 core

uniform sampler2D Texture;
in vec2 textureCoord;
in vec4 lightColor;

uniform int IsGouraudShading;
uniform int IsNoLight;

in vec3 fN;
in vec3 fL;
in vec3 fE;

uniform vec4 AmbientProduct;
uniform vec4 DiffuseProduct;
uniform vec4 SpecularProduct;
uniform mat4 ModelView;
uniform vec4 LightPosition;
uniform float Shininess;

void main()
{
	vec4 textureColor = texture(Texture, textureCoord);
	vec4 finalLightColor;
	if (IsGouraudShading == 1) {
		finalLightColor = lightColor;
	} else {
		// Normalize the input lighting vectors
		vec3 N = normalize(fN);
		vec3 E = normalize(fE);
		vec3 L = normalize(fL);

		vec3 H = normalize( L + E );
		vec4 ambient = AmbientProduct;

		float Kd = max(dot(L, N), 0.0);
		vec4 diffuse = Kd * DiffuseProduct;
		float Ks = pow(max(dot(N, H), 0.0), Shininess);
		vec4 specular = Ks * SpecularProduct;

		// discard the specular highlight if the light's behind the vertex
		if ( dot(L, N) < 0.0 )
			specular = vec4(0.0, 0.0, 0.0, 1.0);

		finalLightColor = ambient;// + diffuse + specular;
		finalLightColor.a = 1.0;
	}

	if (IsNoLight == 1) {
		gl_FragColor = textureColor;
	} else {
		gl_FragColor = finalLightColor * textureColor;
		gl_FragColor.a = 1.0;
	}
}