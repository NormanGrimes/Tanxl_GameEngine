//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-07-12 14:55
// 修复起始页面存在一像素偏差的问题
// 纹理编号改为自动获取
// 增加游戏状态统一变量
// 增加下方的游戏状态栏
// 通过游戏状态控制绘制内容
// 使用无背景纹理替换之前带预渲染的背景
// 增加初始界面背景的绘制
// 去掉游戏信息界面绘制部分
// 移动初始界面背景绘制部分到实例化着色器

#version 430

#define STATE_02_LAYER 0.2f //UI LAYER

layout (location = 1) in vec2 texCoord;
layout (location = 2) uniform int Image_Id;

out vec4 vs_color;
out vec2 tc;
flat out int Cube;

void main(void)
{
	tc = texCoord;

	for(int VertexId = 0; VertexId < 1; ++VertexId)
	{
		if      (gl_VertexID == 0)
		{
			Cube = Image_Id;
			gl_Position = vec4( -0.9f,  0.0f, STATE_02_LAYER, 1.0f);
		}
		else if (gl_VertexID == 1)
		{
			Cube = Image_Id;
			gl_Position = vec4(  0.9f,  0.0f, STATE_02_LAYER, 1.0f);
		}
		else if (gl_VertexID == 2)
		{
			Cube = Image_Id;
			gl_Position = vec4( -0.9f,  0.51f, STATE_02_LAYER, 1.0f);
		}
		else if (gl_VertexID == 3)
		{
			Cube = Image_Id;
			gl_Position = vec4(  0.9f,  0.0f, STATE_02_LAYER, 1.0f);
		}
		else if (gl_VertexID == 4)
		{
			Cube = Image_Id;
			gl_Position = vec4(  0.9f,  0.51f, STATE_02_LAYER, 1.0f);
		}
		else if (gl_VertexID == 5)
		{
			Cube = Image_Id;
			gl_Position = vec4( -0.9f,  0.51f, STATE_02_LAYER, 1.0f);
		}
	}
}