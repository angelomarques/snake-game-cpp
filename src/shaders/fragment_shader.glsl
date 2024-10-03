#version 330 core
out vec4 FragColor;

uniform vec3 customColor; // Color for the rectangle

void main()
{
    FragColor = vec4(customColor, 1.0);  // Custom color
}
