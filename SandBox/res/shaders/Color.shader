#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord; // Take texture coordinates

out vec2 v_TexCoord; // transfer texture coordinates to fragment shader

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord; // Receive texture coordinates from vertex shader

uniform vec4 u_Color;

void main()
{
	color = u_Color;
};