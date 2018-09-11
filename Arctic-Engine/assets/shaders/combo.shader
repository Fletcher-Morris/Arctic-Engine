#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
	gl_Position = vec4(position.x, position.y, position.z, 1.0);
	v_TexCoord = texCoord;
}



#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

vec3 colour;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor;
}