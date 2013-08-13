#include                                <allegro5/allegro.h>
#include                                <string>
#include                                <sstream>
#include                                <iostream>

#define					PATH "saves/"

typedef	struct				mydata_s
{
  ALLEGRO_DISPLAY			*display;
  ALLEGRO_EVENT_QUEUE			*event_queue;
  bool					loop;
  int					x;
  int					y;
  ALLEGRO_COLOR				color;
  int					colorHex;
  std::string				path;
}					mydata_t;

void					init(mydata_t *d)
{
  assert(al_init());
  assert(d->display = al_create_display(500, 500));
  assert(al_install_keyboard());
  assert(d->event_queue = al_create_event_queue());
  al_register_event_source(d->event_queue, al_get_keyboard_event_source());
  d->loop = true;
  d->x = 0;
  d->y = 0;
}

bool					visited(mydata_t *d)
{
  std::ostringstream			convert;
  ALLEGRO_FILE				*file;

  d->path.clear();
  d->path = PATH;
  d->path += "chunk-";
  convert << d->x;
  d->path += convert.str();
  d->path += "_";
  convert.clear();
  convert.str("");
  convert << d->y;
  d->path += convert.str();
  d->path += ".ck";
  if (al_filename_exists(d->path.c_str()))
    {
      std::cout << d->path << " existe !" << std::endl;
      file = al_fopen(d->path.c_str(), "r");
      al_fread(file, &(d->colorHex), 4);
      std::cout << "vieille couleur : " << d->x << " " << d->y << " -- " << d->colorHex << std::endl;
      al_fclose(file);
      return true;
    }
  return false;
}

void					registerColor(mydata_t *d)
{
  ALLEGRO_FILE				*file;

  file = al_fopen(d->path.c_str(), "w");
  std::cout << "nouvelle couleur : " << d->path << " -- " << d->colorHex << std::endl;
  if (!file)
    {
      return;
    }
  al_fwrite(file, &(d->colorHex), 4);
  // al_fputc(file, d->colorHex);
  al_fclose(file);
  // al_fwrite32le(file, (int32_t)d->colorHex);
}

void					move(int x, int y, mydata_t *d)
{
  d->x += x;
  d->y += y;
  if (!visited(d))
    {
      d->colorHex = rand() % 16777215;
      registerColor(d);
    }
  d->color = al_map_rgb((d->colorHex >> 16) & 0xFF, (d->colorHex >> 8) & 0xFF, d->colorHex & 0xFF);
  al_clear_to_color(d->color);
  al_flip_display();
}

int					main()
{
  mydata_t				d;
  ALLEGRO_EVENT				ev;

  init(&d);
  move(0, 0, &d);
  while (d.loop)
    {
      al_wait_for_event(d.event_queue, &ev);
      if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
	  if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
	    d.loop = false;
	  else if (ev.keyboard.keycode == ALLEGRO_KEY_A)
	    {
	      move(-1, 0, &d);
	    }
	  else if (ev.keyboard.keycode == ALLEGRO_KEY_W)
	    {
	      move(0, -1, &d);
	    }
	  else if (ev.keyboard.keycode == ALLEGRO_KEY_D)
	    {
	      move(1, 0, &d);
	    }
	  else if (ev.keyboard.keycode == ALLEGRO_KEY_S)
	    {
	      move(0, 1, &d);
	    }
	}
    }
  return (0);
}
