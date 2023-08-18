#version 330 core

in vec4 FragPos;
in vec4 ShadowCoord;

out vec4 FragColor;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // Perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    
    // Get closest depth value from the shadow map
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    
    // Current depth from light's perspective
    float currentDepth = projCoords.z;
    
    // Calculate bias to reduce shadow acne
    float bias = max(0.05 * (1.0 - dot(normalize(normal), normalize(lightPos - FragPos.xyz))), 0.005);
    
    // Check whether the fragment is in shadow
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
    
    return shadow;
}

void main()
{
    vec3 normal = normalize(inNormal);
    vec3 lightDir = normalize(lightPos - FragPos.xyz);
    vec3 viewDir = normalize(viewPos - FragPos.xyz);
    vec3 reflectDir = reflect(-lightDir, normal);

    // Ambient
    vec3 ambient = 0.2 * texture(diffuseTexture, FragPos.xy).rgb;

    // Diffuse
    vec3 diffuse = max(dot(normal, lightDir), 0.0) * texture(diffuseTexture, FragPos.xy).rgb;

    // Specular
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = vec3(0.4) * spec;

    // Calculate shadow factor
    float shadow = ShadowCalculation(ShadowCoord);
    
    // Apply shadow
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));
    
    FragColor = vec4(lighting, 1.0);
}
