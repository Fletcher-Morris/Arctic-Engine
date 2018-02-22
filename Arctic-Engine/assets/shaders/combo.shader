#shader vertex
#version 400 core
layout(location = 0) in vec4 position;

void main()
{
	gl_Position = position;
}

#shader fragment
#version 400 core
out vec4 color;

void main()
{
	color = vec4(0.8f, 0.2f, 0.8f, 1.0f);
}