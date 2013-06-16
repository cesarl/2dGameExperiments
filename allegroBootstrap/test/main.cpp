#include				<iostream>
#include				"Logger.hpp"
#include				"ImageLoader.hpp"
#include				"MediaManager.hpp"
#include				"ResourceManager.hpp"
#include				<allegro5/allegro_image.h>

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
  al_init_image_addon();

  ILogger::setLogger(new ConsoleLogger);

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

  /////////////////////////
  // media manager tests //
  /////////////////////////
  MediaManager::getInstance().registerLoader(new ImageLoader, ".png,.jpg,.jpeg");
  Image img;
  img = ResourceManager::getInstance().get<Image>("stars.png");

  ILogger::log("Foo");
  ILogger::log("%d lapins dancent en %s", 5, "ronde");

  return 0;
}
