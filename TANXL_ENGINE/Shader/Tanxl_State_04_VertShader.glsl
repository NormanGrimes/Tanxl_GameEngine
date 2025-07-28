//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-10-31 10:50
// 增加三个统一变量存储事件纹理
// 根据事件统一变量选择纹理
// 增加对输出事件纹理的尺寸设置
// 三个已定义的事件纹理移动到事件顶点着色器进行绘制
// 缩小金币纹理的尺寸
// 增加控制事件纹理绘制偏移长度的统一变量
// 缩小神秘核心的纹理尺寸

#version 430

#define STATE_04_LAYER 0.4f // EVENT SHADER

layout (location = 1) in vec2 texCoord;

layout (location = 2) uniform int SHeight;
layout (location = 3) uniform int SWidth;

layout (location = 4) uniform float StateMoveX;
layout (location = 5) uniform float StateMoveY;

layout (location = 6) uniform int PreLoads;

layout (location = 7 ) uniform int Event_01_TextureId;
layout (location = 8 ) uniform int Event_02_TextureId;
layout (location = 9 ) uniform int Event_03_TextureId;
layout (location = 10) uniform int Event_04_TextureId;

uniform vec2 State_OffSet[400];

uniform int EventInfor[400];

out vec4 vs_color;
out vec2 tc;
flat out int Cube;

