uniform vec3 scale;

void main()
{
  vec4 vertex = gl_Vertex;
  vertex.x *= scale.x;
  vertex.y *= scale.y;
  vertex.z *= scale.z;
  gl_Position = gl_ModelViewProjectionMatrix * vertex;
  gl_FrontColor = gl_Color;
  gl_TexCoord[0] = gl_MultiTexCoord0;
}