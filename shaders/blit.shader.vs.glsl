#version 330
// Uniforms : data shared by every shader
in vec2 VertexPosition;

out vec2 uv;

void main(void)
{	
	uv = VertexPosition * 0.5 + 0.5;
	uv.y = 1 - uv.y;
	gl_Position = vec4(VertexPosition.xy, 0.0, 1.0);
}
