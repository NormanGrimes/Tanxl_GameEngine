#version 430

in vec4 vs_color;
out vec4 color;

//basic state Color

uniform float SinCurrentTime;
uniform float CosCurrentTime;

void main(void)
{
	color = vs_color;
}