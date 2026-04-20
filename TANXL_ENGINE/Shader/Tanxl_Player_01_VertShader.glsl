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
// 调整并增加宏控制生命方块大小
// 移除未使用的颜色输入
// 增加正面眨眼的动作纹理
// 修复人物纹理左右颠倒的问题
// 移除未使用变量
// 移除奔跑动作相关参数
// 移除眨眼动作相关参数
// 玩家图形仅保留玩家纹理统一变量
// 移入部分四号着色器的功能
// 增加一行可显示的最大的生命值数量

#version 430

#define PLAYER_01_LAYER 0.3f
#define HEALTH_DIV_SIZE 10

layout (location = 1) in vec2 texCoord;

layout (location = 2) uniform float Current_Move_LocationX;
layout (location = 3) uniform float Current_Move_LocationY;

layout (location = 4) uniform int SHeight;
layout (location = 5) uniform int SWidth;

layout (location = 6) uniform int Player_Texture_Main;

out vec4 vs_color;
out vec2 tc;
flat out int Cube;

void main(void)
{
	float Height = 2.0f / SHeight;
	float Width  = 2.0f / SWidth;
	
	tc = texCoord;

	Cube = Player_Texture_Main;

	if      (gl_VertexID == 0) //MainMoveBlock 0.2F
	{
		vs_color = vec4(0.9f, 0.8f, 1.0f, 1.0f);
		gl_Position = vec4( -Width / 3 + Current_Move_LocationX, -Height / 3 + Current_Move_LocationY, PLAYER_01_LAYER, 1.0f);
	}
	else if (gl_VertexID == 1)
	{
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		gl_Position = vec4(  Width / 3 + Current_Move_LocationX, -Height / 3 + Current_Move_LocationY, PLAYER_01_LAYER, 1.0f);
	}
	else if (gl_VertexID == 2)
	{
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		gl_Position = vec4( -Width / 3 + Current_Move_LocationX,  Height / 3 + Current_Move_LocationY, PLAYER_01_LAYER, 1.0f);
	}
	else if (gl_VertexID == 3)
	{
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		gl_Position = vec4(  Width / 3 + Current_Move_LocationX, -Height / 3 + Current_Move_LocationY, PLAYER_01_LAYER, 1.0f);
	}
	else if (gl_VertexID == 4)
	{
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		gl_Position = vec4(  Width / 3 + Current_Move_LocationX,  Height / 3 + Current_Move_LocationY, PLAYER_01_LAYER, 1.0f);
	}
	else if (gl_VertexID == 5)
	{
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		gl_Position = vec4( -Width / 3 + Current_Move_LocationX,  Height / 3 + Current_Move_LocationY, PLAYER_01_LAYER, 1.0f);
	}
}