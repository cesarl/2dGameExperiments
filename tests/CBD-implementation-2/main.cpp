#include                                <allegro5/allegro.h>
#include				"Entity.hh"
#include				"Component.hh"
#include				"ComponentTypes.hh"

static ALLEGRO_DISPLAY			*init(int width, int height)
{
  ALLEGRO_DISPLAY			*display;

  assert(al_init());
  assert(display = al_create_display(width, height));
  return display;
}

int					main()
{
  Entity				entity[100];
  Entity				text;
  ALLEGRO_DISPLAY			*display = init(50 * 20, 50 * 20);
  int					count;
  int					from;

  int i = 0;
  while (i < 100)
    {
      from = rand() % 8 * 8;
      SPRITE(&entity[i])->config(8, 50, 50, from , 8, from, 0.09);
      IMAGE(&entity[i])->setBitmap("tetris-sprite.jpg");
      MOVE(&entity[i])->vx = rand() % 6 - 3;
      MOVE(&entity[i])->vy = rand() % 6 - 3;
      MOVE(&entity[i])->gravityY = 0.1;
      POSITION(&entity[i])->setPos(500, 500);
      VISIBILITY(&entity[i])->fadeOut(0.01, rand() % 8 + 1);
      ROTATION(&entity[i])->angle = rand() % 200 / 100;
      ++i;
    }

  *TEXT(&text) = "Yeah";
  TEXT(&text)->align = ALLEGRO_ALIGN_CENTER;
  TEXT(&text)->color = al_map_rgb(255, 0, 255);
  TEXT(&text)->setFont("LilitaOne-Regular.ttf", 80);
  POSITION(&text)->setPos(500, 300);

  count = 0;
  while (count < 220)
    {
      i = 0;
      al_clear_to_color(al_map_rgb(0,0,0));
      while (i < 100)
	{
	  entity[i].update();
	  entity[i].draw();
	  ROTATION(&entity[i])->angle += 0.1;
	  ++i;
	}
      if (count == 30)
	*TEXT(&text) += " mon pote";
      text.draw();
      al_flip_display();
      al_rest(0.02);
      ++count;
    }
  al_destroy_display(display);
  return 0;
}
