//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-03-17 09:31
// 从顶点着色器中独立出此功能
// 游戏界面增加自定义坐标功能
// 可通过同一变量决定显示的生命值图标数量
// 缩小玩家方块尺寸
// 支持指定数量生命值纹理换行

#version 430

layout (location = 1) in vec2 texCoord;

layout (location = 2) uniform float Current_Move_LocationX;
layout (location = 3) uniform float Current_Move_LocationY;

layout (location = 4) uniform int SHeight;
layout (location = 5) uniform int SWidth;

layout (location = 6) uniform float Begin_Location_X;
layout (location = 7) uniform float Begin_Location_Y;

layout (location = 8) uniform float Margin;
layout (location = 9) uniform float CuSize;

layout (location = 10) uniform int Health_Length;
layout (location = 11) uniform int Direct_Margin;

in vec4 color;

out vec4 vs_color;
out vec2 tc;
flat out int Cube;

void main(void)
{
	float Margin_X = 0.0f;
	float Margin_Y = 0.0f;

	float Height = 2.0f / SHeight;
	float Width  = 2.0f / SWidth;
	
	tc = texCoord;

	if      (gl_VertexID == 0) //MainMoveBlock 0.2F
	{
		gl_Position = vec4(  Width / 3 + Current_Move_LocationX, -Height / 3 + Current_Move_LocationY, 0.2f, 1.0f); 
		vs_color = vec4(0.9f, 0.8f, 1.0f, 1.0f);
		Cube = 5;
	}
	else if (gl_VertexID == 1)
	{
		gl_Position = vec4( -Width / 3 + Current_Move_LocationX, -Height / 3 + Current_Move_LocationY, 0.2f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 5;
	}
	else if (gl_VertexID == 2)
	{
		gl_Position = vec4(  Width / 3 + Current_Move_LocationX,  Height / 3 + Current_Move_LocationY, 0.2f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 5;
	}
	else if (gl_VertexID == 3)
	{
		gl_Position = vec4( -Width / 3 + Current_Move_LocationX, -Height / 3 + Current_Move_LocationY, 0.2f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 5;
	}
	else if (gl_VertexID == 4)
	{
		gl_Position = vec4( -Width / 3 + Current_Move_LocationX,  Height / 3 + Current_Move_LocationY, 0.2f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 5;
	}
	else if (gl_VertexID == 5)
	{
		gl_Position = vec4(  Width / 3 + Current_Move_LocationX,  Height / 3 + Current_Move_LocationY, 0.2f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 5;
	}

	else if (gl_VertexID == 6)
	{
		gl_Position = vec4(  Width / 16 + Begin_Location_X, -Height / 16 + Begin_Location_Y, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 7;
	}
	else if (gl_VertexID == 7)
	{
		gl_Position = vec4( -Width / 16 + Begin_Location_X, -Height / 16 + Begin_Location_Y, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 7;
	}
	else if (gl_VertexID == 8)
	{
		gl_Position = vec4(  Width / 16 + Begin_Location_X,  Height / 16 + Begin_Location_Y, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 7;
	}
	else if (gl_VertexID == 9)
	{
		gl_Position = vec4( -Width / 16 + Begin_Location_X, -Height / 16 + Begin_Location_Y, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 7;
	}
	else if (gl_VertexID == 10)
	{
		gl_Position = vec4( -Width / 16 + Begin_Location_X,  Height / 16 + Begin_Location_Y, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 7;
	}
	else if (gl_VertexID == 11)
	{
		gl_Position = vec4(  Width / 16 + Begin_Location_X,  Height / 16 + Begin_Location_Y, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 7;
	}

	for(int i = 2, j = 2; i < Health_Length; i++, j++)
	{
		float LineSpace = (i - 1) / 4 * 0.1f;

		if (gl_VertexID == i * 6 + 0)
		{
			gl_Position = vec4(  Width / 16 + Begin_Location_X + 0.1f * (j - 1), -Height / 16 + Begin_Location_Y - LineSpace, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 6;
		}
		else if (gl_VertexID == i * 6 + 1)
		{
			gl_Position = vec4( -Width / 16 + Begin_Location_X + 0.1f * (j - 1), -Height / 16 + Begin_Location_Y - LineSpace, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 6;
		}
		else if (gl_VertexID == i * 6 + 2)
		{
			gl_Position = vec4(  Width / 16 + Begin_Location_X + 0.1f * (j - 1),  Height / 16 + Begin_Location_Y - LineSpace, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 6;
		}
		else if (gl_VertexID == i * 6 + 3)
		{
			gl_Position = vec4( -Width / 16 + Begin_Location_X + 0.1f * (j - 1), -Height / 16 + Begin_Location_Y - LineSpace, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 6;
		}
		else if (gl_VertexID == i * 6 + 4)
		{
			gl_Position = vec4( -Width / 16 + Begin_Location_X + 0.1f * (j - 1),  Height / 16 + Begin_Location_Y - LineSpace, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 6;
		}
		else if (gl_VertexID == i * 6 + 5)
		{
			gl_Position = vec4(  Width / 16 + Begin_Location_X + 0.1f * (j - 1),  Height / 16 + Begin_Location_Y - LineSpace, 0.1f, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 6;
		}

		if(i % 4 == 0)
			j -= 4;
	}
}