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
  al_create_display(300, 300);

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

      MediaManager::getInstance().load<Image>("stars.png");

      ImagePtr img = ResourceManager::getInstance().get<Image>("stars.png");
      ImagePtr img1 = ResourceManager::getInstance().get<Image>("stars.png");

      img->draw();
      ILogger::log("Foo");
      ILogger::log("%d lapins dancent en %s", 5, "ronde");
      al_flip_display();
    }
  catch (const std::exception &e)
    {
      ILogger::log(e.what());
    }
  return 0;
}
