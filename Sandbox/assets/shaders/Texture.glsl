// Basic Texture Shader

#type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TexCoord;
out vec2 v_ScreenPos;

void main()
{
	v_TexCoord = a_TexCoord;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
	v_ScreenPos = gl_Position.xy;
}

#type fragment
#version 460 core

layout(location = 0) out vec4 colour;

in vec2 v_TexCoord;
in vec2 v_ScreenPos;

uniform sampler2D u_Texture;
//uniform sampler2D u_Bayer8;

uniform float u_TexScale = 1.0;
uniform vec4 u_Colour;

void main()
{
	float dist = 1.f - distance(v_ScreenPos * .8f, vec2(0.f));
	dist = clamp(dist, 0.f, 1.f);
	dist = sqrt(dist);
	colour = texture(u_Texture, v_TexCoord * u_TexScale) * u_Colour * dist;
	//vec4 dither = vec4(texture2D(u_Bayer8, gl_FragCoord.xy / 8.0).r / 32.0 - (1.0 / 128.0));
	//colour += dither;

	//colour = vec4(v_TexCoord, 0.0, 1.0);
}