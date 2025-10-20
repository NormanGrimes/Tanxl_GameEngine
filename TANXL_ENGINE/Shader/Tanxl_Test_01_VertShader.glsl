//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-08-28 15:34
// 实例化测试版本顶点着色器
// 实例化绘制的颜色设置改为着色器实现

#version 430

#define TEST_01_LAYER 0.2f //UI LAYER

layout (location = 0) in vec2 Pos;
layout (location = 2) in vec3 Offset;
layout (location = 3) in vec2 texCoord;

flat out int Cube;

out vec2 tc;
out vec4 vs_color;

void main()
{
    tc = texCoord;
    Cube = 32;

    if(Offset.z == 0.0f)
    {
        vs_color = vec4(0.1f, 1.0f, 1.0f, 1.0);
        //Cube = 1;
    }
    else
    {
        vs_color = vec4(1.0f, 1.0f, 0.1f, 1.0);
        //Cube = 2;
    }

    gl_Position = vec4(Pos.x + Offset.x, Pos.y + Offset.y, TEST_01_LAYER, 1.0);
}