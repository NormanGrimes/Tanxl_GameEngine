//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2024-03-21 14:21
// 新增游戏属性界面着色器
// 增加生命值槽的绘制
// 生命值槽位置与大小调整
// 生命值槽的长度使用统一变量控制

#version 430

#define PLAYER_01_LAYER 0.3f
#define HEALTH_SLOT_DIV 8
#define HEALTH_DIV_SIZE 10

layout (location = 1) in vec2 texCoord;

layout (location = 2) uniform int SHeight;
layout (location = 3) uniform int SWidth;

layout (location = 4) uniform float Begin_Location_X;
layout (location = 5) uniform float Begin_Location_Y;

layout (location = 6) uniform int Health_Length;
layout (location = 7) uniform float Direct_Margin;

layout (location = 8) uniform int Player_Health_Texture_01;
layout (location = 9) uniform int Player_Health_Texture_02;

layout (location = 10) uniform int Player_Health_Slot_Texture_01;
layout (location = 11) uniform int Player_Health_Slot_Texture_02;
layout (location = 12) uniform int Player_Health_Slot_Texture_03;

layout (location = 13) uniform int Health_Slot_Length;

out vec4 vs_color;
out vec2 tc;
flat out int Cube;

void main(void)
{
	float Height = 2.0f / SHeight;
	float Width  = 2.0f / SWidth;
	
	tc = texCoord;

	if(gl_VertexID < (Health_Slot_Length + 1) * 6)
	{
		if(gl_VertexID < 6)
		{
			Cube = Player_Health_Texture_02;
			if (gl_VertexID == 0)
			{
				gl_Position = vec4(  Width / HEALTH_SLOT_DIV + Begin_Location_X, -Height / HEALTH_SLOT_DIV + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			else if (gl_VertexID == 1)
			{
				gl_Position = vec4( -Width / HEALTH_SLOT_DIV + Begin_Location_X, -Height / HEALTH_SLOT_DIV + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			else if (gl_VertexID == 2)
			{
				gl_Position = vec4(  Width / HEALTH_SLOT_DIV + Begin_Location_X,  Height / HEALTH_SLOT_DIV + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			else if (gl_VertexID == 3)
			{
				gl_Position = vec4( -Width / HEALTH_SLOT_DIV + Begin_Location_X, -Height / HEALTH_SLOT_DIV + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			else if (gl_VertexID == 4)
			{
				gl_Position = vec4( -Width / HEALTH_SLOT_DIV + Begin_Location_X,  Height / HEALTH_SLOT_DIV + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			else if (gl_VertexID == 5)
			{
				gl_Position = vec4(  Width / HEALTH_SLOT_DIV + Begin_Location_X,  Height / HEALTH_SLOT_DIV + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
		}
		else
		{
			for(int i = 1; i < Health_Slot_Length + 1; i++)
			{
				float WidthSpace = 0.06f * i;
	
				if (gl_VertexID == i * 6 + 0)
				{
					if(i == 1)
						Cube = Player_Health_Slot_Texture_03;
					else if(i == Health_Slot_Length)
						Cube = Player_Health_Slot_Texture_01;
					else
						Cube = Player_Health_Slot_Texture_02;

					gl_Position = vec4(  Width / HEALTH_SLOT_DIV + Begin_Location_X + WidthSpace + 0.03f, -Height / HEALTH_SLOT_DIV + Begin_Location_Y, PLAYER_01_LAYER + 0.01f, 1.0f); 
					vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
				}
				else if (gl_VertexID == i * 6 + 1)
				{
					if(i == 1)
						Cube = Player_Health_Slot_Texture_03;
					else if(i == Health_Slot_Length)
						Cube = Player_Health_Slot_Texture_01;
					else
						Cube = Player_Health_Slot_Texture_02;

					gl_Position = vec4( -Width / HEALTH_SLOT_DIV + Begin_Location_X + WidthSpace + 0.03f, -Height / HEALTH_SLOT_DIV + Begin_Location_Y, PLAYER_01_LAYER + 0.01f, 1.0f); 
					vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
				}
				else if (gl_VertexID == i * 6 + 2)
				{
					if(i == 1)
						Cube = Player_Health_Slot_Texture_03;
					else if(i == Health_Slot_Length)
						Cube = Player_Health_Slot_Texture_01;
					else
						Cube = Player_Health_Slot_Texture_02;

					gl_Position = vec4(  Width / HEALTH_SLOT_DIV + Begin_Location_X + WidthSpace + 0.03f,  Height / HEALTH_SLOT_DIV + Begin_Location_Y, PLAYER_01_LAYER + 0.01f, 1.0f); 
					vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
				}
				else if (gl_VertexID == i * 6 + 3)
				{
					if(i == 1)
						Cube = Player_Health_Slot_Texture_03;
					else if(i == Health_Slot_Length)
						Cube = Player_Health_Slot_Texture_01;
					else
						Cube = Player_Health_Slot_Texture_02;

					gl_Position = vec4( -Width / HEALTH_SLOT_DIV + Begin_Location_X + WidthSpace + 0.03f, -Height / HEALTH_SLOT_DIV + Begin_Location_Y, PLAYER_01_LAYER + 0.01f, 1.0f); 
					vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
				}
				else if (gl_VertexID == i * 6 + 4)
				{
					if(i == 1)
						Cube = Player_Health_Slot_Texture_03;
					else if(i == Health_Slot_Length)
						Cube = Player_Health_Slot_Texture_01;
					else
						Cube = Player_Health_Slot_Texture_02;

					gl_Position = vec4( -Width / HEALTH_SLOT_DIV + Begin_Location_X + WidthSpace + 0.03f,  Height / HEALTH_SLOT_DIV + Begin_Location_Y, PLAYER_01_LAYER + 0.01f, 1.0f); 
					vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
				}
				else if (gl_VertexID == i * 6 + 5)
				{
					if(i == 1)
						Cube = Player_Health_Slot_Texture_03;
					else if(i == Health_Slot_Length)
						Cube = Player_Health_Slot_Texture_01;
					else
						Cube = Player_Health_Slot_Texture_02;

					gl_Position = vec4(  Width / HEALTH_SLOT_DIV + Begin_Location_X + WidthSpace + 0.03f,  Height / HEALTH_SLOT_DIV + Begin_Location_Y, PLAYER_01_LAYER + 0.01f, 1.0f); 
					vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
				}
			}
		}
	}
	else
	{
		Cube = Player_Health_Texture_01;
		for(int i = 1 + Health_Slot_Length, j = 2; i < Health_Length + Health_Slot_Length - 1; i++, j++)
		{
			if (gl_VertexID == i * 6 + 0)
			{
				gl_Position = vec4(  Width / HEALTH_DIV_SIZE + Begin_Location_X + Direct_Margin * (j - 1), -Height / HEALTH_DIV_SIZE + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			else if (gl_VertexID == i * 6 + 1)
			{
				gl_Position = vec4( -Width / HEALTH_DIV_SIZE + Begin_Location_X + Direct_Margin * (j - 1), -Height / HEALTH_DIV_SIZE + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			else if (gl_VertexID == i * 6 + 2)
			{
				gl_Position = vec4(  Width / HEALTH_DIV_SIZE + Begin_Location_X + Direct_Margin * (j - 1),  Height / HEALTH_DIV_SIZE + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			else if (gl_VertexID == i * 6 + 3)
			{
				gl_Position = vec4( -Width / HEALTH_DIV_SIZE + Begin_Location_X + Direct_Margin * (j - 1), -Height / HEALTH_DIV_SIZE + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			else if (gl_VertexID == i * 6 + 4)
			{
				gl_Position = vec4( -Width / HEALTH_DIV_SIZE + Begin_Location_X + Direct_Margin * (j - 1),  Height / HEALTH_DIV_SIZE + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			else if (gl_VertexID == i * 6 + 5)
			{
				gl_Position = vec4(  Width / HEALTH_DIV_SIZE + Begin_Location_X + Direct_Margin * (j - 1),  Height / HEALTH_DIV_SIZE + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
		}
	}
}