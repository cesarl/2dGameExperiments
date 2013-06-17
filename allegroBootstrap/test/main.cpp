#include				<iostream>
#include				"Logger.hpp"
#include				"ImageLoader.hpp"
#include				"MediaManager.hpp"
#include				"ResourceManager.hpp"
#include				<exception>
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
  try
    {
      MediaManager::getInstance().registerLoader(new ImageLoader, ".jpg,.png,.jpeg");
      MediaManager::getInstance().addSearchPath("./assets/imgs/");

      ImagePtr img;
      img = (ResourceManager::getInstance().get<Image>("stars.png"));
      if (!img)
	{
	  ILogger::log("L'image n'est pas encore chargee");
	  img = MediaManager::getInstance().load<Image>("stars.png");
	  img->sayHello();
	  ILogger::log("Foo");
	  ILogger::log("%d lapins dancent en %s", 5, "ronde");
	}
    }
  catch (const std::exception &e)
    {
      ILogger::log(e.what());
    }
  return 0;
}
