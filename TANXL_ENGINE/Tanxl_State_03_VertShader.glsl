//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-07-24 09:34

#version 430

#define STATE_03_LAYER 0.1f //PAGE SWITCH LAYER

layout (location = 1) in vec2 texCoord;
layout (location = 2) uniform int Draw_Status;

out vec4 vs_color;
out vec2 tc;
flat out int Cube;

void main(void)
{
	Cube = -1;
	tc = texCoord;

	float Status_0 = 0.0f;

	if(Draw_Status <= 100)
	{
		Status_0 = Draw_Status * 0.01f;
	}
	else
	{
		Status_0 = 1.0f - (Draw_Status - 100) * 0.01f;
	}

	int counts = 0;

	float Line_Length = 0.25f;// 1/4

	float WidthMove  = - 3 * Line_Length;
	float HeightMove =   3 * Line_Length;

	for(int VertexId = 0; VertexId < 16; ++VertexId)
	{
		vs_color = vec4(0.8f, 0.8f, 0.7f, Status_0);

		if      (gl_VertexID == VertexId * 6 + 0) 
		{
			gl_Position = vec4( -Line_Length + WidthMove, -Line_Length + HeightMove, STATE_03_LAYER, 1.0f);
		}
		else if (gl_VertexID == VertexId * 6 + 1) 
		{
			gl_Position = vec4(  Line_Length + WidthMove, -Line_Length + HeightMove, STATE_03_LAYER, 1.0f); 
		}
		else if (gl_VertexID == VertexId * 6 + 2) 
		{
			gl_Position = vec4( -Line_Length + WidthMove,  Line_Length + HeightMove, STATE_03_LAYER, 1.0f);
		}
		else if (gl_VertexID == VertexId * 6 + 3) 
		{
			gl_Position = vec4(  Line_Length + WidthMove, -Line_Length + HeightMove, STATE_03_LAYER, 1.0f); 
		}
		else if (gl_VertexID == VertexId * 6 + 4) 
		{
			gl_Position = vec4(  Line_Length + WidthMove,  Line_Length + HeightMove, STATE_03_LAYER, 1.0f);
		}
		else if (gl_VertexID == VertexId * 6 + 5) 
		{
			gl_Position = vec4( -Line_Length + WidthMove,  Line_Length + HeightMove, STATE_03_LAYER, 1.0f);
		}

		WidthMove += Line_Length * 2;
		counts++;
		if(counts == 4)
		{
			counts = 0;
			WidthMove = -3 * Line_Length;
			HeightMove -= 2 * Line_Length;
		}
	}
}