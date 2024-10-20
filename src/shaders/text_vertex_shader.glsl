#version 330 core

layout (location = 0) in vec4 vertex; // Vertex attributes for a quad (position and texture coordinates)
out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0); // Project the 2D text quad to the screen
    TexCoords = vertex.zw; // Pass texture coordinates to fragment shader
}
