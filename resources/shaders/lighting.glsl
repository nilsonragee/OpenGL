#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    // Do this on CPU !!!
    Normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = projection * view * model * vec4(FragPos, 1.0);
}

#shader fragment
#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 view_position;
uniform Material material;
uniform Light light;

void main()
{
    // ambient light
    vec3 ambient_light = light.ambient * material.ambient;

    // diffuse light
    vec3 normal = normalize(Normal);
    vec3 light_direction = normalize(light.position - FragPos);

    float diffuse = max(dot(normal, light_direction), 0.0);
    vec3 diffuse_light = light.diffuse * (diffuse * material.diffuse);

    // specular highlight
    vec3 view_direction = normalize(view_position - FragPos);
    vec3 reflection_direction = reflect(-light_direction, normal);

    float specular = pow(max(dot(view_direction, reflection_direction), 0.0), material.shininess);
    vec3 specular_highlight = light.specular * (specular * material.specular);

    // result
    vec3 result = ambient_light + diffuse_light + specular_highlight;
    FragColor = vec4(result, 1.0);
}