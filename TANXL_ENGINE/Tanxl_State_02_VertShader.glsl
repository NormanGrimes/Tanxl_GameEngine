//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-07-12 14:55
// 修复起始页面存在一像素偏差的问题

#version 430

#define STATE_02_LAYER 0.2f //UI LAYER

layout (location = 1) in vec2 texCoord;

out vec4 vs_color;
out vec2 tc;
flat out int Cube;

void main(void)
{
	tc = texCoord;

	Cube = 11;

	for(int VertexId = 0; VertexId < 1; ++VertexId)
	{
		if      (gl_VertexID == VertexId * 6 + 0) 
		{ 
			gl_Position = vec4( -1.01f, -1.01f, STATE_02_LAYER, 1.0f);
		}
		else if (gl_VertexID == VertexId * 6 + 1) 
		{ 
			gl_Position = vec4(  1.01f, -1.01f, STATE_02_LAYER, 1.0f); 
		}
		else if (gl_VertexID == VertexId * 6 + 2) 
		{ 
			gl_Position = vec4( -1.01f,  1.01f, STATE_02_LAYER, 1.0f);
		}
		else if (gl_VertexID == VertexId * 6 + 3) 
		{ 
			gl_Position = vec4(  1.01f, -1.01f, STATE_02_LAYER, 1.0f); 
		}
		else if (gl_VertexID == VertexId * 6 + 4) 
		{
			gl_Position = vec4(  1.01f,  1.01f, STATE_02_LAYER, 1.0f);
		}
		else if (gl_VertexID == VertexId * 6 + 5) 
		{
			gl_Position = vec4( -1.01f,  1.01f, STATE_02_LAYER, 1.0f);
		}
	}
}