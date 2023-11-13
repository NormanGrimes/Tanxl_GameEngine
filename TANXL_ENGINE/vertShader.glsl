//_VERSION_0_7_ UPDATE LOG
// LAST_UPDATE 2023-01-16 17:41
// 纹理功能已调试完成并实装
// 修复Cube不能正确传入片段着色器的问题
// 移除未使用变量并重新排序
// 新增游戏界面显示层
// 增加变量保存计算后的方块值
// 地图其他绘制方块移动到地图绘制之后

#version 430

layout (location = 1) in vec2 texCoord;

layout (location = 2) uniform float Current_Move_LocationX;
layout (location = 3) uniform float Current_Move_LocationY;

layout (location = 4) uniform int SHeight;
layout (location = 5) uniform int SWidth;

layout (location = 6) uniform float StateMoveX;
layout (location = 7) uniform float StateMoveY;

layout (location = 8) uniform int PreLoads;

in vec3 position;
in vec4 color;

uniform int State[300];

out vec4 vs_color;
out vec2 tc;
flat out int Cube;

void main(void)
{
	tc = texCoord;
	
	float Height = 2.0f / SHeight;
	float Width  = 2.0f / SWidth;

	int counts = 0;
	int VertexId = 0;
	int State_Datas = (SHeight + PreLoads) * (SWidth + PreLoads) + 1;

	float WidthMove = -((SWidth + PreLoads - 1) / 2) * Width;
	float HeightMove = ((SHeight + PreLoads - 1) / 2) * Height;

	for(VertexId = 0; VertexId < State_Datas; ++VertexId)//MAP LAYER 0.3F
	{
		if      (gl_VertexID == VertexId * 6 + 0) 
		{ 
			gl_Position = vec4(  Width / 2 + WidthMove + StateMoveX, 
							    -Height / 2 + HeightMove + StateMoveY, 0.3f, 1.0f);
			if(State[VertexId] == 0)
			{
				vs_color = vec4(1.0f, 0.8f, 0.1f, 1.0f);
				Cube = 1;
			}
			else if(State[VertexId] == 1)
			{
				vs_color = vec4(0.1f, 0.8f, 1.0f, 1.0f);
				Cube = 2;
			}
			else if(State[VertexId] == 2)
			{
				vs_color = vec4(1.0f, 0.8f, 0.4f, 1.0f);
				Cube = 3;
			}
			else
			{
				vs_color = vec4(0.9f, 0.7f, 0.9f, 1.0f);
				Cube = 0;
			}
		}
		else if (gl_VertexID == VertexId * 6 + 1) 
		{ 
			gl_Position = vec4( -Width / 2 + WidthMove + StateMoveX,
			                    -Height / 2 + HeightMove + StateMoveY, 0.3f, 1.0f); 
			if(State[VertexId] == 0)
			{
				vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
				Cube = 1;
			}
			else if(State[VertexId] == 1)
			{
				vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
				Cube = 2;
			}
			else if(State[VertexId] == 2)
			{
				vs_color = vec4(1.0f, 0.4f, 0.4f, 1.0f);
				Cube = 3;
			}
			else
			{
				vs_color = vec4(1.0f, 0.1f, 1.0f, 1.0f);
				Cube = 0;
			}
		}
		else if (gl_VertexID == VertexId * 6 + 2) 
		{ 
			gl_Position = vec4(  Width / 2 + WidthMove + StateMoveX,
			                     Height / 2 + HeightMove + StateMoveY, 0.3f, 1.0f);
			if(State[VertexId] == 0)
			{
				vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
				Cube = 1;
			}
			else if(State[VertexId] == 1)
			{
				vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
				Cube = 2;
			}
			else if(State[VertexId] == 2)
			{
				vs_color = vec4(1.0f, 0.4f, 0.4f, 1.0f);
				Cube = 3;
			}
			else
			{
				vs_color = vec4(1.0f, 0.1f, 1.0f, 1.0f);
				Cube = 0;
			}
		}
		else if (gl_VertexID == VertexId * 6 + 3) 
		{ 
			gl_Position = vec4( -Width / 2 + WidthMove + StateMoveX,
			                    -Height / 2 + HeightMove + StateMoveY, 0.3f, 1.0f); 
			if(State[VertexId] == 0)
			{
				vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
				Cube = 1;
			}
			else if(State[VertexId] == 1)
			{
				vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
				Cube = 2;
			}
			else if(State[VertexId] == 2)
			{
				vs_color = vec4(1.0f, 0.4f, 0.4f, 1.0f);
				Cube = 3;
			}
			else
			{
				vs_color = vec4(1.0f, 0.1f, 1.0f, 1.0f);
				Cube = 0;
			}
		}
		else if (gl_VertexID == VertexId * 6 + 4) 
		{
			gl_Position = vec4( -Width / 2 + WidthMove + StateMoveX,
			                    Height / 2 + HeightMove + StateMoveY, 0.3f, 1.0f);
			if(State[VertexId] == 0)
			{
				vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
				Cube = 1;
			}
			else if(State[VertexId] == 1)
			{
				vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
				Cube = 2;
			}
			else if(State[VertexId] == 2)
			{
				vs_color = vec4(1.0f, 0.4f, 0.4f, 1.0f);
				Cube = 3;
			}
			else
			{
				vs_color = vec4(1.0f, 0.1f, 1.0f, 1.0f);
				Cube = 0;
			}
		}
		else if (gl_VertexID == VertexId * 6 + 5) 
		{
			gl_Position = vec4(  Width / 2 + WidthMove + StateMoveX,
			                     Height / 2 + HeightMove + StateMoveY, 0.3f, 1.0f);
			if(State[VertexId] == 0)
			{
				vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
				Cube = 1;
			}
			else if(State[VertexId] == 1)
			{
				vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
				Cube = 2;
			}
			else if(State[VertexId] == 2)
			{
				vs_color = vec4(1.0f, 0.4f, 0.4f, 1.0f);
				Cube = 3;
			}
			else
			{
				vs_color = vec4(1.0f, 0.1f, 1.0f, 1.0f);
				Cube = 0;
			}
		}

		WidthMove += Width;
		counts++;
		if(counts == SWidth + PreLoads)
		{
			counts = 0;
			WidthMove = -((SWidth + PreLoads - 1) / 2) * Width;
			HeightMove -= Height;
		}
	}

	if(gl_VertexID >= (VertexId - 1) * 6)
	{
		if      (gl_VertexID == (VertexId) * 6 - 6)//(gl_VertexID == 0) //MainMoveBlock 0.2F
		{
			gl_Position = vec4(  Width / 2 + Current_Move_LocationX, -Height / 2 + Current_Move_LocationY, 0.2f, 1.0f); 
			vs_color = vec4(0.9f, 0.8f, 1.0f, 1.0f);
			Cube = -1;
		}
		else if (gl_VertexID == (VertexId) * 6 - 5)//(gl_VertexID == 1) 
		{
			gl_Position = vec4( -Width / 2 + Current_Move_LocationX, -Height / 2 + Current_Move_LocationY, 0.2f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = -1;
		}
		else if (gl_VertexID == (VertexId) * 6 - 4)//(gl_VertexID == 2) 
		{
			gl_Position = vec4(  Width / 2 + Current_Move_LocationX,  Height / 2 + Current_Move_LocationY, 0.2f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = -1;
		}
		else if (gl_VertexID == (VertexId) * 6 - 3)//(gl_VertexID == 3) 
		{
			gl_Position = vec4( -Width / 2 + Current_Move_LocationX, -Height / 2 + Current_Move_LocationY, 0.2f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = -1;
		}
		else if (gl_VertexID == (VertexId) * 6 - 2)//(gl_VertexID == 4) 
		{
			gl_Position = vec4( -Width / 2 + Current_Move_LocationX,  Height / 2 + Current_Move_LocationY, 0.2f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = -1;
		}
		else if (gl_VertexID == (VertexId) * 6 - 1)//(gl_VertexID == 5) 
		{
			gl_Position = vec4(  Width / 2 + Current_Move_LocationX,  Height / 2 + Current_Move_LocationY, 0.2f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = -1;
		}

		else if (gl_VertexID == (VertexId) * 6 + 0)
		{
			gl_Position = vec4(  Width / 16 + 0.9f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 4;
		}
		else if (gl_VertexID == (VertexId) * 6 + 1)
		{
			gl_Position = vec4( -Width / 16 + 0.9f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 4;
		}
		else if (gl_VertexID == (VertexId) * 6 + 2)
		{
			gl_Position = vec4(  Width / 16 + 0.9f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 4;
		}
		else if (gl_VertexID == (VertexId) * 6 + 3)
		{
			gl_Position = vec4( -Width / 16 + 0.9f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 4;
		}
		else if (gl_VertexID == (VertexId) * 6 + 4)
		{
			gl_Position = vec4( -Width / 16 + 0.9f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 4;
		}
		else if (gl_VertexID == (VertexId) * 6 + 5)
		{
			gl_Position = vec4(  Width / 16 + 0.9f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 4;
		}
		/////////////////////////////////////////////////////////////////////////////
		else if (gl_VertexID == (VertexId) * 6 + 6)
		{
			gl_Position = vec4(  Width / 16 + 0.8f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 4;
		}
		else if (gl_VertexID == (VertexId) * 6 + 7)
		{
			gl_Position = vec4( -Width / 16 + 0.8f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 4;
		}
		else if (gl_VertexID == (VertexId) * 6 + 8)
		{
			gl_Position = vec4(  Width / 16 + 0.8f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 4;
		}
		else if (gl_VertexID == (VertexId) * 6 + 9)
		{
			gl_Position = vec4( -Width / 16 + 0.8f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 4;
		}
		else if (gl_VertexID == (VertexId) * 6 + 10)
		{
			gl_Position = vec4( -Width / 16 + 0.8f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 4;
		}
		else if (gl_VertexID == (VertexId) * 6 + 11)
		{
			gl_Position = vec4(  Width / 16 + 0.8f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 4;
		}
		/////////////////////////////////////////////////////////////////////////////
		else if (gl_VertexID == (VertexId) * 6 + 12)
		{
			gl_Position = vec4(  Width / 16 + 0.7f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 4;
		}
		else if (gl_VertexID == (VertexId) * 6 + 13)
		{
			gl_Position = vec4( -Width / 16 + 0.7f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 4;
		}
		else if (gl_VertexID == (VertexId) * 6 + 14)
		{
			gl_Position = vec4(  Width / 16 + 0.7f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 4;
		}
		else if (gl_VertexID == (VertexId) * 6 + 15)
		{
			gl_Position = vec4( -Width / 16 + 0.7f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 4;
		}
		else if (gl_VertexID == (VertexId) * 6 + 16)
		{
			gl_Position = vec4( -Width / 16 + 0.7f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 4;
		}
		else if (gl_VertexID == (VertexId) * 6 + 17)
		{
			gl_Position = vec4(  Width / 16 + 0.7f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 4;
		}
		/////////////////////////////////////////////////////////////////////////////
		else if (gl_VertexID == (VertexId) * 6 + 18)
		{
			gl_Position = vec4(  Width / 16 + 0.6f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 5;
		}
		else if (gl_VertexID == (VertexId) * 6 + 19)
		{
			gl_Position = vec4( -Width / 16 + 0.6f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 5;
		}
		else if (gl_VertexID == (VertexId) * 6 + 20)
		{
			gl_Position = vec4(  Width / 16 + 0.6f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 5;
		}
		else if (gl_VertexID == (VertexId) * 6 + 21)
		{
			gl_Position = vec4( -Width / 16 + 0.6f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 5;
		}
		else if (gl_VertexID == (VertexId) * 6 + 22)
		{
			gl_Position = vec4( -Width / 16 + 0.6f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 5;
		}
		else if (gl_VertexID == (VertexId) * 6 + 23)
		{
			gl_Position = vec4(  Width / 16 + 0.6f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 5;
		}
	}
}