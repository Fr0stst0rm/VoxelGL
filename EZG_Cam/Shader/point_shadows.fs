#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
	vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D normalMap;
uniform samplerCube depthMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float far_plane;
uniform bool shadows;

uniform bool reverse_normals;

uniform vec3 lightColor;
uniform float bumpiness;

// array of offset direction for sampling
vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float ShadowCalculation(vec3 fragPos)
{
    // get vector between fragment position and light position
    vec3 fragToLight = fragPos - lightPos;

    float currentDepth = length(fragToLight);
    
    float shadow = 0.0;
    float bias = 0.15;
    int samples = 20;
    float viewDistance = length(viewPos - fragPos);
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
    for(int i = 0; i < samples; ++i)
    {
        float closestDepth = texture(depthMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= far_plane;   // undo mapping [0;1]
        if(currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);
        
    // display closestDepth as debug (to visualize depth cubemap)
    // FragColor = vec4(vec3(closestDepth / far_plane), 1.0);    
        
    return shadow;
}
void main()
{   
	//Normals
	 // obtain normal from normal map in range [0,1]
	vec3 normal = vec3(0);

	if(reverse_normals) // for the sky box
		//TODO
		//normal = transpose(texture(normalMap, fs_in.TexCoords).rgb) * (-1.0 * aNormal);
		normal = texture(normalMap, fs_in.TexCoords).rgb;
    else
		normal = texture(normalMap, fs_in.TexCoords).rgb;
		    
    // transform normal vector to range [-1,1]
    normal = normalize(normal * 2.0 - 1.0) * bumpiness;  // this normal is in tangent space
	
	// Ambient
    vec3 ambient = lightColor * 0.3;//vec3(texture(material.diffuse, fs_in.TexCoords));

    // Diffuse
	vec3 lightDir = normalize(lightPos - fs_in.FragPos);
	//vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = lightColor * diff * vec3(texture(diffuseTexture, fs_in.TexCoords));
	
    
	float mat_shininess = 20.0;

	// Specular
	vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    //vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat_shininess);
    //vec3 halfwayDir = normalize(lightDir + viewDir);  
    //float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 specular = lightColor * spec;  // * vec3(texture(material.specular, fs_in.TexCoords));

	// calculate shadow
    float shadow = shadows ? ShadowCalculation(fs_in.FragPos) : 0.0;
	
	float light_constant = 1.0;
    float light_linear = 0.09;
    float light_quadratic = 0.032;

	// Attenuation
    //float distance    = length(lightPos - fs_in.FragPos);
    //float attenuation = 1.0f / (light_constant + light_linear * distance + light_quadratic * (distance * distance));
    
    //ambient  *= attenuation;
    //diffuse  *= attenuation;
    //specular *= attenuation;
     

	FragColor = vec4((ambient + (1.0 - shadow) * (diffuse + specular)) * vec3(texture(diffuseTexture, fs_in.TexCoords)), 1.0);
}