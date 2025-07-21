//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-09-22 16:27
// 字体变换矩阵使用固定位置

#version 430

layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
layout (location = 4) uniform mat4 projection;

out vec2 TexCoords;

void main()
{
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
}