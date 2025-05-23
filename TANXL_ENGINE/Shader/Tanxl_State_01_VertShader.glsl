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

#version 430

#define STATE_01_LAYER 0.5f
#define TEXTURE_OFFSET 5

layout (location = 1) in vec2 texCoord;

layout (location = 2) uniform int SHeight;
layout (location = 3) uniform int SWidth;

layout (location = 4) uniform float StateMoveX;
layout (location = 5) uniform float StateMoveY;

layout (location = 6) uniform int PreLoads;

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

	for(VertexId = 0; VertexId < State_Datas; ++VertexId)//MAP LAYER 0.3f
	{
		if      (gl_VertexID == VertexId * 6 + 0) 
		{ 
			gl_Position = vec4( -Width + WidthMove + StateMoveX, 
							    -Height + HeightMove + StateMoveY, STATE_01_LAYER, 1.0f);

			Cube = int(Infor[VertexId].x) + TEXTURE_OFFSET;
		}
		else if (gl_VertexID == VertexId * 6 + 1) 
		{ 
			gl_Position = vec4(  Width + WidthMove + StateMoveX,
			                    -Height + HeightMove + StateMoveY, STATE_01_LAYER, 1.0f); 

			Cube = int(Infor[VertexId].x) + TEXTURE_OFFSET;
		}
		else if (gl_VertexID == VertexId * 6 + 2) 
		{ 
			gl_Position = vec4( -Width + WidthMove + StateMoveX,
			                     Height + HeightMove + StateMoveY, STATE_01_LAYER, 1.0f);
			
			Cube = int(Infor[VertexId].x) + TEXTURE_OFFSET;
		}
		else if (gl_VertexID == VertexId * 6 + 3) 
		{ 
			gl_Position = vec4(  Width + WidthMove + StateMoveX,
			                    -Height + HeightMove + StateMoveY, STATE_01_LAYER, 1.0f); 
			
			Cube = int(Infor[VertexId].x) + TEXTURE_OFFSET;
		}
		else if (gl_VertexID == VertexId * 6 + 4) 
		{
			gl_Position = vec4(  Width + WidthMove + StateMoveX,
			                     Height + HeightMove + StateMoveY, STATE_01_LAYER, 1.0f);
			
			Cube = int(Infor[VertexId].x) + TEXTURE_OFFSET;
		}
		else if (gl_VertexID == VertexId * 6 + 5) 
		{
			gl_Position = vec4( -Width + WidthMove + StateMoveX,
			                     Height + HeightMove + StateMoveY, STATE_01_LAYER, 1.0f);
			
			Cube = int(Infor[VertexId].x) + TEXTURE_OFFSET;
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