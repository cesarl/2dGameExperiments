#ifndef					__TETRIS_GRID_HH__
# define				__TETRIS_GRID_HH__

#include				<string.h>
#include				<math.h>
#include				<time.h>
#include				<stdlib.h>
#include				"Entity.hh"
#include				"ComponentTypes.hh"

# define				GRID_WIDTH 10
# define				GRID_HEIGHT 22
# define				CELL_SIZE 50
# define				GRID_TOP_PADDING 2
# define				SPEED 0.15
# define				SHAPE_NUMBER 7

typedef					struct shape_s
{
  int					rotation;
  int					postX;
  int					postY;
  int					x;
  int					y;
  int					type;
  Entity				*blocks[4];
}					shape_t;

class					TetrisGrid
{
public:
  TetrisGrid();
  ~TetrisGrid();
  void					newGame(int *score);
  void					draw();
  void					update();
  void					input(int key);
  bool					getGameOver() const;
private:
  Entity				entityPool_[GRID_WIDTH * GRID_HEIGHT];
  Entity				*grid_[GRID_HEIGHT][GRID_WIDTH];
  shape_t				shape_;
  int					shapeModel_[SHAPE_NUMBER][4];
  int					*score_;
  bool					isGameOVer_;
private: //function members
  void					p_newShape();
  bool					p_moveShape(int x, int y);
  void					p_drawShape();
  void					p_updateShape();
  void					p_registerShape();
  bool					p_shapeCollision();
  bool					p_invalidateCollision();
  void					p_rotateShape();
  void					p_dropShape();
  void					p_checkGridState();
  void					p_cleanLine(int line);
  void					p_gameOver();
};

#endif					// __TETRIS_GRID_HH__















