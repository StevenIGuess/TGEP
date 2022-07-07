#version 330 core

out vec4 FragColor;

uniform vec3 lightColor;
uniform sampler2D fancyTextureL;

in vec2 TexCoord;

void main()
{
	FragColor = texture(fancyTextureL, TexCoord);
}