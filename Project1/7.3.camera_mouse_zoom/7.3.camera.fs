#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	// �ӵ�һ������Ԫ��������
    vec4 texColor1 = texture(texture1, TexCoord);
    // �ӵڶ�������Ԫ��������
    vec4 texColor2 = texture(texture2, TexCoord);
	FragColor = mix(texColor1, texColor2, 0.5);
}