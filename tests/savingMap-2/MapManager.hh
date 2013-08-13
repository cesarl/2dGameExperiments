#ifndef				__MAP_MANAGER_HH__
# define			__MAP_MANAGER_HH__

#include			<string>
#include			<sstream>
#include			<iostream>
#include			<vector>
#include			<allegro5/allegro.h>
#include			<allegro5/allegro_native_dialog.h>
#include			<allegro5/allegro_primitives.h>

#include			"Entity.hh"

typedef struct			s_tile
{
  int				x;
  int				y;
  int				hexColor;
  ALLEGRO_COLOR			color;
  bool				active;
}				t_tile;

#define				FILEPREFIX "saves/chunk"

class				MapManager
{
public:
  MapManager(int width, int height);
  ~MapManager();
public:
  void				move(int x, int y);
  void				draw();
  bool				readExistingWorldChunk();
  void				createNewWorldChunk();
private:
  int				cellSize_;
  int				x_;
  int				y_;
  int				width_;
  int				height_;
  std::ostringstream		filePath_;
  t_tile			**grid_;
  Entity			entities_[15];
private:
  void				p_hexColorToAlColor(t_tile *tile);
  void				p_move(int x, int y);
};

#endif				// __MAP_MANAGER_HH__
