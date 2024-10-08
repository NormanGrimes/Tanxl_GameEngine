//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-03-17 09:31
// 从顶点着色器中独立出此功能
// 游戏界面增加自定义坐标功能
// 可通过统一变量决定显示的生命值图标数量
// 缩小玩家方块尺寸
// 支持指定数量生命值纹理换行
// 支持自定义生命值的图片间距
// 移除两个未使用变量
// 增加宏控制该层下所有顶点的距离
// 增加操作状态统一变量
// 根据移动操作状态对玩家方块绘制方向
// 增加纵向移动的纹理绘制
// 优化玩家纹理绘制流程
// 纹理编号改为自动获取
// 代码整理优化

#version 430

#define PLAYER_01_LAYER 0.3f

layout (location = 1) in vec2 texCoord;

layout (location = 2) uniform float Current_Move_LocationX;
layout (location = 3) uniform float Current_Move_LocationY;

layout (location = 4) uniform int SHeight;
layout (location = 5) uniform int SWidth;

layout (location = 6) uniform float Begin_Location_X;
layout (location = 7) uniform float Begin_Location_Y;

layout (location = 8) uniform int Health_Length;
layout (location = 9) uniform float Direct_Margin;

layout (location = 10) uniform int Insert_Status;

layout (location = 11) uniform int Player_Texture_01;
layout (location = 12) uniform int Player_Texture_02;
layout (location = 13) uniform int Player_Texture_03;
layout (location = 14) uniform int Player_Texture_04;

layout (location = 15) uniform int Player_Texture_05;
layout (location = 16) uniform int Player_Texture_06;

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

	if(gl_VertexID < 6)
	{
		if(Insert_Status == 0)
			Cube = Player_Texture_02;
		else if(Insert_Status == 1)
			Cube = Player_Texture_04;
		else if(Insert_Status == 2)
			Cube = Player_Texture_03;
		else if(Insert_Status == 3)
			Cube = Player_Texture_01;

		if      (gl_VertexID == 0) //MainMoveBlock 0.2F
		{
			vs_color = vec4(0.9f, 0.8f, 1.0f, 1.0f);
			gl_Position = vec4(  Width / 3 + Current_Move_LocationX, -Height / 3 + Current_Move_LocationY, PLAYER_01_LAYER, 1.0f);
		}
		else if (gl_VertexID == 1)
		{
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			gl_Position = vec4( -Width / 3 + Current_Move_LocationX, -Height / 3 + Current_Move_LocationY, PLAYER_01_LAYER, 1.0f);
		}
		else if (gl_VertexID == 2)
		{
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			gl_Position = vec4(  Width / 3 + Current_Move_LocationX,  Height / 3 + Current_Move_LocationY, PLAYER_01_LAYER, 1.0f);
		}
		else if (gl_VertexID == 3)
		{
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			gl_Position = vec4( -Width / 3 + Current_Move_LocationX, -Height / 3 + Current_Move_LocationY, PLAYER_01_LAYER, 1.0f);
		}
		else if (gl_VertexID == 4)
		{
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			gl_Position = vec4( -Width / 3 + Current_Move_LocationX,  Height / 3 + Current_Move_LocationY, PLAYER_01_LAYER, 1.0f);
		}
		else if (gl_VertexID == 5)
		{
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			gl_Position = vec4(  Width / 3 + Current_Move_LocationX,  Height / 3 + Current_Move_LocationY, PLAYER_01_LAYER, 1.0f);
		}
	}
	else if(gl_VertexID < 12)
	{
		if (gl_VertexID == 6)
		{
			gl_Position = vec4(  Width / 16 + Begin_Location_X, -Height / 16 + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = Player_Texture_06;
		}
		else if (gl_VertexID == 7)
		{
			gl_Position = vec4( -Width / 16 + Begin_Location_X, -Height / 16 + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = Player_Texture_06;
		}
		else if (gl_VertexID == 8)
		{
			gl_Position = vec4(  Width / 16 + Begin_Location_X,  Height / 16 + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = Player_Texture_06;
		}
		else if (gl_VertexID == 9)
		{
			gl_Position = vec4( -Width / 16 + Begin_Location_X, -Height / 16 + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = Player_Texture_06;
		}
		else if (gl_VertexID == 10)
		{
			gl_Position = vec4( -Width / 16 + Begin_Location_X,  Height / 16 + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = Player_Texture_06;
		}
		else if (gl_VertexID == 11)
		{
			gl_Position = vec4(  Width / 16 + Begin_Location_X,  Height / 16 + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = Player_Texture_06;
		}
	}
	else
	{
		Cube = Player_Texture_05;
		for(int i = 2, j = 2; i < Health_Length; i++, j++)
		{
			float LineSpace = (i - 1) / 4 * Direct_Margin;
			
			if (gl_VertexID == i * 6 + 0)
			{
				gl_Position = vec4(  Width / 16 + Begin_Location_X + Direct_Margin * (j - 1), -Height / 16 + Begin_Location_Y - LineSpace, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			else if (gl_VertexID == i * 6 + 1)
			{
				gl_Position = vec4( -Width / 16 + Begin_Location_X + Direct_Margin * (j - 1), -Height / 16 + Begin_Location_Y - LineSpace, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			else if (gl_VertexID == i * 6 + 2)
			{
				gl_Position = vec4(  Width / 16 + Begin_Location_X + Direct_Margin * (j - 1),  Height / 16 + Begin_Location_Y - LineSpace, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			else if (gl_VertexID == i * 6 + 3)
			{
				gl_Position = vec4( -Width / 16 + Begin_Location_X + Direct_Margin * (j - 1), -Height / 16 + Begin_Location_Y - LineSpace, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			else if (gl_VertexID == i * 6 + 4)
			{
				gl_Position = vec4( -Width / 16 + Begin_Location_X + Direct_Margin * (j - 1),  Height / 16 + Begin_Location_Y - LineSpace, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			else if (gl_VertexID == i * 6 + 5)
			{
				gl_Position = vec4(  Width / 16 + Begin_Location_X + Direct_Margin * (j - 1),  Height / 16 + Begin_Location_Y - LineSpace, PLAYER_01_LAYER, 1.0f); 
				vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			}
			
			if(i % 4 == 0)
				j -= 4;
		}
	}
}