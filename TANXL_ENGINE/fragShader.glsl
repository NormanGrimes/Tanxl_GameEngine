//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-01-16 10:30
// 纹理功能已调试完成并实装
// 更新多纹理支持（最高十个纹理）
// 支持的纹理数量提升到上限值
// 增加指定主移动方块的纹理
// 调用新增的两个纹理


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
layout (binding = 10) uniform sampler2D Samp_10;
layout (binding = 11) uniform sampler2D Samp_11;
layout (binding = 12) uniform sampler2D Samp_12;
layout (binding = 13) uniform sampler2D Samp_13;
layout (binding = 14) uniform sampler2D Samp_14;
layout (binding = 15) uniform sampler2D Samp_15;
layout (binding = 16) uniform sampler2D Samp_16;
layout (binding = 17) uniform sampler2D Samp_17;
layout (binding = 18) uniform sampler2D Samp_18;
layout (binding = 19) uniform sampler2D Samp_19;
layout (binding = 20) uniform sampler2D Samp_20;
layout (binding = 21) uniform sampler2D Samp_21;
layout (binding = 22) uniform sampler2D Samp_22;
layout (binding = 23) uniform sampler2D Samp_23;
layout (binding = 24) uniform sampler2D Samp_24;
layout (binding = 25) uniform sampler2D Samp_25;
layout (binding = 26) uniform sampler2D Samp_26;
layout (binding = 27) uniform sampler2D Samp_27;
layout (binding = 28) uniform sampler2D Samp_28;
layout (binding = 29) uniform sampler2D Samp_29;
layout (binding = 30) uniform sampler2D Samp_30;
layout (binding = 31) uniform sampler2D Samp_31;

void main(void)
{	
	if	    (Cube == 1)
		color = texture(Samp_00, tc);
	else if (Cube == 2)
		color = texture(Samp_01, tc);
	else if (Cube == 3)
		color = texture(Samp_02, tc);
	else if (Cube == 0)
		color = texture(Samp_03, tc);
	else if (Cube == 4)
		color = texture(Samp_06, tc);
	else if (Cube == 5)
		color = texture(Samp_07, tc);

	else if (Cube == -1)
		color = texture(Samp_05, tc);
	else
		color = vs_color;
}
