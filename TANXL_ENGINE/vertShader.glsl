//_VERSION_0_6_ UPDATE LOG
// LAST_UPDATE 2022-09-15 21:30
// 正式加入视角移动功能
// 增加第四种状态颜色
// 调整移动物品坐标的名称
// 统一变量采用固定位置
// SHeight/SWidth改为整型类型

#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

out vec4 vs_color;

layout (location = 3) uniform float Margin;

layout (location = 4) uniform float Current_Move_LocationX;
layout (location = 5) uniform float Current_Move_LocationY;

layout (location = 6) uniform int SHeight;
layout (location = 7) uniform int SWidth;

layout (location = 8) uniform float StateMoveX;
layout (location = 9) uniform float StateMoveY;

layout (location = 10) uniform int PreLoads;

uniform int State[200];

void main(void)
{
	
	float Height = 2.0f / SHeight;
	float Width  = 2.0f / SWidth;

	int counts = 0;

	float WidthMove = -((SWidth + PreLoads - 1) / 2) * Width;
	float HeightMove = ((SHeight + PreLoads - 1) / 2) * Height;
	for(int i = 1; i < (SHeight + PreLoads) * (SWidth + PreLoads) + 1; i++)
	{

		if      (gl_VertexID == i * 6 + 0) 
		{ 
			gl_Position = vec4(  Width / 2 + WidthMove + StateMoveX, 
							    -Height / 2 + HeightMove + StateMoveY, 0.2f, 1.0f);
			if(State[i - 1] == 0)
				vs_color = vec4(1.0f, 0.8f, 0.1f, 1.0f);
			else if(State[i - 1] == 1)
				vs_color = vec4(0.1f, 0.8f, 1.0f, 1.0f);
			else if(State[i - 1] == 2)
				vs_color = vec4(1.0f, 0.8f, 0.4f, 1.0f);
			else
				vs_color = vec4(0.9f, 0.7f, 0.9f, 1.0f);
		}
		else if (gl_VertexID == i * 6 + 1) 
		{ 
			gl_Position = vec4( -Width / 2 + WidthMove + StateMoveX,
			                    -Height / 2 + HeightMove + StateMoveY, 0.2f, 1.0f); 
			if(State[i - 1] == 0)
				vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
			else if(State[i - 1] == 1)
				vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
			else if(State[i - 1] == 2)
				vs_color = vec4(1.0f, 0.4f, 0.4f, 1.0f);
			else
				vs_color = vec4(1.0f, 0.1f, 1.0f, 1.0f);
		}
		else if (gl_VertexID == i * 6 + 2) 
		{ 
			gl_Position = vec4(  Width / 2 + WidthMove + StateMoveX,
			                     Height / 2 + HeightMove + StateMoveY, 0.2f, 1.0f);
			if(State[i - 1] == 0)
				vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
			else if(State[i - 1] == 1)
				vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
			else if(State[i - 1] == 2)
				vs_color = vec4(1.0f, 0.4f, 0.4f, 1.0f);
			else
				vs_color = vec4(1.0f, 0.1f, 1.0f, 1.0f);
		}
		else if (gl_VertexID == i * 6 + 3) 
		{ 
			gl_Position = vec4( -Width / 2 + WidthMove + StateMoveX,
			                    -Height / 2 + HeightMove + StateMoveY, 0.2f, 1.0f); 
			if(State[i - 1] == 0)
				vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
			else if(State[i - 1] == 1)
				vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
			else if(State[i - 1] == 2)
				vs_color = vec4(1.0f, 0.4f, 0.4f, 1.0f);
			else
				vs_color = vec4(1.0f, 0.1f, 1.0f, 1.0f);
		}
		else if (gl_VertexID == i * 6 + 4) 
		{
			gl_Position = vec4( -Width / 2 + WidthMove + StateMoveX,
			                    Height / 2 + HeightMove + StateMoveY, 0.2f, 1.0f);
			if(State[i - 1] == 0)
				vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
			else if(State[i - 1] == 1)
				vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
			else if(State[i - 1] == 2)
				vs_color = vec4(1.0f, 0.4f, 0.4f, 1.0f);
			else
				vs_color = vec4(1.0f, 0.1f, 1.0f, 1.0f);
		}
		else if (gl_VertexID == i * 6 + 5) 
		{
			gl_Position = vec4(  Width / 2 + WidthMove + StateMoveX,
			                     Height / 2 + HeightMove + StateMoveY, 0.2f, 1.0f);
			if(State[i - 1] == 0)
				vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
			else if(State[i - 1] == 1)
				vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
			else if(State[i - 1] == 2)
				vs_color = vec4(1.0f, 0.4f, 0.4f, 1.0f);
			else
				vs_color = vec4(1.0f, 0.1f, 1.0f, 1.0f);
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

	if      (gl_VertexID == 0) //MainMoveBlock
	{
		gl_Position = vec4(  Width / 2 + Current_Move_LocationX, -Height / 2 + Current_Move_LocationY, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 0.8f, 1.0f, 1.0f);
	}
	else if (gl_VertexID == 1) 
	{
		gl_Position = vec4( -Width / 2 + Current_Move_LocationX, -Height / 2 + Current_Move_LocationY, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
	}
	else if (gl_VertexID == 2) 
	{
		gl_Position = vec4(  Width / 2 + Current_Move_LocationX,  Height / 2 + Current_Move_LocationY, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
	}
	else if (gl_VertexID == 3) 
	{
		gl_Position = vec4( -Width / 2 + Current_Move_LocationX, -Height / 2 + Current_Move_LocationY, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
	}
	else if (gl_VertexID == 4) 
	{
		gl_Position = vec4( -Width / 2 + Current_Move_LocationX,  Height / 2 + Current_Move_LocationY, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
	}
	else if (gl_VertexID == 5) 
	{
		gl_Position = vec4(  Width / 2 + Current_Move_LocationX,  Height / 2 + Current_Move_LocationY, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
	}
}