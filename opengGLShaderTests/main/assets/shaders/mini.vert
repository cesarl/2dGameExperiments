/************************************/
/* ici nous retrecissons les vertex */
/* le rendu est miniaturise	    */
/************************************/

void		main()
{
  gl_Position = ftransform();
  gl_Position = vec4(gl_Position.xyz * 0.3, gl_Position.w);
  gl_FrontColor = gl_Color;
}
