//_VERSION_0_8_ UPDATE LOG
// LAST_UPDATE 2024-02-05 09:52

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