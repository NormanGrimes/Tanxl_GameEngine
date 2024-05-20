//_VERSION_0_7_ UPDATE LOG
// LAST_UPDATE 2023-01-16 17:41
// �������ѵ�����ɲ�ʵװ
// �޸�Cube������ȷ����Ƭ����ɫ��������
// �Ƴ�δʹ�ñ�������������
// ������Ϸ������ʾ��
// ���ӱ�����������ķ���ֵ
// ��ͼ�������Ʒ����ƶ�����ͼ����֮��
// �Ƴ�δʹ�ñ���
// �Ż����ٸ߶����ȵļ�����
// �޸�����ͼ�ߴ�Ϊ20X20
// �޸�Ԥ�ع���ֻ������һ�����ݵ�����
// ����ͳһ������ظĶ�
// �����ɹ̶���Ÿ�Ϊ��ȡ��ǰ���
// ���Ӻ���Ʊ�����ɫ������
// Ԥ����ʵ������ش���
// ��ͼ�����Ŵ������������ƶ���������
// �޸�ʵ�����������õ��±�����������

#version 430

//deaflut color : Enable when texture is not exist
#define VERTSHADER_STATE_01_TEXTUR_BACKUP_COLOR 0

#define VERTSHADER_STATE_01_INSTANCED_VERSION   0

layout (location = 1) in vec2 texCoord;

layout (location = 2) uniform float Current_Move_LocationX;
layout (location = 3) uniform float Current_Move_LocationY;

layout (location = 4) uniform int SHeight;
layout (location = 5) uniform int SWidth;

layout (location = 6) uniform float StateMoveX;
layout (location = 7) uniform float StateMoveY;

layout (location = 8) uniform int PreLoads;

uniform vec2 State[400];
uniform ivec2 Infor[400];

out vec4 vs_color;
out vec2 tc;
flat out int Cube;

