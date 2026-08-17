//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2024-05-28 14:04

#version 430

#define PLAYER_UI_02_SPEAKER_LAYER 0.20f
#define PLAYER_UI_02_BACKGRO_LAYER 0.22f

layout (location = 1) in vec2 texCoord;

layout (location = 2) uniform int Character_Texture;
layout (location = 3) uniform int Data_BackGround;

out vec4 vs_color;
out vec2 tc;
flat out int Cube;

void main(void)
{
	tc = texCoord;

	if(gl_VertexID < 6)
	{
		Cube = Data_BackGround;
		if (gl_VertexID == 0)
		{
			gl_Position = vec4(  1.0f, -1.0f, PLAYER_UI_02_BACKGRO_LAYER, 1.0f); 
			vs_color = vec4(0.9f, 0.1f, 1.0f, 1.0f);
		}
		else if (gl_VertexID == 1)
		{
			gl_Position = vec4( -1.0f, -1.0f, PLAYER_UI_02_BACKGRO_LAYER, 1.0f); 
			vs_color = vec4(0.9f, 0.1f, 1.0f, 1.0f);
		}
		else if (gl_VertexID == 2)
		{
			gl_Position = vec4(  1.0f, -0.5f, PLAYER_UI_02_BACKGRO_LAYER, 1.0f); 
			vs_color = vec4(0.9f, 0.1f, 1.0f, 1.0f);
		}
		else if (gl_VertexID == 3)
		{
			gl_Position = vec4( -1.0f, -1.0f, PLAYER_UI_02_BACKGRO_LAYER, 1.0f); 
			vs_color = vec4(0.9f, 0.1f, 1.0f, 1.0f);
		}
		else if (gl_VertexID == 4)
		{
			gl_Position = vec4( -1.0f, -0.5f, PLAYER_UI_02_BACKGRO_LAYER, 1.0f); 
			vs_color = vec4(0.9f, 0.1f, 1.0f, 1.0f);
		}
		else if (gl_VertexID == 5)
		{
			gl_Position = vec4(  1.0f, -0.5f, PLAYER_UI_02_BACKGRO_LAYER, 1.0f); 
			vs_color = vec4(0.9f, 0.1f, 1.0f, 1.0f);
		}
	}
	else
	{
		Cube = Character_Texture;
		if (gl_VertexID == 6)
		{
			gl_Position = vec4( -1.2f, -1.3f, PLAYER_UI_02_SPEAKER_LAYER, 1.0f);
			vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
		}
		else if (gl_VertexID == 7)
		{
			gl_Position = vec4( -0.4f, -1.3f, PLAYER_UI_02_SPEAKER_LAYER, 1.0f);
			vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
		}
		else if (gl_VertexID == 8)
		{
			gl_Position = vec4( -1.2f, -0.3f, PLAYER_UI_02_SPEAKER_LAYER, 1.0f);
			vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
		}
		else if (gl_VertexID == 9)
		{
			gl_Position = vec4( -0.4f, -1.3f, PLAYER_UI_02_SPEAKER_LAYER, 1.0f);
			vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
		}
		else if (gl_VertexID == 10)
		{
			gl_Position = vec4( -0.4f, -0.3f, PLAYER_UI_02_SPEAKER_LAYER, 1.0f);
			vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
		}
		else if (gl_VertexID == 11)
		{
			gl_Position = vec4( -1.2f, -0.3f, PLAYER_UI_02_SPEAKER_LAYER, 1.0f);
			vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0f);
		}
	}
}