#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	// 从第一个纹理单元采样纹理
    vec4 texColor1 = texture(texture1, TexCoord);
    // 从第二个纹理单元采样纹理
    vec4 texColor2 = texture(texture2, TexCoord);
	FragColor = mix(texColor1, texColor2, 0.5);
}