void main(void)
{
	tc = texCoord;
	
	float Height = 1.0f / SHeight; // 每个独立方块的高度
	float Width  = 1.0f / SWidth;  // 每个独立方块的宽度

	float Shrink_Size = 0.5f;

	float Shrink_Height = Height * Shrink_Size;
	float Shrink_Width  = Width  * Shrink_Size;

	int counts = 0;
	int VertexId = 0;
	int State_Datas = (SHeight + PreLoads * 2) * (SWidth + PreLoads * 2) ;

	float WidthMove  = -(SWidth + PreLoads - 1) * Width;
	float HeightMove = (SHeight + PreLoads - 1) * Height;
	
	Cube = -1;

	for(VertexId = 0; VertexId < State_Datas; ++VertexId)//EVENT LAYER 0.3f
	{
		if      (gl_VertexID == VertexId * 6 + 0) 
		{
			if		(EventInfor[VertexId] == 1)
				Cube = 9;
			else if	(EventInfor[VertexId] == 2)
				Cube = 10;
			else if	(EventInfor[VertexId] == 3)
				Cube = 11;
			else if (EventInfor[VertexId] == 4)
				Cube = Event_01_TextureId;
			else if (EventInfor[VertexId] == 5)
			    Cube = Event_02_TextureId;

			if ((EventInfor[VertexId] == 5) || (EventInfor[VertexId] == 4) || (EventInfor[VertexId] == 3))
				gl_Position = vec4( -Shrink_Width + WidthMove + StateMoveX + State_OffSet[VertexId].x, -Shrink_Height + HeightMove + StateMoveY + State_OffSet[VertexId].y, STATE_04_LAYER, 1.0f);
			else
				gl_Position = vec4( -Width + WidthMove + StateMoveX + State_OffSet[VertexId].x, -Height + HeightMove + StateMoveY + State_OffSet[VertexId].y, STATE_04_LAYER, 1.0f);
		}
		else if (gl_VertexID == VertexId * 6 + 1) 
		{
			if		(EventInfor[VertexId] == 1)
				Cube = 9;
			else if	(EventInfor[VertexId] == 2)
				Cube = 10;
			else if	(EventInfor[VertexId] == 3)
				Cube = 11;
			else if (EventInfor[VertexId] == 4)
				Cube = Event_01_TextureId;
			else if (EventInfor[VertexId] == 5)
			    Cube = Event_02_TextureId;

			if ((EventInfor[VertexId] == 5) || (EventInfor[VertexId] == 4) || (EventInfor[VertexId] == 3))
				gl_Position = vec4(  Shrink_Width + WidthMove + StateMoveX + State_OffSet[VertexId].x, -Shrink_Height + HeightMove + StateMoveY + State_OffSet[VertexId].y, STATE_04_LAYER, 1.0f); 
			else
				gl_Position = vec4(  Width + WidthMove + StateMoveX + State_OffSet[VertexId].x, -Height + HeightMove + StateMoveY + State_OffSet[VertexId].y, STATE_04_LAYER, 1.0f);
		}
		else if (gl_VertexID == VertexId * 6 + 2) 
		{
			if		(EventInfor[VertexId] == 1)
				Cube = 9;
			else if	(EventInfor[VertexId] == 2)
				Cube = 10;
			else if	(EventInfor[VertexId] == 3)
				Cube = 11;
			else if (EventInfor[VertexId] == 4)
				Cube = Event_01_TextureId;
			else if (EventInfor[VertexId] == 5)
			    Cube = Event_02_TextureId;

			if ((EventInfor[VertexId] == 5) || (EventInfor[VertexId] == 4) || (EventInfor[VertexId] == 3))
				gl_Position = vec4( -Shrink_Width + WidthMove + StateMoveX + State_OffSet[VertexId].x, Shrink_Height + HeightMove + StateMoveY + State_OffSet[VertexId].y, STATE_04_LAYER, 1.0f);
			else
				gl_Position = vec4( -Width + WidthMove + StateMoveX + State_OffSet[VertexId].x, Height + HeightMove + StateMoveY + State_OffSet[VertexId].y, STATE_04_LAYER, 1.0f);
		}
		else if (gl_VertexID == VertexId * 6 + 3) 
		{
			if		(EventInfor[VertexId] == 1)
				Cube = 9;
			else if	(EventInfor[VertexId] == 2)
				Cube = 10;
			else if	(EventInfor[VertexId] == 3)
				Cube = 11;
			else if (EventInfor[VertexId] == 4)
				Cube = Event_01_TextureId;
			else if (EventInfor[VertexId] == 5)
			    Cube = Event_02_TextureId;

			if ((EventInfor[VertexId] == 5) || (EventInfor[VertexId] == 4) || (EventInfor[VertexId] == 3))
				gl_Position = vec4(  Shrink_Width + WidthMove + StateMoveX + State_OffSet[VertexId].x, -Shrink_Height + HeightMove + StateMoveY + State_OffSet[VertexId].y, STATE_04_LAYER, 1.0f);
			else
				gl_Position = vec4(  Width + WidthMove + StateMoveX + State_OffSet[VertexId].x, -Height + HeightMove + StateMoveY + State_OffSet[VertexId].y, STATE_04_LAYER, 1.0f);
		}
		else if (gl_VertexID == VertexId * 6 + 4) 
		{
			if		(EventInfor[VertexId] == 1)
				Cube = 9;
			else if	(EventInfor[VertexId] == 2)
				Cube = 10;
			else if	(EventInfor[VertexId] == 3)
				Cube = 11;
			else if (EventInfor[VertexId] == 4)
				Cube = Event_01_TextureId;
			else if (EventInfor[VertexId] == 5)
			    Cube = Event_02_TextureId;

			if ((EventInfor[VertexId] == 5) || (EventInfor[VertexId] == 4) || (EventInfor[VertexId] == 3))
				gl_Position = vec4(  Shrink_Width + WidthMove + StateMoveX + State_OffSet[VertexId].x, Shrink_Height + HeightMove + StateMoveY + State_OffSet[VertexId].y, STATE_04_LAYER, 1.0f);
			else
				gl_Position = vec4(  Width + WidthMove + StateMoveX + State_OffSet[VertexId].x, Height + HeightMove + StateMoveY + State_OffSet[VertexId].y, STATE_04_LAYER, 1.0f);
		}
		else if (gl_VertexID == VertexId * 6 + 5) 
		{
			if		(EventInfor[VertexId] == 1)
				Cube = 9;
			else if	(EventInfor[VertexId] == 2)
				Cube = 10;
			else if	(EventInfor[VertexId] == 3)
				Cube = 11;
			else if (EventInfor[VertexId] == 4)
				Cube = Event_01_TextureId;
			else if (EventInfor[VertexId] == 5)
			    Cube = Event_02_TextureId;

			if ((EventInfor[VertexId] == 5) || (EventInfor[VertexId] == 4) || (EventInfor[VertexId] == 3))
				gl_Position = vec4( -Shrink_Width + WidthMove + StateMoveX + State_OffSet[VertexId].x, Shrink_Height + HeightMove + StateMoveY + State_OffSet[VertexId].y, STATE_04_LAYER, 1.0f);
			else
				gl_Position = vec4( -Width + WidthMove + StateMoveX + State_OffSet[VertexId].x, Height + HeightMove + StateMoveY + State_OffSet[VertexId].y, STATE_04_LAYER, 1.0f);
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