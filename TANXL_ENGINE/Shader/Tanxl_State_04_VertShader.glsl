//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-10-31 10:50
// 增加三个统一变量存储事件纹理
// 根据事件统一变量选择纹理

#version 430

#define STATE_04_LAYER 0.4f

layout (location = 1) in vec2 texCoord;

layout (location = 2) uniform int SHeight;
layout (location = 3) uniform int SWidth;

layout (location = 4) uniform float StateMoveX;
layout (location = 5) uniform float StateMoveY;

layout (location = 6) uniform int PreLoads;

layout (location = 7) uniform int Event_01_TextureId;
layout (location = 8) uniform int Event_02_TextureId;
layout (location = 9) uniform int Event_03_TextureId;

uniform int EventInfor[400];

out vec4 vs_color;
out vec2 tc;
flat out int Cube = -1;

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

	for(VertexId = 0; VertexId < State_Datas; ++VertexId)//EVENT LAYER 0.3f
	{
		if      (gl_VertexID == VertexId * 6 + 0) 
		{ 
			gl_Position = vec4( -Width + WidthMove + StateMoveX, 
							    -Height + HeightMove + StateMoveY, STATE_04_LAYER, 1.0f);

			if      (EventInfor[VertexId] == 1)
				Cube = Event_01_TextureId;
			else if (EventInfor[VertexId] == 2)
				Cube = Event_02_TextureId;
			else
				Cube = Event_03_TextureId;
		}
		else if (gl_VertexID == VertexId * 6 + 1) 
		{ 
			gl_Position = vec4(  Width + WidthMove + StateMoveX,
			                    -Height + HeightMove + StateMoveY, STATE_04_LAYER, 1.0f); 

			if      (EventInfor[VertexId] == 1)
				Cube = Event_01_TextureId;
			else if (EventInfor[VertexId] == 2)
				Cube = Event_02_TextureId;
			else
				Cube = Event_03_TextureId;
		}
		else if (gl_VertexID == VertexId * 6 + 2) 
		{ 
			gl_Position = vec4( -Width + WidthMove + StateMoveX,
			                     Height + HeightMove + StateMoveY, STATE_04_LAYER, 1.0f);
			
			if      (EventInfor[VertexId] == 1)
				Cube = Event_01_TextureId;
			else if (EventInfor[VertexId] == 2)
				Cube = Event_02_TextureId;
			else
				Cube = Event_03_TextureId;
		}
		else if (gl_VertexID == VertexId * 6 + 3) 
		{ 
			gl_Position = vec4(  Width + WidthMove + StateMoveX,
			                    -Height + HeightMove + StateMoveY, STATE_04_LAYER, 1.0f); 
			
			if      (EventInfor[VertexId] == 1)
				Cube = Event_01_TextureId;
			else if (EventInfor[VertexId] == 2)
				Cube = Event_02_TextureId;
			else
				Cube = Event_03_TextureId;
		}
		else if (gl_VertexID == VertexId * 6 + 4) 
		{
			gl_Position = vec4(  Width + WidthMove + StateMoveX,
			                     Height + HeightMove + StateMoveY, STATE_04_LAYER, 1.0f);
			
			if      (EventInfor[VertexId] == 1)
				Cube = Event_01_TextureId;
			else if (EventInfor[VertexId] == 2)
				Cube = Event_02_TextureId;
			else
				Cube = Event_03_TextureId;
		}
		else if (gl_VertexID == VertexId * 6 + 5) 
		{
			gl_Position = vec4( -Width + WidthMove + StateMoveX,
			                     Height + HeightMove + StateMoveY, STATE_04_LAYER, 1.0f);
			
			if      (EventInfor[VertexId] == 1)
				Cube = Event_01_TextureId;
			else if (EventInfor[VertexId] == 2)
				Cube = Event_02_TextureId;
			else
				Cube = Event_03_TextureId;
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