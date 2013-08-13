#include				<ctime>
#include				"MapManager.hh"

int					main()
{
  ALLEGRO_DISPLAY			*display;
  ALLEGRO_EVENT				ev;
  ALLEGRO_EVENT_QUEUE			*event_queue;
  bool					loop;

  loop = true;
  assert(al_init());
  assert(display = al_create_display(400, 400));
  assert(event_queue = al_create_event_queue());
  assert(al_install_keyboard());
  al_init_primitives_addon();
  al_register_event_source(event_queue, al_get_keyboard_event_source());

  MapManager				map(10, 10);

  srand(time(NULL));
  map.move(0, 0);
  while (loop)
    {
      al_wait_for_event(event_queue, &ev);
      if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
	  if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
	    loop = false;
	  else if (ev.keyboard.keycode == ALLEGRO_KEY_A)
	    {
	      map.move(-1, 0);
	    }
	  else if (ev.keyboard.keycode == ALLEGRO_KEY_W)
	    {
	      map.move(0, -1);
	    }
	  else if (ev.keyboard.keycode == ALLEGRO_KEY_D)
	    {
	      map.move(1, 0);
	    }
	  else if (ev.keyboard.keycode == ALLEGRO_KEY_S)
	    {
	      map.move(0, 1);
	    }
	}
    }
  return 0;
}
