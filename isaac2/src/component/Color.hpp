#ifndef				__COLOR_COMPONENT_HPP__
# define			__COLOR_COMPONENT_HPP__

struct				Color
{
  float				r;
  float				g;
  float				b;
  float				a;

  Color(float ar = 1.0f,
	float ag = 1.0f,
	float ab = 1.0f,
	float aa = 1.0f) :
    r(ar),
    g(ag),
    b(ab),
    a(aa)
  {}
  void				set(float ar = 1.0f,
				    float ag = 1.0f,
				    float ab = 1.0f,
				    float aa = 1.0f)
  {
    this->r = ar;
    this->g = ag;
    this->b = ab;
    this->a = aa;
  }
};

#endif				// __COLOR_COMPONENT_HPP__
