//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-07-12 14:55
// 修复起始页面存在一像素偏差的问题
// 纹理编号改为自动获取
// 增加游戏状态统一变量
// 增加下方的游戏状态栏
// 通过游戏状态控制绘制内容

#version 430

#define STATE_02_LAYER 0.2f //UI LAYER

layout (location = 1) in vec2 texCoord;
layout (location = 2) uniform int Image_Id;
layout (location = 3) uniform int Game_Status;

out vec4 vs_color;
out vec2 tc;
flat out int Cube;

void main(void)
{
	tc = texCoord;

	Cube = Image_Id;

	for(int VertexId = 0; VertexId < 1; ++VertexId)
	{
		if      (gl_VertexID == (VertexId * 6 + 0))
		{
			if((Game_Status != 0) && (Game_Status != 3))
			{
				Cube = -1;
				gl_Position = vec4( -1.0f, -1.0f, STATE_02_LAYER, 1.0f);
			}
			else
				gl_Position = vec4( -1.01f, -1.01f, STATE_02_LAYER, 1.0f);
		}
		else if (gl_VertexID == (VertexId * 6 + 1))
		{
			if((Game_Status != 0) && (Game_Status != 3))
			{
				Cube = -1;
				gl_Position = vec4(  1.0f, -1.0f, STATE_02_LAYER, 1.0f);
			}
			else
				gl_Position = vec4(  1.01f, -1.01f, STATE_02_LAYER, 1.0f);
		}
		else if (gl_VertexID == (VertexId * 6 + 2))
		{
			if((Game_Status != 0) && (Game_Status != 3))
			{
				Cube = -1;
				gl_Position = vec4( -1.0f, -0.6f, STATE_02_LAYER, 1.0f);
			}
			else
				gl_Position = vec4( -1.01f,  1.01f, STATE_02_LAYER, 1.0f);
		}
		else if (gl_VertexID == (VertexId * 6 + 3))
		{
			if((Game_Status != 0) && (Game_Status != 3))
			{
				Cube = -1;
				gl_Position = vec4(  1.0f, -1.0f, STATE_02_LAYER, 1.0f);
			}
			else
				gl_Position = vec4(  1.01f, -1.01f, STATE_02_LAYER, 1.0f); 
		}
		else if (gl_VertexID == (VertexId * 6 + 4))
		{
			if((Game_Status != 0) && (Game_Status != 3))
			{
				Cube = -1;
				gl_Position = vec4(  1.0f, -0.6f, STATE_02_LAYER, 1.0f);
			}
			else
				gl_Position = vec4(  1.01f,  1.01f, STATE_02_LAYER, 1.0f);
		}
		else if (gl_VertexID == (VertexId * 6 + 5))
		{
			if((Game_Status != 0) && (Game_Status != 3))
			{
				Cube = -1;
				gl_Position = vec4( -1.0f, -0.6f, STATE_02_LAYER, 1.0f);
			}
			else
				gl_Position = vec4( -1.01f,  1.01f, STATE_02_LAYER, 1.0f);
		}
	}
}