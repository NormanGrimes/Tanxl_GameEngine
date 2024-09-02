//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-03-17 09:31
// �Ӷ�����ɫ���ж������˹���
// ��Ϸ���������Զ������깦��
// ��ͨ��ͳһ����������ʾ������ֵͼ������
// ��С��ҷ���ߴ�
// ֧��ָ����������ֵ������
// ֧���Զ�������ֵ��ͼƬ���
// �Ƴ�����δʹ�ñ���
// ���Ӻ���Ƹò������ж���ľ���
// ���Ӳ���״̬ͳһ����
// �����ƶ�����״̬����ҷ�����Ʒ���
// ���������ƶ����������
// �Ż���������������

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

	if      (gl_VertexID == 0) //MainMoveBlock 0.2F
	{
		vs_color = vec4(0.9f, 0.8f, 1.0f, 1.0f);
		gl_Position = vec4(  Width / 3 + Current_Move_LocationX, -Height / 3 + Current_Move_LocationY, PLAYER_01_LAYER, 1.0f);

		if(Insert_Status == 0)
			Cube = 6;
		else if(Insert_Status == 1)
			Cube = 8;
		else if(Insert_Status == 2)
			Cube = 7;
		else if(Insert_Status == 3)
			Cube = 5;
	}
	else if (gl_VertexID == 1)
	{
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		gl_Position = vec4( -Width / 3 + Current_Move_LocationX, -Height / 3 + Current_Move_LocationY, PLAYER_01_LAYER, 1.0f);

		if(Insert_Status == 0)
			Cube = 6;
		else if(Insert_Status == 1)
			Cube = 8;
		else if(Insert_Status == 2)
			Cube = 7;
		else if(Insert_Status == 3)
			Cube = 5;
	}
	else if (gl_VertexID == 2)
	{
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		gl_Position = vec4(  Width / 3 + Current_Move_LocationX,  Height / 3 + Current_Move_LocationY, PLAYER_01_LAYER, 1.0f);

		if(Insert_Status == 0)
			Cube = 6;
		else if(Insert_Status == 1)
			Cube = 8;
		else if(Insert_Status == 2)
			Cube = 7;
		else if(Insert_Status == 3)
			Cube = 5;
	}
	else if (gl_VertexID == 3)
	{
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		gl_Position = vec4( -Width / 3 + Current_Move_LocationX, -Height / 3 + Current_Move_LocationY, PLAYER_01_LAYER, 1.0f);

		if(Insert_Status == 0)
			Cube = 6;
		else if(Insert_Status == 1)
			Cube = 8;
		else if(Insert_Status == 2)
			Cube = 7;
		else if(Insert_Status == 3)
			Cube = 5;
	}
	else if (gl_VertexID == 4)
	{
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		gl_Position = vec4( -Width / 3 + Current_Move_LocationX,  Height / 3 + Current_Move_LocationY, PLAYER_01_LAYER, 1.0f);

		if(Insert_Status == 0)
			Cube = 6;
		else if(Insert_Status == 1)
			Cube = 8;
		else if(Insert_Status == 2)
			Cube = 7;
		else if(Insert_Status == 3)
			Cube = 5;
	}
	else if (gl_VertexID == 5)
	{
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		gl_Position = vec4(  Width / 3 + Current_Move_LocationX,  Height / 3 + Current_Move_LocationY, PLAYER_01_LAYER, 1.0f);

		if(Insert_Status == 0)
			Cube = 6;
		else if(Insert_Status == 1)
			Cube = 8;
		else if(Insert_Status == 2)
			Cube = 7;
		else if(Insert_Status == 3)
			Cube = 5;
	}

	else if (gl_VertexID == 6)
	{
		gl_Position = vec4(  Width / 16 + Begin_Location_X, -Height / 16 + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 10;
	}
	else if (gl_VertexID == 7)
	{
		gl_Position = vec4( -Width / 16 + Begin_Location_X, -Height / 16 + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 10;
	}
	else if (gl_VertexID == 8)
	{
		gl_Position = vec4(  Width / 16 + Begin_Location_X,  Height / 16 + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 10;
	}
	else if (gl_VertexID == 9)
	{
		gl_Position = vec4( -Width / 16 + Begin_Location_X, -Height / 16 + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 10;
	}
	else if (gl_VertexID == 10)
	{
		gl_Position = vec4( -Width / 16 + Begin_Location_X,  Height / 16 + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 10;
	}
	else if (gl_VertexID == 11)
	{
		gl_Position = vec4(  Width / 16 + Begin_Location_X,  Height / 16 + Begin_Location_Y, PLAYER_01_LAYER, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 10;
	}

	for(int i = 2, j = 2; i < Health_Length; i++, j++)
	{
		float LineSpace = (i - 1) / 4 * Direct_Margin;

		if (gl_VertexID == i * 6 + 0)
		{
			gl_Position = vec4(  Width / 16 + Begin_Location_X + Direct_Margin * (j - 1), -Height / 16 + Begin_Location_Y - LineSpace, PLAYER_01_LAYER, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 9;
		}
		else if (gl_VertexID == i * 6 + 1)
		{
			gl_Position = vec4( -Width / 16 + Begin_Location_X + Direct_Margin * (j - 1), -Height / 16 + Begin_Location_Y - LineSpace, PLAYER_01_LAYER, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 9;
		}
		else if (gl_VertexID == i * 6 + 2)
		{
			gl_Position = vec4(  Width / 16 + Begin_Location_X + Direct_Margin * (j - 1),  Height / 16 + Begin_Location_Y - LineSpace, PLAYER_01_LAYER, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 9;
		}
		else if (gl_VertexID == i * 6 + 3)
		{
			gl_Position = vec4( -Width / 16 + Begin_Location_X + Direct_Margin * (j - 1), -Height / 16 + Begin_Location_Y - LineSpace, PLAYER_01_LAYER, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 9;
		}
		else if (gl_VertexID == i * 6 + 4)
		{
			gl_Position = vec4( -Width / 16 + Begin_Location_X + Direct_Margin * (j - 1),  Height / 16 + Begin_Location_Y - LineSpace, PLAYER_01_LAYER, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 9;
		}
		else if (gl_VertexID == i * 6 + 5)
		{
			gl_Position = vec4(  Width / 16 + Begin_Location_X + Direct_Margin * (j - 1),  Height / 16 + Begin_Location_Y - LineSpace, PLAYER_01_LAYER, 1.0f); 
			vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
			Cube = 9;
		}

		if(i % 4 == 0)
			j -= 4;
	}
}