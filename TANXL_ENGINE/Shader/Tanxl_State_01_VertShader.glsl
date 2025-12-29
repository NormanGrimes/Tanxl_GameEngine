//_VERSION_0_7_ UPDATE LOG
// LAST_UPDATE 2023-01-16 17:41
// 纹理功能已调试完成并实装
// 修复Cube不能正确传入片段着色器的问题
// 移除未使用变量并重新排序
// 新增游戏界面显示层
// 增加变量保存计算后的方块值
// 地图其他绘制方块移动到地图绘制之后
// 移除未使用变量
// 优化减少高度与宽度的计算量
// 修改最大地图尺寸为20X20
// 修复预载功能只载入了一半内容的问题
// 适配统一变量相关改动
// 方块由固定编号改为获取当前编号
// 增加宏控制备用颜色的启用
// 预加入实例化相关代码
// 地图纹理编号从坐标向量中移动到新向量
// 修复实例化绘制启用导致编译错误的问题
// 增加宏控制该层下所有顶点的距离
// 修复纹理绘制方向横向相反的问题
// 增加根据事件绘制不同纹理的设定
// 移除备用方块颜色功能
// 移除实例化测试相关功能
// 修改游戏纹理起始位置
// 额外预留四个纹理用于其他用途
// 调整第一层地图的深度
// 移除未使用变量
// 调整统一变量位置
// 增加纹理偏移的宏
// 增加三个统一变量存储事件纹理
// 根据事件统一变量选择纹理
// 增加对输出事件纹理的尺寸设置
// 三个已定义的事件纹理移动到事件顶点着色器进行绘制
// 缩小金币纹理的尺寸
// 增加控制事件纹理绘制偏移长度的统一变量
// 缩小神秘核心的纹理尺寸

#version 430

#define STATE_01_LAYER 0.5f
#define STATE_04_LAYER 0.4f // EVENT SHADER

#define TEXTURE_OFFSET 5

layout (location = 1) in vec2 texCoord;

layout (location = 2) uniform int SHeight;
layout (location = 3) uniform int SWidth;

layout (location = 4) uniform float StateMoveX;
layout (location = 5) uniform float StateMoveY;

layout (location = 6) uniform int PreLoads;
layout (location = 7) uniform int ShaderMode;

layout (location = 8 ) uniform int Event_01_TextureId;
layout (location = 9 ) uniform int Event_02_TextureId;
layout (location = 10) uniform int Event_03_TextureId;
layout (location = 11) uniform int Event_04_TextureId;

uniform ivec2 Infor[400];

out vec4 vs_color;
out vec2 tc;
flat out int Cube;

