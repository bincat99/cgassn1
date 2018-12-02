#version 330
 
layout (std140) uniform Material {
    vec4 diffuse;
    vec4 ambient;
    vec4 specular;
    vec4 emissive;
    float shininess;
    int texCount;
};


 
uniform sampler2D texUnit;
 
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;


uniform vec3 viewPos;

uniform vec3 light_position;

out vec4 FragColor;
 

void main()
{
	// light coefficient
	float light_ambient = 0.2f;
	float light_diffuse = 0.5f;
	float light_specular = 1.0f;
	float light_constant = 1.0f;
	float light_linear = 0.007f;
	float light_quadratic = 0.0002f;


    vec4 color;
    vec4 amb;
	vec4 spec;
	vec4 diff;

    float intensity;
    vec3 lightDir;
    vec3 n;
	
	// diffuse
    lightDir = normalize(vec3(1.0,1.0,1.0));
    n = normalize(Normal);
    intensity = max(dot(lightDir,n),0.0);

    if (texCount == 0) {
        color = diffuse;
        amb = ambient;
		spec = specular;
    }
    else {
        color = texture2D(texUnit, TexCoord);
        amb = color * 0.33;
		// specular
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, n);  
		float specc = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
		spec = 0.5*specc * color;  
    }


	float distance = length(light_position - FragPos);
	float attenuation = 1.0 / (light_constant + light_linear * distance + light_quadratic * (distance * distance));
	
	
	diff = 1.0 * color * intensity;
 

	FragColor = (amb + diff +spec);

}