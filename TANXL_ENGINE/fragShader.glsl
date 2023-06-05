//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-01-16 10:30
// 纹理功能调试中

#version 430

in vec4 vs_color;
in vec2 tc;
out vec4 color;
flat in int Current_Cube;

//uniform mat4 mv_matrix;
//uniform mat4 proj_matrix;
layout (binding=0) uniform sampler2D samp;

void main(void)
{	
	if(Current_Cube < 500)
		color = vs_color;
	else
		color = texture(samp, tc);
}
