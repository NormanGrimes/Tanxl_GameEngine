//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-01-16 10:30
// 纹理功能已调试完成并实装
// 更新多纹理支持（最高十个纹理）

#version 430

in vec4 vs_color;
in vec2 tc;
out vec4 color;

flat in int Cube;

layout (binding = 0) uniform sampler2D Samp_00;
layout (binding = 1) uniform sampler2D Samp_01;
layout (binding = 2) uniform sampler2D Samp_02;
layout (binding = 3) uniform sampler2D Samp_03;
layout (binding = 4) uniform sampler2D Samp_04;
layout (binding = 5) uniform sampler2D Samp_05;
layout (binding = 6) uniform sampler2D Samp_06;
layout (binding = 7) uniform sampler2D Samp_07;
layout (binding = 8) uniform sampler2D Samp_08;
layout (binding = 9) uniform sampler2D Samp_09;

void main(void)
{	
	if(Cube == 1)
		color = texture(Samp_00, tc);
	else if(Cube == 2)
		color = texture(Samp_01, tc);
	else if(Cube == 3)
		color = texture(Samp_02, tc);
	else if(Cube == 0)
		color = texture(Samp_03, tc);
	else
		color = texture(Samp_04, tc);
	//color = vs_color;
}
