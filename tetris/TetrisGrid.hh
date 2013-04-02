#ifndef					__TETRIS_GRID_HH__
# define				__TETRIS_GRID_HH__

#include				"Entity.hh"
#include				"ContentComponentSprite.hh"

# define				GRID_WIDTH 10
# define				GRID_HEIGHT 24
# define				CELL_SIZE 50
# define				GRID_TOP_PADDING 4
# define				SPEED 0.5

typedef					struct s_formTetris
{
  int					c1_x;
  int					c1_y;
  int					c2_x;
  int					c2_y;
  int					c3_x;
  int					c3_y;
  int					c4_x;
  int					c4_y;
}					t_formTetris;

class					TetrisGrid
{
public:
  TetrisGrid();
  ~TetrisGrid();
  void					draw();
  void					update();
  void					input(int key);
private:
  ContentComponentSprite		spriteTab_[GRID_WIDTH * GRID_HEIGHT];
  Entity				grid_[GRID_HEIGHT][GRID_WIDTH];
  t_formTetris				form_;
  t_formTetris				pastForm_;
private: //function members
  void					p_newForm();
  void					p_showForm();
  void					p_hideForm();
  void					p_moveForm(int x, int y);
  void					p_copyForm(t_formTetris *src, t_formTetris *dest);
};

#endif					// __TETRIS_GRID_HH__
