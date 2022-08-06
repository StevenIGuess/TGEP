#type vertex
#version 460 core

layout (location = 0) in vec3 aPos;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;


void main() 
{
    gl_Position = u_ViewProjection * u_Transform * vec4(aPos, 1.0);
} 
#type fragment
#version 460 core

out vec4 FragColor;
uniform vec4 u_Color;

void main()
{
    FragColor = u_Color;
}