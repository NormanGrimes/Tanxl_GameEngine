//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-08-28 15:34
// 实例化测试版本顶点着色器

#version 430
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aOffset;

flat out int Cube;

out vec2 tc;
out vec4 vs_color;

void main()
{
    Cube = -1;
    vs_color = vec4(aColor, 1.0);
    gl_Position = vec4(aPos + aOffset, 0.0, 1.0);
}