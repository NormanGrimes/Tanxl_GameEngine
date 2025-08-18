//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-07-12 14:55
// �޸���ʼҳ�����һ����ƫ�������
// �����Ÿ�Ϊ�Զ���ȡ
// ������Ϸ״̬ͳһ����
// �����·�����Ϸ״̬��
// ͨ����Ϸ״̬���ƻ�������
// ʹ���ޱ��������滻֮ǰ��Ԥ��Ⱦ�ı���
// ���ӳ�ʼ���汳���Ļ���
// ȥ����Ϸ��Ϣ������Ʋ���
// �ƶ���ʼ���汳�����Ʋ��ֵ�ʵ������ɫ��

#version 430

#define STATE_02_LAYER 0.2f //UI LAYER

layout (location = 1) in vec2 texCoord;
layout (location = 2) uniform int Image_Id;

out vec4 vs_color;
out vec2 tc;
flat out int Cube;

void main(void)
{
	tc = texCoord;

	for(int VertexId = 0; VertexId < 1; ++VertexId)
	{
		if      (gl_VertexID == 0)
		{
			Cube = Image_Id;
			gl_Position = vec4( -0.9f,  0.0f, STATE_02_LAYER, 1.0f);
		}
		else if (gl_VertexID == 1)
		{
			Cube = Image_Id;
			gl_Position = vec4(  0.9f,  0.0f, STATE_02_LAYER, 1.0f);
		}
		else if (gl_VertexID == 2)
		{
			Cube = Image_Id;
			gl_Position = vec4( -0.9f,  0.51f, STATE_02_LAYER, 1.0f);
		}
		else if (gl_VertexID == 3)
		{
			Cube = Image_Id;
			gl_Position = vec4(  0.9f,  0.0f, STATE_02_LAYER, 1.0f);
		}
		else if (gl_VertexID == 4)
		{
			Cube = Image_Id;
			gl_Position = vec4(  0.9f,  0.51f, STATE_02_LAYER, 1.0f);
		}
		else if (gl_VertexID == 5)
		{
			Cube = Image_Id;
			gl_Position = vec4( -0.9f,  0.51f, STATE_02_LAYER, 1.0f);
		}
	}
}