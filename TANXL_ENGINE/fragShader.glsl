//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-01-16 10:30
// 纹理功能已调试完成并实装

#version 430

in vec4 vs_color;
in vec2 tc;
out vec4 color;

flat in int Cube;

layout (binding = 0) uniform sampler2D samp;

void main(void)
{	
	if(Cube != -1)
		color = texture(samp, tc);
	else
		color = vs_color;
}
