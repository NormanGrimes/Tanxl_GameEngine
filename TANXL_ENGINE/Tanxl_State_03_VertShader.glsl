//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-07-24 09:34
// 根据中间帧个数动态绘制
// 过渡页面增加顶点个数并细化效果

#version 430

#define STATE_03_LAYER 0.1f //PAGE SWITCH LAYER

layout (location = 1) in vec2 texCoord;
layout (location = 2) uniform int Draw_Status;
layout (location = 3) uniform int Max_Status;

out vec4 vs_color;
out vec2 tc;
flat out int Cube;

void main(void)
{
	Cube = -1;
	tc = texCoord;

	float Status_0 = 0.0f;

	if(Draw_Status <= Max_Status / 2)
		Status_0 = Draw_Status * (2.0f / Max_Status);
	else
		Status_0 = 1.0f - (Draw_Status - 100) * (2.0f / Max_Status);

	int counts = 0;

	float Line_Length = 0.20f;// 1/5

	float WidthMove  = - 4 * Line_Length;
	float HeightMove =   4 * Line_Length;

	for(int VertexId = 0; VertexId < 25; ++VertexId)
	{
		if      (gl_VertexID == VertexId * 6 + 0) 
		{
			gl_Position = vec4( -Line_Length + WidthMove, -Line_Length + HeightMove, STATE_03_LAYER, 1.0f);
			if(mod(float(VertexId), 2.0f) == 0.0f)
				vs_color = vec4(0.7f, 1.0f, 1.0f, Status_0);
			else
				vs_color = vec4(1.0f, 1.0f, 0.7f, Status_0);
		}
		else if (gl_VertexID == VertexId * 6 + 1) 
		{
			gl_Position = vec4(  Line_Length + WidthMove, -Line_Length + HeightMove, STATE_03_LAYER, 1.0f);
			if(mod(float(VertexId), 2.0f) == 0.0f)
				vs_color = vec4(0.7f, 1.0f, 1.0f, Status_0);
			else
				vs_color = vec4(1.0f, 1.0f, 0.7f, Status_0);
		}
		else if (gl_VertexID == VertexId * 6 + 2) 
		{
			gl_Position = vec4( -Line_Length + WidthMove,  Line_Length + HeightMove, STATE_03_LAYER, 1.0f);
			if(mod(float(VertexId), 2.0f) == 0.0f)
				vs_color = vec4(0.7f, 1.0f, 1.0f, Status_0);
			else
				vs_color = vec4(1.0f, 1.0f, 0.7f, Status_0);
		}
		else if (gl_VertexID == VertexId * 6 + 3) 
		{
			gl_Position = vec4(  Line_Length + WidthMove, -Line_Length + HeightMove, STATE_03_LAYER, 1.0f);
			if(mod(float(VertexId), 2.0f) == 0.0f)
				vs_color = vec4(0.7f, 1.0f, 1.0f, Status_0);
			else
				vs_color = vec4(1.0f, 1.0f, 0.7f, Status_0);
		}
		else if (gl_VertexID == VertexId * 6 + 4) 
		{
			gl_Position = vec4(  Line_Length + WidthMove,  Line_Length + HeightMove, STATE_03_LAYER, 1.0f);
			if(mod(float(VertexId), 2.0f) == 0.0f)
				vs_color = vec4(0.7f, 1.0f, 1.0f, Status_0);
			else
				vs_color = vec4(1.0f, 1.0f, 0.7f, Status_0);
		}
		else if (gl_VertexID == VertexId * 6 + 5) 
		{
			gl_Position = vec4( -Line_Length + WidthMove,  Line_Length + HeightMove, STATE_03_LAYER, 1.0f);
			if(mod(float(VertexId), 2.0f) == 0.0f)
				vs_color = vec4(0.7f, 1.0f, 1.0f, Status_0);
			else
				vs_color = vec4(1.0f, 1.0f, 0.7f, Status_0);
		}

		WidthMove += Line_Length * 2;
		counts++;
		if(counts == 5)
		{
			counts = 0;
			WidthMove = -4 * Line_Length;
			HeightMove -= 2 * Line_Length;
		}
	}
}