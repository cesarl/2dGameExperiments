/* void main() */
/* { */
/*   gl_Position = ftransform(); */
/*   gl_TexCoord[0] = gl_MultiTexCoord0; */
/* } */


void main()
{
  gl_FrontColor = gl_Color;
  gl_TexCoord[0] = gl_MultiTexCoord0;
  gl_Position = ftransform();
}
