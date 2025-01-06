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
// ���Ӻ���Ƹò������ж���ľ���
// �޸�������Ʒ�������෴������
// ���Ӹ����¼����Ʋ�ͬ������趨
// �Ƴ����÷�����ɫ����
// �Ƴ�ʵ����������ع���

#version 430

#define STATE_01_LAYER 0.4f

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

	float WidthMove  = -(SWidth + PreLoads - 1) * Width;
	float HeightMove = (SHeight + PreLoads - 1) * Height;

	for(VertexId = 0; VertexId < State_Datas; ++VertexId)//MAP LAYER 0.3f
	{
		if      (gl_VertexID == VertexId * 6 + 0) 
		{ 
			gl_Position = vec4( -Width + WidthMove + StateMoveX, 
							    -Height + HeightMove + StateMoveY, STATE_01_LAYER, 1.0f);

			if		(int(Infor[VertexId].y) == 2)
				Cube = 5;
			else if	(int(Infor[VertexId].y) == 3)
				Cube = 6;
			else
				Cube = int(Infor[VertexId].x);
		}
		else if (gl_VertexID == VertexId * 6 + 1) 
		{ 
			gl_Position = vec4(  Width + WidthMove + StateMoveX,
			                    -Height + HeightMove + StateMoveY, STATE_01_LAYER, 1.0f); 

			if		(int(Infor[VertexId].y) == 2)
				Cube = 5;
			else if	(int(Infor[VertexId].y) == 3)
				Cube = 6;
			else
				Cube = int(Infor[VertexId].x);
		}
		else if (gl_VertexID == VertexId * 6 + 2) 
		{ 
			gl_Position = vec4( -Width + WidthMove + StateMoveX,
			                     Height + HeightMove + StateMoveY, STATE_01_LAYER, 1.0f);
			
			if		(int(Infor[VertexId].y) == 2)
				Cube = 5;
			else if	(int(Infor[VertexId].y) == 3)
				Cube = 6;
			else
				Cube = int(Infor[VertexId].x);
		}
		else if (gl_VertexID == VertexId * 6 + 3) 
		{ 
			gl_Position = vec4(  Width + WidthMove + StateMoveX,
			                    -Height + HeightMove + StateMoveY, STATE_01_LAYER, 1.0f); 
			
			if		(int(Infor[VertexId].y) == 2)
				Cube = 5;
			else if	(int(Infor[VertexId].y) == 3)
				Cube = 6;
			else
				Cube = int(Infor[VertexId].x);
		}
		else if (gl_VertexID == VertexId * 6 + 4) 
		{
			gl_Position = vec4(  Width + WidthMove + StateMoveX,
			                     Height + HeightMove + StateMoveY, STATE_01_LAYER, 1.0f);
			
			if		(int(Infor[VertexId].y) == 2)
				Cube = 5;
			else if	(int(Infor[VertexId].y) == 3)
				Cube = 6;
			else
				Cube = int(Infor[VertexId].x);
		}
		else if (gl_VertexID == VertexId * 6 + 5) 
		{
			gl_Position = vec4( -Width + WidthMove + StateMoveX,
			                     Height + HeightMove + StateMoveY, STATE_01_LAYER, 1.0f);
			
			if		(int(Infor[VertexId].y) == 2)
				Cube = 5;
			else if	(int(Infor[VertexId].y) == 3)
				Cube = 6;
			else
				Cube = int(Infor[VertexId].x);
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