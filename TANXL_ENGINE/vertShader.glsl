//_VERSION_0_7_ UPDATE LOG
// LAST_UPDATE 2023-01-16 17:41
// 纹理功能已调试完成并实装
// 修复Cube不能正确传入片段着色器的问题

#version 430

layout (binding = 0) uniform sampler2D samp;

layout (location = 1) in vec2 texCoord;

layout (location = 3) uniform float Margin;

layout (location = 4) uniform float Current_Move_LocationX;
layout (location = 5) uniform float Current_Move_LocationY;

layout (location = 6) uniform int SHeight;
layout (location = 7) uniform int SWidth;

layout (location = 8) uniform float StateMoveX;
layout (location = 9) uniform float StateMoveY;

layout (location = 10) uniform int PreLoads;

layout (location = 11) in vec3 position;
layout (location = 12) in vec4 color;

layout (location = 13) uniform int Move_With;

uniform int State[200];

out vec4 vs_color;
out vec2 tc;
flat out int Cube;

void main(void)
{
	tc = texCoord;
	
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
			{
				vs_color = vec4(1.0f, 0.8f, 0.1f, 1.0f);
				Cube = 1;
			}
			else if(State[i - 1] == 1)
			{
				vs_color = vec4(0.1f, 0.8f, 1.0f, 1.0f);
				Cube = 2;
			}
			else if(State[i - 1] == 2)
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
		else if (gl_VertexID == i * 6 + 1) 
		{ 
			gl_Position = vec4( -Width / 2 + WidthMove + StateMoveX,
			                    -Height / 2 + HeightMove + StateMoveY, 0.2f, 1.0f); 
			if(State[i - 1] == 0)
			{
				vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
				Cube = 1;
			}
			else if(State[i - 1] == 1)
			{
				vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
				Cube = 2;
			}
			else if(State[i - 1] == 2)
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
		else if (gl_VertexID == i * 6 + 2) 
		{ 
			gl_Position = vec4(  Width / 2 + WidthMove + StateMoveX,
			                     Height / 2 + HeightMove + StateMoveY, 0.2f, 1.0f);
			if(State[i - 1] == 0)
			{
				vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
				Cube = 1;
			}
			else if(State[i - 1] == 1)
			{
				vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
				Cube = 2;
			}
			else if(State[i - 1] == 2)
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
		else if (gl_VertexID == i * 6 + 3) 
		{ 
			gl_Position = vec4( -Width / 2 + WidthMove + StateMoveX,
			                    -Height / 2 + HeightMove + StateMoveY, 0.2f, 1.0f); 
			if(State[i - 1] == 0)
			{
				vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
				Cube = 1;
			}
			else if(State[i - 1] == 1)
			{
				vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
				Cube = 2;
			}
			else if(State[i - 1] == 2)
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
		else if (gl_VertexID == i * 6 + 4) 
		{
			gl_Position = vec4( -Width / 2 + WidthMove + StateMoveX,
			                    Height / 2 + HeightMove + StateMoveY, 0.2f, 1.0f);
			if(State[i - 1] == 0)
			{
				vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
				Cube = 1;
			}
			else if(State[i - 1] == 1)
			{
				vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
				Cube = 2;
			}
			else if(State[i - 1] == 2)
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
		else if (gl_VertexID == i * 6 + 5) 
		{
			gl_Position = vec4(  Width / 2 + WidthMove + StateMoveX,
			                     Height / 2 + HeightMove + StateMoveY, 0.2f, 1.0f);
			if(State[i - 1] == 0)
			{
				vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
				Cube = 1;
			}
			else if(State[i - 1] == 1)
			{
				vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
				Cube = 2;
			}
			else if(State[i - 1] == 2)
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

	if      (gl_VertexID == 0) //MainMoveBlock
	{
		gl_Position = vec4(  Width / 2 + Current_Move_LocationX, -Height / 2 + Current_Move_LocationY, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 0.8f, 1.0f, 1.0f);
		Cube = -1;
	}
	else if (gl_VertexID == 1) 
	{
		gl_Position = vec4( -Width / 2 + Current_Move_LocationX, -Height / 2 + Current_Move_LocationY, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = -1;
	}
	else if (gl_VertexID == 2) 
	{
		gl_Position = vec4(  Width / 2 + Current_Move_LocationX,  Height / 2 + Current_Move_LocationY, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = -1;
	}
	else if (gl_VertexID == 3) 
	{
		gl_Position = vec4( -Width / 2 + Current_Move_LocationX, -Height / 2 + Current_Move_LocationY, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = -1;
	}
	else if (gl_VertexID == 4) 
	{
		gl_Position = vec4( -Width / 2 + Current_Move_LocationX,  Height / 2 + Current_Move_LocationY, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = -1;
	}
	else if (gl_VertexID == 5) 
	{
		gl_Position = vec4(  Width / 2 + Current_Move_LocationX,  Height / 2 + Current_Move_LocationY, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = -1;
	}
}