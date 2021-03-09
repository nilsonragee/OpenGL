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
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 object_color;
uniform vec3 view_position;

void main()
{
    // ambient light
    float ambient_lighting_strength = 0.1;
    vec3 ambient_light = ambient_lighting_strength * light_color;

    // diffuse light
    vec3 normal = normalize(Normal);
    vec3 light_direction = normalize(light_position - FragPos);

    float difference = max(dot(normal, light_direction), 0.0);
    vec3 diffuse_light = difference * light_color;

    // specular highlight
    float specular_strength = 0.5;

    vec3 view_direction = normalize(view_position - FragPos);
    vec3 reflection_direction = reflect(-light_direction, normal);

    float spec = pow(max(dot(view_direction, reflection_direction), 0.0), 32);
    vec3 specular_highlight = specular_strength * spec * light_color;

    // result
    vec3 result = (ambient_light + diffuse_light + specular_highlight) * object_color;
    FragColor = vec4(result, 1.0);
}