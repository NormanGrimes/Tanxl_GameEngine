//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-09-22 16:29
// Ϊ������ɫͳһ����ָ����ʼλ��

#version 430

layout (location = 0) uniform vec3 textColor;
uniform sampler2D text;

in vec2 TexCoords;
out vec4 color;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = vec4(textColor, 1.0) * sampled;
}