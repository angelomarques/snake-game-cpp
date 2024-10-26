#version 330 core

out vec4 FragColor;
uniform vec4 color; // Pass color with alpha

void main()
{
    FragColor = color;  // Custom color
}
