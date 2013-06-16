#include				<iostream>
#include				"Logger.hpp"
#include				"SmartPointer.hpp"

// le delete ne fonctionne pas et provoqeu une boucle infinie
//#include				"Memory.hpp"

struct Test
{
  int t;
  int j;
};


int					main()
{

  ////////////////////
  // initialisation //
  ////////////////////

  al_init();

  ILogger::setLogger(new FileLogger);

  //////////
  // main //
  //////////

  std::cout << "coucou" << std::endl;
  Test *test = new Test;
  std::cout << "coucou" << std::endl;
  delete test;

  char *foo = new char[31];
  (void)foo;
  delete foo;

  ILogger::log("Foo");
  ILogger::log("%d lapins dancent en %s", 5, "ronde");

  return 0;
}
