//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-01-16 10:30
// 纹理功能已调试完成并实装
// 更新多纹理支持（最高十个纹理）
// 支持的纹理数量提升到上限值
// 增加指定主移动方块的纹理
// 调用新增的两个纹理
// 变量名称调整
// 整理输入纹理顺序
// 完整支持所有编号的纹理

#version 430

in vec4 vs_color;
in vec2 tc;
out vec4 color;

flat in int Cube;

layout (binding = 0) uniform sampler2D Tex_00;
layout (binding = 1) uniform sampler2D Tex_01;
layout (binding = 2) uniform sampler2D Tex_02;
layout (binding = 3) uniform sampler2D Tex_03;
layout (binding = 4) uniform sampler2D Tex_04;
layout (binding = 5) uniform sampler2D Tex_05;
layout (binding = 6) uniform sampler2D Tex_06;
layout (binding = 7) uniform sampler2D Tex_07;
layout (binding = 8) uniform sampler2D Tex_08;
layout (binding = 9) uniform sampler2D Tex_09;
layout (binding = 10) uniform sampler2D Tex_10;
layout (binding = 11) uniform sampler2D Tex_11;
layout (binding = 12) uniform sampler2D Tex_12;
layout (binding = 13) uniform sampler2D Tex_13;
layout (binding = 14) uniform sampler2D Tex_14;
layout (binding = 15) uniform sampler2D Tex_15;
layout (binding = 16) uniform sampler2D Tex_16;
layout (binding = 17) uniform sampler2D Tex_17;
layout (binding = 18) uniform sampler2D Tex_18;
layout (binding = 19) uniform sampler2D Tex_19;
layout (binding = 20) uniform sampler2D Tex_20;
layout (binding = 21) uniform sampler2D Tex_21;
layout (binding = 22) uniform sampler2D Tex_22;
layout (binding = 23) uniform sampler2D Tex_23;
layout (binding = 24) uniform sampler2D Tex_24;
layout (binding = 25) uniform sampler2D Tex_25;
layout (binding = 26) uniform sampler2D Tex_26;
layout (binding = 27) uniform sampler2D Tex_27;
layout (binding = 28) uniform sampler2D Tex_28;
layout (binding = 29) uniform sampler2D Tex_29;
layout (binding = 30) uniform sampler2D Tex_30;
layout (binding = 31) uniform sampler2D Tex_31;

void main(void)
{	
	switch(Cube)
	{
	case 0:
		color = texture(Tex_00, tc);
		break;
	case 1:
		color = texture(Tex_01, tc);
		break;
	case 2:
		color = texture(Tex_02, tc);
		break;
	case 3:
		color = texture(Tex_03, tc);
		break;
	case 4:
		color = texture(Tex_04, tc);
		break;
	case 5:
		color = texture(Tex_05, tc);
		break;
	case 6:
		color = texture(Tex_06, tc);
		break;
	case 7:
		color = texture(Tex_07, tc);
		break;
	case 8:
		color = texture(Tex_08, tc);
		break;
	case 9:
		color = texture(Tex_09, tc);
		break;
	case 10:
		color = texture(Tex_10, tc);
		break;
	case 11:
		color = texture(Tex_11, tc);
		break;
	case 12:
		color = texture(Tex_12, tc);
		break;
	case 13:
		color = texture(Tex_13, tc);
		break;
	case 14:
		color = texture(Tex_14, tc);
		break;
	case 15:
		color = texture(Tex_15, tc);
		break;
	case 16:
		color = texture(Tex_16, tc);
		break;
	case 17:
		color = texture(Tex_17, tc);
		break;
	case 18:
		color = texture(Tex_18, tc);
		break;
	case 19:
		color = texture(Tex_19, tc);
		break;
	case 20:
		color = texture(Tex_20, tc);
		break;
	case 21:
		color = texture(Tex_21, tc);
		break;
	case 22:
		color = texture(Tex_22, tc);
		break;
	case 23:
		color = texture(Tex_23, tc);
		break;
	case 24:
		color = texture(Tex_24, tc);
		break;
	case 25:
		color = texture(Tex_25, tc);
		break;
	case 26:
		color = texture(Tex_26, tc);
		break;
	case 27:
		color = texture(Tex_27, tc);
		break;
	case 28:
		color = texture(Tex_28, tc);
		break;
	case 29:
		color = texture(Tex_29, tc);
		break;
	case 30:
		color = texture(Tex_30, tc);
		break;
	case 31:
		color = texture(Tex_31, tc);
		break;
	default:
		color = vs_color;
		break;
	}
}
