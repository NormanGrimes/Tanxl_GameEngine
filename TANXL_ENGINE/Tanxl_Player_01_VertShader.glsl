//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-03-17 09:31
// 从顶点着色器中独立出此功能

#version 430

layout (location = 1) in vec2 texCoord;

layout (location = 2) uniform float Current_Move_LocationX;
layout (location = 3) uniform float Current_Move_LocationY;

layout (location = 4) uniform int SHeight;
layout (location = 5) uniform int SWidth;

in vec4 color;

out vec4 vs_color;
out vec2 tc;
flat out int Cube;

void main(void)
{
	tc = texCoord;
	
	float Height = 2.0f / SHeight;
	float Width  = 2.0f / SWidth;

	if      (gl_VertexID == 0) //MainMoveBlock 0.2F
	{
		gl_Position = vec4(  Width / 2 + Current_Move_LocationX, -Height / 2 + Current_Move_LocationY, 0.2f, 1.0f); 
		vs_color = vec4(0.9f, 0.8f, 1.0f, 1.0f);
		Cube = -1;
	}
	else if (gl_VertexID == 1)
	{
		gl_Position = vec4( -Width / 2 + Current_Move_LocationX, -Height / 2 + Current_Move_LocationY, 0.2f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = -1;
	}
	else if (gl_VertexID == 2)
	{
		gl_Position = vec4(  Width / 2 + Current_Move_LocationX,  Height / 2 + Current_Move_LocationY, 0.2f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = -1;
	}
	else if (gl_VertexID == 3)
	{
		gl_Position = vec4( -Width / 2 + Current_Move_LocationX, -Height / 2 + Current_Move_LocationY, 0.2f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = -1;
	}
	else if (gl_VertexID == 4)
	{
		gl_Position = vec4( -Width / 2 + Current_Move_LocationX,  Height / 2 + Current_Move_LocationY, 0.2f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = -1;
	}
	else if (gl_VertexID == 5)
	{
		gl_Position = vec4(  Width / 2 + Current_Move_LocationX,  Height / 2 + Current_Move_LocationY, 0.2f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = -1;
	}

	else if (gl_VertexID == 6)
	{
		gl_Position = vec4(  Width / 16 + 0.9f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 4;
	}
	else if (gl_VertexID == 7)
	{
		gl_Position = vec4( -Width / 16 + 0.9f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 4;
	}
	else if (gl_VertexID == 8)
	{
		gl_Position = vec4(  Width / 16 + 0.9f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 4;
	}
	else if (gl_VertexID == 9)
	{
		gl_Position = vec4( -Width / 16 + 0.9f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 4;
	}
	else if (gl_VertexID == 10)
	{
		gl_Position = vec4( -Width / 16 + 0.9f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 4;
	}
	else if (gl_VertexID == 11)
	{
		gl_Position = vec4(  Width / 16 + 0.9f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 4;
	}

	else if (gl_VertexID == 12)
	{
		gl_Position = vec4(  Width / 16 + 0.8f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 4;
	}
	else if (gl_VertexID == 13)
	{
		gl_Position = vec4( -Width / 16 + 0.8f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 4;
	}
	else if (gl_VertexID == 14)
	{
		gl_Position = vec4(  Width / 16 + 0.8f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 4;
	}
	else if (gl_VertexID == 15)
	{
		gl_Position = vec4( -Width / 16 + 0.8f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 4;
	}
	else if (gl_VertexID == 16)
	{
		gl_Position = vec4( -Width / 16 + 0.8f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 4;
	}
	else if (gl_VertexID == 17)
	{
		gl_Position = vec4(  Width / 16 + 0.8f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 4;
	}

	else if (gl_VertexID == 18)
	{
		gl_Position = vec4(  Width / 16 + 0.7f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 4;
	}
	else if (gl_VertexID == 19)
	{
		gl_Position = vec4( -Width / 16 + 0.7f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 4;
	}
	else if (gl_VertexID == 20)
	{
		gl_Position = vec4(  Width / 16 + 0.7f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 4;
	}
	else if (gl_VertexID == 21)
	{
		gl_Position = vec4( -Width / 16 + 0.7f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 4;
	}
	else if (gl_VertexID == 22)
	{
		gl_Position = vec4( -Width / 16 + 0.7f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 4;
	}
	else if (gl_VertexID == 23)
	{
		gl_Position = vec4(  Width / 16 + 0.7f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 4;
	}

	else if (gl_VertexID == 24)
	{
		gl_Position = vec4(  Width / 16 + 0.6f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 5;
	}
	else if (gl_VertexID == 25)
	{
		gl_Position = vec4( -Width / 16 + 0.6f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 5;
	}
	else if (gl_VertexID == 26)
	{
		gl_Position = vec4(  Width / 16 + 0.6f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 5;
	}
	else if (gl_VertexID == 27)
	{
		gl_Position = vec4( -Width / 16 + 0.6f, -Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 5;
	}
	else if (gl_VertexID == 28)
	{
		gl_Position = vec4( -Width / 16 + 0.6f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 5;
	}
	else if (gl_VertexID == 29)
	{
		gl_Position = vec4(  Width / 16 + 0.6f,  Height / 16 + 0.9f, 0.1f, 1.0f); 
		vs_color = vec4(0.9f, 1.0f, 1.0f, 1.0f);
		Cube = 5;
	}
}