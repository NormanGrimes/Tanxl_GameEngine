#version 430

//basic state Draw

layout (location=0) in vec3 position;
layout (location=1) in vec4 color;

out vec4 vs_color;

uniform int State[100];

uniform float MoveX;
uniform float MoveY;

uniform float SHeight;
uniform float SWidth;

void main(void)
{ 

//	if      (gl_VertexID == 0) gl_Position = vec4(  0.25 + MoveX, -0.25 + MoveY, 0.0, 1);//MIDDLE
//	else if (gl_VertexID == 1) gl_Position = vec4( -0.25 + MoveX, -0.25 + MoveY, 0.0, 1);
//	else if (gl_VertexID == 2) gl_Position = vec4(  0.25 + MoveX,  0.25 + MoveY, 0.0, 1);
//	else if (gl_VertexID == 3) gl_Position = vec4( -0.25 + MoveX, -0.25 + MoveY, 0.0, 1);
//	else if (gl_VertexID == 4) gl_Position = vec4( -0.25 + MoveX,  0.25 + MoveY, 0.0, 1);
//	else if (gl_VertexID == 5) gl_Position = vec4(  0.25 + MoveX,  0.25 + MoveY, 0.0, 1);


	float Height = 2.0f / SHeight;
	float Width  = 2.0f / SWidth;

	int counts = 0;

	float WidthMove = -((SWidth-1) / 2) * Width;
	float HeightMove = ((SHeight-1) / 2) * Height;
	for(int i = 0; i < SHeight * SWidth; i++)
	{

		if      (gl_VertexID == i * 6 + 0) 
		{ gl_Position = vec4(  Width / 2 + WidthMove, -Height / 2 + HeightMove, 0.0, 1.0); vs_color = vec4(1, 1, 0, 1);}
		else if (gl_VertexID == i * 6 + 1) 
		{ gl_Position = vec4( -Width / 2 + WidthMove, -Height / 2 + HeightMove, 0.0, 1.0); vs_color = vec4(1, 1, 0, 1);}
		else if (gl_VertexID == i * 6 + 2) 
		{ gl_Position = vec4(  Width / 2 + WidthMove,  Height / 2 + HeightMove, 0.0, 1.0); vs_color = vec4(1, 1, 0, 1);}
		else if (gl_VertexID == i * 6 + 3) 
		{ gl_Position = vec4( -Width / 2 + WidthMove, -Height / 2 + HeightMove, 0.0, 1.0); vs_color = vec4(1, 1, 0, 1);}
		else if (gl_VertexID == i * 6 + 4) 
		{ gl_Position = vec4( -Width / 2 + WidthMove,  Height / 2 + HeightMove, 0.0, 1.0); vs_color = vec4(1, 1, 0, 1);}
		else if (gl_VertexID == i * 6 + 5) 
		{ gl_Position = vec4(  Width / 2 + WidthMove,  Height / 2 + HeightMove, 0.0, 1.0); vs_color = vec4(1, 1, 0, 1);}

		WidthMove += Width;
		counts++;
		if(counts == SWidth)
		{
			counts = 0;
			WidthMove = -((SWidth-1) / 2) * Width;
			HeightMove -= Height;
		}
	}
}