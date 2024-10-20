#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D text;     // Text texture (glyph)
uniform vec3 textColor;     // Text color

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r); // Sample the glyph texture
    FragColor = vec4(textColor, 1.0) * sampled; // Apply color
}
