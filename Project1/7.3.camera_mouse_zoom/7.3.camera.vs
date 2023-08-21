#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPos; // ÐÂÔö cameraPos uniform

void main()
{
    vec3 toCamera = normalize(cameraPos - aPos);
    vec3 right = normalize(cross(vec3(0.0, 1.0, 0.0), toCamera));
    vec3 up = cross(toCamera, right);

    mat3 billboardMatrix = mat3(right, up, toCamera);

    vec3 rotatedPos = billboardMatrix * aPos;
    gl_Position = projection * view * model * vec4(rotatedPos, 1.0f);

    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}


