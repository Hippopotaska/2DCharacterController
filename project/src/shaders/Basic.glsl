#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 u_ModelViewProjection;

out vec2 vTexCoord;

void main()
{
    gl_Position = u_ModelViewProjection * position;
    vTexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 vTexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, vTexCoord);
    color = texColor * u_Color;
};