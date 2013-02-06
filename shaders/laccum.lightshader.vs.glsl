#version 330

in vec2 VertexPosition;

out vec2 uvs;

void main()
{
  uvs = VertexPosition * 0.5 + 0.5;
  gl_Position = vec4(VertexPosition.xy, 0.0, 1.0);
}
