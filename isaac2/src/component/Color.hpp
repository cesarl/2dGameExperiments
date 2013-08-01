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

  Color(const Color& other)
    : r(other.r)
    , g(other.g)
    , b(other.b)
    , a(other.a)
  {}

  Color				&operator=(const Color& other)
  {
    this->r = other.r;
    this->g = other.g;
    this->b = other.b;
    this->a = other.a;
    return (*this);
  }

  Color				&operator+=(const Color& other)
  {
    this->r += other.r;
    this->g += other.g;
    this->b += other.b;
    this->a += other.a;
    return (*this);
  }

  Color				&operator-=(const Color& other)
  {
    this->r -= other.r;
    this->g -= other.g;
    this->b -= other.b;
    this->a -= other.a;
    return (*this);
  }

  Color				&operator*=(const Color& other)
  {
    this->r *= other.r;
    this->g *= other.g;
    this->b *= other.b;
    this->a *= other.a;
    return (*this);
  }

  Color				&operator/=(const Color& other)

  {
    this->r /= other.r;
    this->g /= other.g;
    this->b /= other.b;
    this->a /= other.a;
    return (*this);
  }



  template			<typename T>
  Color				&operator=(T other)
  {
    this->r = other;
    this->g = other;
    this->b = other;
    this->a = other;
    return (*this);
  }

  template			<typename T>
  Color				&operator+=(T other)
  {
    this->r += other;
    this->g += other;
    this->b += other;
    this->a += other;
    return (*this);
  }

  template			<typename T>
  Color				&operator-=(T other)
  {
    this->r -= other;
    this->g -= other;
    this->b -= other;
    this->a -= other;
    return (*this);
  }

  template			<typename T>
  Color				&operator*=(T other)
  {
    this->r *= other;
    this->g *= other;
    this->b *= other;
    this->a *= other;
    return (*this);
  }

  template			<typename T>
  Color				&operator/=(T other)
  {
    this->r /= other;
    this->g /= other;
    this->b /= other;
    this->a /= other;
    return (*this);
  }

};

template			<typename T>
  Color				operator+(const Color& left, T right)
  {
    Color			tmp(left);

    tmp += right;
    return (tmp);
  }

template			<typename T>
  Color				operator-(const Color& left, T right)
  {
    Color			tmp(left);

    tmp -= right;
    return (tmp);
  }

template			<typename T>
  Color				operator*(const Color& left, T right)
  {
    Color			tmp(left);

    tmp *= right;
    return (tmp);
  }

template			<typename T>
  Color				operator/(const Color& left, T right)
  {
    Color			tmp(left);

    tmp /= right;
    return (tmp);
  }

#endif				// __COLOR_COMPONENT_HPP__
