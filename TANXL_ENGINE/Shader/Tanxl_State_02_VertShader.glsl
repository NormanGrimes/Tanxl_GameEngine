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

	int counts = 0;
	int CLevel = 1;

	float Line_Length_Width = 1.0f / 6.0f;
	float Line_Length_Height = 0.20f;// 1/5

	float WidthMove  = - 5 * Line_Length_Width;
	float HeightMove =   4 * Line_Length_Height;

	for(int VertexId = 0; VertexId < 31; ++VertexId)
	{
		if(VertexId == 30)
		{
			if      (gl_VertexID == 180)
			{
				Cube = Image_Id;
				gl_Position = vec4( -0.9f,  0.0f, STATE_02_LAYER, 1.0f);
			}
			else if (gl_VertexID == 181)
			{
				Cube = Image_Id;
				gl_Position = vec4(  0.9f,  0.0f, STATE_02_LAYER, 1.0f);
			}
			else if (gl_VertexID == 182)
			{
				Cube = Image_Id;
				gl_Position = vec4( -0.9f,  0.51f, STATE_02_LAYER, 1.0f);
			}
			else if (gl_VertexID == 183)
			{
				Cube = Image_Id;
				gl_Position = vec4(  0.9f,  0.0f, STATE_02_LAYER, 1.0f);
			}
			else if (gl_VertexID == 184)
			{
				Cube = Image_Id;
				gl_Position = vec4(  0.9f,  0.51f, STATE_02_LAYER, 1.0f);
			}
			else if (gl_VertexID == 185)
			{
				Cube = Image_Id;
				gl_Position = vec4( -0.9f,  0.51f, STATE_02_LAYER, 1.0f);
			}
		}
		else
		{
			Cube = 32;
			if      (gl_VertexID == VertexId * 6 + 0) 
			{
				gl_Position = vec4( -Line_Length_Width + WidthMove, -Line_Length_Height + HeightMove, STATE_02_LAYER, 1.0f);
				if(CLevel == 1)
				{
					if(mod(float(VertexId), 2.0f) == 0.0f)
						vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
					else
						vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
				}
				else
				{
					if(mod(float(VertexId), 2.0f) == 0.0f)
						vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
					else
						vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
				}
			}
			else if (gl_VertexID == VertexId * 6 + 1) 
			{
				gl_Position = vec4(  Line_Length_Width + WidthMove, -Line_Length_Height + HeightMove, STATE_02_LAYER, 1.0f);
				if(CLevel == 1)
				{
					if(mod(float(VertexId), 2.0f) == 0.0f)
						vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
					else
						vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
				}
				else
				{
					if(mod(float(VertexId), 2.0f) == 0.0f)
						vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
					else
						vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
				}
			}
			else if (gl_VertexID == VertexId * 6 + 2) 
			{
				gl_Position = vec4( -Line_Length_Width + WidthMove,  Line_Length_Height + HeightMove, STATE_02_LAYER, 1.0f);
				if(CLevel == 1)
				{
					if(mod(float(VertexId), 2.0f) == 0.0f)
						vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
					else
						vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
				}
				else
				{
					if(mod(float(VertexId), 2.0f) == 0.0f)
						vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
					else
						vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
				}
			}
			else if (gl_VertexID == VertexId * 6 + 3) 
			{
				gl_Position = vec4(  Line_Length_Width + WidthMove, -Line_Length_Height + HeightMove, STATE_02_LAYER, 1.0f);
				if(CLevel == 1)
				{
					if(mod(float(VertexId), 2.0f) == 0.0f)
						vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
					else
						vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
				}
				else
				{
					if(mod(float(VertexId), 2.0f) == 0.0f)
						vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
					else
						vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
				}
			}
			else if (gl_VertexID == VertexId * 6 + 4) 
			{
				gl_Position = vec4(  Line_Length_Width + WidthMove,  Line_Length_Height + HeightMove, STATE_02_LAYER, 1.0f);
				if(CLevel == 1)
				{
					if(mod(float(VertexId), 2.0f) == 0.0f)
						vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
					else
						vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
				}
				else
				{
					if(mod(float(VertexId), 2.0f) == 0.0f)
						vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
					else
						vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
				}
			}
			else if (gl_VertexID == VertexId * 6 + 5) 
			{
				gl_Position = vec4( -Line_Length_Width + WidthMove,  Line_Length_Height + HeightMove, STATE_02_LAYER, 1.0f);
				if(CLevel == 1)
				{
					if(mod(float(VertexId), 2.0f) == 0.0f)
						vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
					else
						vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
				}
				else
				{
					if(mod(float(VertexId), 2.0f) == 0.0f)
						vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
					else
						vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
				}
			}

			WidthMove += Line_Length_Width * 2;
			counts++;
			if(counts == 6)
			{
				if(CLevel == 1)
					CLevel = 0;
				else
					CLevel = 1;

				counts = 0;
				WidthMove = -5 * Line_Length_Width;
				HeightMove -= 2 * Line_Length_Height;
			}
		}
	}
}