void main(void)
{
	tc = texCoord;
	
	float Height = 1.0f / SHeight; // 每个独立方块的高度
	float Width  = 1.0f / SWidth;  // 每个独立方块的宽度

	int counts = 0;
	int VertexId = 0;
	int State_Datas = (SHeight + PreLoads * 2) * (SWidth + PreLoads * 2) ;

	float WidthMove  = -(SWidth + PreLoads - 1) * Width;
	float HeightMove = (SHeight + PreLoads - 1) * Height;

	float Shrink_Size = 0.5f;

	float Shrink_Height = Height * Shrink_Size;
	float Shrink_Width  = Width  * Shrink_Size;

	for(VertexId = 0; VertexId < State_Datas; ++VertexId)//MAP LAYER 0.3f
	{
		if      (gl_VertexID == VertexId * 6 + 0) 
		{
			if(ShaderMode == 0)
			{
				gl_Position = vec4( -Width + WidthMove + StateMoveX, -Height + HeightMove + StateMoveY, STATE_01_LAYER, 1.0f);
				Cube = int(Infor[VertexId].x) + TEXTURE_OFFSET;
			}
			else
			{
				Cube = -1;
				if		(Infor[VertexId].y == 1)
					Cube = 9;
				else if	(Infor[VertexId].y == 2)
					Cube = 10;
				else if	(Infor[VertexId].y == 3)
					Cube = 11;
				else if (Infor[VertexId].y == 4)
					Cube = Event_01_TextureId;
				else if (Infor[VertexId].y == 5)
					Cube = Event_02_TextureId;

				if ((Infor[VertexId].y == 5) || (Infor[VertexId].y == 4) || (Infor[VertexId].y == 3))
					gl_Position = vec4( -Shrink_Width + WidthMove + StateMoveX, -Shrink_Height + HeightMove + StateMoveY, STATE_04_LAYER, 1.0f);
				else
					gl_Position = vec4( -Width + WidthMove + StateMoveX, -Height + HeightMove + StateMoveY, STATE_04_LAYER, 1.0f);
			}
		}
		else if (gl_VertexID == VertexId * 6 + 1) 
		{
			if(ShaderMode == 0)
			{
				gl_Position = vec4(  Width + WidthMove + StateMoveX, -Height + HeightMove + StateMoveY, STATE_01_LAYER, 1.0f);
				Cube = int(Infor[VertexId].x) + TEXTURE_OFFSET;
			}
			else
			{
				Cube = -1;
				if		(Infor[VertexId].y == 1)
					Cube = 9;
				else if	(Infor[VertexId].y == 2)
					Cube = 10;
				else if	(Infor[VertexId].y == 3)
					Cube = 11;
				else if (Infor[VertexId].y == 4)
					Cube = Event_01_TextureId;
				else if (Infor[VertexId].y == 5)
					Cube = Event_02_TextureId;

				if ((Infor[VertexId].y == 5) || (Infor[VertexId].y == 4) || (Infor[VertexId].y == 3))
					gl_Position = vec4(  Shrink_Width + WidthMove + StateMoveX, -Shrink_Height + HeightMove + StateMoveY, STATE_04_LAYER, 1.0f); 
				else
					gl_Position = vec4(  Width + WidthMove + StateMoveX, -Height + HeightMove + StateMoveY, STATE_04_LAYER, 1.0f);
			}
		}
		else if (gl_VertexID == VertexId * 6 + 2) 
		{
			if(ShaderMode == 0)
			{
				gl_Position = vec4( -Width + WidthMove + StateMoveX,  Height + HeightMove + StateMoveY, STATE_01_LAYER, 1.0f);
				Cube = int(Infor[VertexId].x) + TEXTURE_OFFSET;
			}
			else
			{
				Cube = -1;
				if		(Infor[VertexId].y == 1)
					Cube = 9;
				else if	(Infor[VertexId].y == 2)
					Cube = 10;
				else if	(Infor[VertexId].y == 3)
					Cube = 11;
				else if (Infor[VertexId].y == 4)
					Cube = Event_01_TextureId;
				else if (Infor[VertexId].y == 5)
					Cube = Event_02_TextureId;

				if ((Infor[VertexId].y == 5) || (Infor[VertexId].y == 4) || (Infor[VertexId].y == 3))
					gl_Position = vec4( -Shrink_Width + WidthMove + StateMoveX, Shrink_Height + HeightMove + StateMoveY, STATE_04_LAYER, 1.0f);
				else
					gl_Position = vec4( -Width + WidthMove + StateMoveX, Height + HeightMove + StateMoveY, STATE_04_LAYER, 1.0f);
			}
		}
		else if (gl_VertexID == VertexId * 6 + 3) 
		{
			if(ShaderMode == 0)
			{
				gl_Position = vec4(  Width + WidthMove + StateMoveX, -Height + HeightMove + StateMoveY, STATE_01_LAYER, 1.0f);
				Cube = int(Infor[VertexId].x) + TEXTURE_OFFSET;
			}
			else
			{
				Cube = -1;
				if		(Infor[VertexId].y == 1)
					Cube = 9;
				else if	(Infor[VertexId].y == 2)
					Cube = 10;
				else if	(Infor[VertexId].y == 3)
					Cube = 11;
				else if (Infor[VertexId].y == 4)
					Cube = Event_01_TextureId;
				else if (Infor[VertexId].y == 5)
					Cube = Event_02_TextureId;

				if ((Infor[VertexId].y == 5) || (Infor[VertexId].y == 4) || (Infor[VertexId].y == 3))
					gl_Position = vec4(  Shrink_Width + WidthMove + StateMoveX, -Shrink_Height + HeightMove + StateMoveY, STATE_04_LAYER, 1.0f);
				else
					gl_Position = vec4(  Width + WidthMove + StateMoveX, -Height + HeightMove + StateMoveY, STATE_04_LAYER, 1.0f);
			}
		}
		else if (gl_VertexID == VertexId * 6 + 4) 
		{
			if(ShaderMode == 0)
			{
				gl_Position = vec4(  Width + WidthMove + StateMoveX,  Height + HeightMove + StateMoveY, STATE_01_LAYER, 1.0f);
				Cube = int(Infor[VertexId].x) + TEXTURE_OFFSET;
			}
			else
			{
				Cube = -1;
				if		(Infor[VertexId].y == 1)
					Cube = 9;
				else if	(Infor[VertexId].y == 2)
					Cube = 10;
				else if	(Infor[VertexId].y == 3)
					Cube = 11;
				else if (Infor[VertexId].y == 4)
					Cube = Event_01_TextureId;
				else if (Infor[VertexId].y == 5)
					Cube = Event_02_TextureId;

				if ((Infor[VertexId].y == 5) || (Infor[VertexId].y == 4) || (Infor[VertexId].y == 3))
					gl_Position = vec4(  Shrink_Width + WidthMove + StateMoveX, Shrink_Height + HeightMove + StateMoveY, STATE_04_LAYER, 1.0f);
				else
					gl_Position = vec4(  Width + WidthMove + StateMoveX, Height + HeightMove + StateMoveY, STATE_04_LAYER, 1.0f);
			}
		}
		else if (gl_VertexID == VertexId * 6 + 5) 
		{
			if(ShaderMode == 0)
			{
				gl_Position = vec4( -Width + WidthMove + StateMoveX,  Height + HeightMove + StateMoveY, STATE_01_LAYER, 1.0f);
				Cube = int(Infor[VertexId].x) + TEXTURE_OFFSET;
			}
			else
			{
				Cube = -1;
				if		(Infor[VertexId].y == 1)
					Cube = 9;
				else if	(Infor[VertexId].y == 2)
					Cube = 10;
				else if	(Infor[VertexId].y == 3)
					Cube = 11;
				else if (Infor[VertexId].y == 4)
					Cube = Event_01_TextureId;
				else if (Infor[VertexId].y == 5)
					Cube = Event_02_TextureId;

				if ((Infor[VertexId].y == 5) || (Infor[VertexId].y == 4) || (Infor[VertexId].y == 3))
					gl_Position = vec4( -Shrink_Width + WidthMove + StateMoveX, Shrink_Height + HeightMove + StateMoveY, STATE_04_LAYER, 1.0f);
				else
					gl_Position = vec4( -Width + WidthMove + StateMoveX, Height + HeightMove + StateMoveY, STATE_04_LAYER, 1.0f);
			}
		}

		WidthMove += (Width * 2);
		counts++;
		if(counts == SWidth + PreLoads * 2)
		{
			counts = 0;
			WidthMove = -(SWidth + PreLoads - 1) * Width;
			HeightMove -= (Height * 2);
		}
	}
}