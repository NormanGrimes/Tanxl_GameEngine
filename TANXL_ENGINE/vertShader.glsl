//_VERSION_0_2_ UPDATE LOG
// LAST_UPDATE 2022-05-09 00:04
// 文件名称简化
// 方块颜色调整
// 深度（Z）调整

#version 430

layout (location=0) in vec3 position;
layout (location=1) in vec4 color;

out vec4 vs_color;

uniform int State[100];

uniform float MoveX;
uniform float MoveY;

uniform float SHeight;
uniform float SWidth;

void main(void)
{ 
	float Height = 2.0f / SHeight;
	float Width  = 2.0f / SWidth;

//	float Height = 0.2f;  //用于单一方块移动测试 调整方块宽高
//	float Width  = 0.2f;

	int counts = 0;

	float WidthMove = -((SWidth-1) / 2) * Width;
	float HeightMove = ((SHeight-1) / 2) * Height;
	for(int i = 1; i < SHeight * SWidth; i++)
	{

		if      (gl_VertexID == i * 6 + 0) 
		{ gl_Position = vec4(  Width / 2 + WidthMove, -Height / 2 + HeightMove, 0.2, 1.0); vs_color = vec4(1.0, 0.8, 0, 1);}
		else if (gl_VertexID == i * 6 + 1) 
		{ gl_Position = vec4( -Width / 2 + WidthMove, -Height / 2 + HeightMove, 0.2, 1.0); vs_color = vec4(1.0, 1.0, 0, 1);}
		else if (gl_VertexID == i * 6 + 2) 
		{ gl_Position = vec4(  Width / 2 + WidthMove,  Height / 2 + HeightMove, 0.2, 1.0); vs_color = vec4(1.0, 1, 0, 1);}
		else if (gl_VertexID == i * 6 + 3) 
		{ gl_Position = vec4( -Width / 2 + WidthMove, -Height / 2 + HeightMove, 0.2, 1.0); vs_color = vec4(1.0, 1, 0, 1);}
		else if (gl_VertexID == i * 6 + 4) 
		{ gl_Position = vec4( -Width / 2 + WidthMove,  Height / 2 + HeightMove, 0.2, 1.0); vs_color = vec4(1.0, 1, 0, 1);}
		else if (gl_VertexID == i * 6 + 5) 
		{ gl_Position = vec4(  Width / 2 + WidthMove,  Height / 2 + HeightMove, 0.2, 1.0); vs_color = vec4(1.0, 1, 0, 1);}

		WidthMove += Width;
		counts++;
		if(counts == SWidth)
		{
			counts = 0;
			WidthMove = -((SWidth-1) / 2) * Width;
			HeightMove -= Height;
		}
	}

	if      (gl_VertexID == 0) 
	{ gl_Position = vec4(  Width / 2 + MoveX, -Height / 2 + MoveY, 0.1, 1.0); vs_color = vec4(1.0, 0.8, 0.0, 1.0);}
	else if (gl_VertexID == 1) 
	{ gl_Position = vec4( -Width / 2 + MoveX, -Height / 2 + MoveY, 0.1, 1.0); vs_color = vec4(1.0, 1.0, 0.0, 1.0);}
	else if (gl_VertexID == 2) 
	{ gl_Position = vec4(  Width / 2 + MoveX,  Height / 2 + MoveY, 0.1, 1.0); vs_color = vec4(1.0, 1.0, 0.0, 1.0);}
	else if (gl_VertexID == 3) 
	{ gl_Position = vec4( -Width / 2 + MoveX, -Height / 2 + MoveY, 0.1, 1.0); vs_color = vec4(1.0, 1.0, 0.0, 1.0);}
	else if (gl_VertexID == 4) 
	{ gl_Position = vec4( -Width / 2 + MoveX,  Height / 2 + MoveY, 0.1, 1.0); vs_color = vec4(1.0, 1.0, 0.0, 1.0);}
	else if (gl_VertexID == 5) 
	{ gl_Position = vec4(  Width / 2 + MoveX,  Height / 2 + MoveY, 0.1, 1.0); vs_color = vec4(1.0, 1.0, 0.0, 1.0);}
}