#include			<iostream>

#include			"Archive.hpp"

int				main(void)
{
  std::string			map = "0123";
  int				width = 5, test = 2;
  std::ofstream			f1;

  if (!Archive::open(f1, "toto.dat"))
    return -1;

  Archive::serialize(f1, width);
  Archive::serialize(f1, map);
  Archive::serialize(f1, test);

  f1.close();

  std::ifstream			f2("toto.dat", std::ios::out | std::ios::binary);

  int				width1, test1;
  std::string			map1;

  Archive::unserialize(f2, width1);
  Archive::unserialize(f2, map1);
  Archive::unserialize(f2, test1);

  f2.close();

  std::cout << "Width : " << width1 << std::endl;
  std::cout << "Map Value : " << map1 << std::endl;
  std::cout << test1 << std::endl;

  return 0;
}