void main(void)
{
	tc = texCoord;
	
	float Height = 1.0f / SHeight; // ÿ����������ĸ߶�
	float Width  = 1.0f / SWidth;  // ÿ����������Ŀ��

	int counts = 0;
	int VertexId = 0;
	int State_Datas = (SHeight + PreLoads * 2) * (SWidth + PreLoads * 2) ;

	vec2 OffSet = State[State_Datas].xy;

	float WidthMove  = -(SWidth + PreLoads - 1) * Width;
	float HeightMove = (SHeight + PreLoads - 1) * Height;

#if VERTSHADER_STATE_01_INSTANCED_VERSION
	gl_Position = vec4(OffSet[0], OffSet[1], 0.3f, 1.0f);
	Cube = int(Infor[VertexId].x);
	if(Cube == 4)
		Cube = 8;
	vs_color = vec4(0.9f, 0.7f, 0.9f, 1.0f);
#endif

#if !VERTSHADER_STATE_01_INSTANCED_VERSION
	for(VertexId = 0; VertexId < State_Datas; ++VertexId)//MAP LAYER 0.3F
	{
		if      (gl_VertexID == VertexId * 6 + 0) 
		{ 
			gl_Position = vec4(  Width + WidthMove + StateMoveX, 
							    -Height + HeightMove + StateMoveY, 0.3f, 1.0f);
			Cube = int(Infor[VertexId].x);
#if VERTSHADER_STATE_01_TEXTUR_BACKUP_COLOR
			if(Infor[VertexId].x == 0)
			{
				vs_color = vec4(1.0f, 0.8f, 0.1f, 1.0f);
			}
			else if(Infor[VertexId].x == 1)
			{
				vs_color = vec4(0.1f, 0.8f, 1.0f, 1.0f);
			}
			else if(Infor[VertexId].x == 2)
			{
				vs_color = vec4(1.0f, 0.8f, 0.4f, 1.0f);
			}
			else
			{
				vs_color = vec4(0.9f, 0.7f, 0.9f, 1.0f);
			}
#endif
		}
		else if (gl_VertexID == VertexId * 6 + 1) 
		{ 
			gl_Position = vec4( -Width + WidthMove + StateMoveX,
			                    -Height + HeightMove + StateMoveY, 0.3f, 1.0f); 
			Cube = int(Infor[VertexId].x);
#if VERTSHADER_STATE_01_TEXTUR_BACKUP_COLOR
			if(Infor[VertexId].x == 0)
			{
				vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
			}
			else if(Infor[VertexId].x == 1)
			{
				vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
			}
			else if(Infor[VertexId].x == 2)
			{
				vs_color = vec4(1.0f, 0.4f, 0.4f, 1.0f);
			}
			else
			{
				vs_color = vec4(1.0f, 0.1f, 1.0f, 1.0f);
			}
#endif
		}
		else if (gl_VertexID == VertexId * 6 + 2) 
		{ 
			gl_Position = vec4(  Width + WidthMove + StateMoveX,
			                     Height + HeightMove + StateMoveY, 0.3f, 1.0f);
			Cube = int(Infor[VertexId].x);
#if VERTSHADER_STATE_01_TEXTUR_BACKUP_COLOR
			if(Infor[VertexId].x == 0)
			{
				vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
			}
			else if(Infor[VertexId].x == 1)
			{
				vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
			}
			else if(Infor[VertexId].x == 2)
			{
				vs_color = vec4(1.0f, 0.4f, 0.4f, 1.0f);
			}
			else
			{
				vs_color = vec4(1.0f, 0.1f, 1.0f, 1.0f);
			}
#endif
		}
		else if (gl_VertexID == VertexId * 6 + 3) 
		{ 
			gl_Position = vec4( -Width + WidthMove + StateMoveX,
			                    -Height + HeightMove + StateMoveY, 0.3f, 1.0f); 
			Cube = int(Infor[VertexId].x);
#if VERTSHADER_STATE_01_TEXTUR_BACKUP_COLOR
			if(Infor[VertexId].x == 0)
			{
				vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
			}
			else if(Infor[VertexId].x == 1)
			{
				vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
			}
			else if(Infor[VertexId].x == 2)
			{
				vs_color = vec4(1.0f, 0.4f, 0.4f, 1.0f);
			}
			else
			{
				vs_color = vec4(1.0f, 0.1f, 1.0f, 1.0f);
			}
#endif
		}
		else if (gl_VertexID == VertexId * 6 + 4) 
		{
			gl_Position = vec4( -Width + WidthMove + StateMoveX,
			                    Height + HeightMove + StateMoveY, 0.3f, 1.0f);
			Cube = int(Infor[VertexId].x);
#if VERTSHADER_STATE_01_TEXTUR_BACKUP_COLOR
			if(Infor[VertexId].x == 0)
			{
				vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
			}
			else if(Infor[VertexId].x == 1)
			{
				vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
			}
			else if(Infor[VertexId].x == 2)
			{
				vs_color = vec4(1.0f, 0.4f, 0.4f, 1.0f);
			}
			else
			{
				vs_color = vec4(1.0f, 0.1f, 1.0f, 1.0f);
			}
#endif
		}
		else if (gl_VertexID == VertexId * 6 + 5) 
		{
			gl_Position = vec4(  Width + WidthMove + StateMoveX,
			                     Height + HeightMove + StateMoveY, 0.3f, 1.0f);
			Cube = int(Infor[VertexId].x);
#if VERTSHADER_STATE_01_TEXTUR_BACKUP_COLOR
			if(Infor[VertexId].x == 0)
			{
				vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0f);
			}
			else if(Infor[VertexId].x == 1)
			{
				vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
			}
			else if(Infor[VertexId].x == 2)
			{
				vs_color = vec4(1.0f, 0.4f, 0.4f, 1.0f);
			}
			else
			{
				vs_color = vec4(1.0f, 0.1f, 1.0f, 1.0f);
			}
#endif
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
	if(Cube == 4)
		Cube = 8;
#endif
}