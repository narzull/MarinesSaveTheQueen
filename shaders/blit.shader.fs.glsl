#version 330

in vec2 uv;

uniform sampler2D diffuseTexture;

out vec4  Color;

void main(void)
{
	vec3 diffuse = texture(diffuseTexture, uv).rgb;
	Color = vec4(diffuse, 1.0);
}
