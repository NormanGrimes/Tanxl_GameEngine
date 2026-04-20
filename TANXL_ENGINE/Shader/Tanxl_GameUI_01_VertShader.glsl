//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2024-03-21 14:21
// 新增游戏属性界面着色器
// 增加生命值槽的绘制

#version 430

#define PLAYER_01_LAYER 0.3f
#define HEALTH_DIV_SIZE 10
#define HEALTH_SLOT_LENGTH 25

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

out vec4 vs_color;
out vec2 tc;
flat out int Cube;

void main(void)
{
	float Height = 2.0f / SHeight;
	float Width  = 2.0f / SWidth;
	
	tc = texCoord;

	if(gl_VertexID < (HEALTH_SLOT_LENGTH + 1) * 6)
	{
		if(gl_VertexID < 6)
		{
			Cube = Player_Health_Texture_02;
			if (gl_VertexID == 0)
			{
				gl_Position = vec4(  Width / 9 + Begin_Location_X, -Height / 9 + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			else if (gl_VertexID == 1)
			{
				gl_Position = vec4( -Width / 9 + Begin_Location_X, -Height / 9 + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			else if (gl_VertexID == 2)
			{
				gl_Position = vec4(  Width / 9 + Begin_Location_X,  Height / 9 + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			else if (gl_VertexID == 3)
			{
				gl_Position = vec4( -Width / 9 + Begin_Location_X, -Height / 9 + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			else if (gl_VertexID == 4)
			{
				gl_Position = vec4( -Width / 9 + Begin_Location_X,  Height / 9 + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			else if (gl_VertexID == 5)
			{
				gl_Position = vec4(  Width / 9 + Begin_Location_X,  Height / 9 + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
		}
		else
		{
			for(int i = 1; i < HEALTH_SLOT_LENGTH + 1; i++)
			{
				float WidthSpace = 0.06f * i;

				Cube = Player_Health_Slot_Texture_02;

				if(i == 1)
					Cube = Player_Health_Slot_Texture_01;
				else if(i == HEALTH_SLOT_LENGTH + 1)
					Cube = Player_Health_Slot_Texture_03;
	
				if (gl_VertexID == i * 6 + 0)
				{
					gl_Position = vec4(  Width / 9 + Begin_Location_X + WidthSpace, -Height / 9 + Begin_Location_Y, PLAYER_01_LAYER + 0.01f, 1.0f); 
					vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
				}
				else if (gl_VertexID == i * 6 + 1)
				{
					gl_Position = vec4( -Width / 9 + Begin_Location_X + WidthSpace, -Height / 9 + Begin_Location_Y, PLAYER_01_LAYER + 0.01f, 1.0f); 
					vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
				}
				else if (gl_VertexID == i * 6 + 2)
				{
					gl_Position = vec4(  Width / 9 + Begin_Location_X + WidthSpace,  Height / 9 + Begin_Location_Y, PLAYER_01_LAYER + 0.01f, 1.0f); 
					vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
				}
				else if (gl_VertexID == i * 6 + 3)
				{
					gl_Position = vec4( -Width / 9 + Begin_Location_X + WidthSpace, -Height / 9 + Begin_Location_Y, PLAYER_01_LAYER + 0.01f, 1.0f); 
					vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
				}
				else if (gl_VertexID == i * 6 + 4)
				{
					gl_Position = vec4( -Width / 9 + Begin_Location_X + WidthSpace,  Height / 9 + Begin_Location_Y, PLAYER_01_LAYER + 0.01f, 1.0f); 
					vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
				}
				else if (gl_VertexID == i * 6 + 5)
				{
					gl_Position = vec4(  Width / 9 + Begin_Location_X + WidthSpace,  Height / 9 + Begin_Location_Y, PLAYER_01_LAYER + 0.01f, 1.0f); 
					vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
				}
			}
		}
	}
	else
	{
		Cube = Player_Health_Texture_01;
		for(int i = 1 + HEALTH_SLOT_LENGTH, j = 2; i < Health_Length + HEALTH_SLOT_LENGTH - 1; i++, j++)
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