#version 330 core

layout(location = 0) in vec2 aPos;  // Input vertex position (2D)

uniform mat4 model;  // Model matrix for transforming the 2D object

void main()
{
    gl_Position = model * vec4(aPos, 0.0, 1.0);  // Transform the vertex position
}
