#include				"TetrisGrid.hh"

TetrisGrid::TetrisGrid()
{
  int					i;
  int					j;

  i = 0;
  while (i < GRID_HEIGHT)
    {
      j = 0;
      while (j < GRID_WIDTH)
  	{
  	  this->spriteTab_[i * j].setBitmap("assets/imgs/blue_sky_background.jpg");
  	  this->spriteTab_[i * j].setColumnNumber(4);
	  this->spriteTab_[i * j].setStepNumber(40);
	  this->spriteTab_[i * j].setSpeed(i * j);
	  this->spriteTab_[i * j].setPartWidth(CELL_SIZE);
	  this->spriteTab_[i * j].setPartHeight(CELL_SIZE);
  	  this->grid_[i][j].setContentComponent(&(this->spriteTab_[i * j]));
	  this->grid_[i][j].setVisible(false);
  	  this->grid_[i][j].setWidth(CELL_SIZE);
  	  this->grid_[i][j].setHeight(CELL_SIZE);
	  this->grid_[i][j].setPos(j * CELL_SIZE, i * CELL_SIZE - GRID_TOP_PADDING * CELL_SIZE);
  	  ++j;
  	}
      ++i;
    }
  this->p_newForm();
  this->p_showForm();
}

TetrisGrid::~TetrisGrid()
{}

void					TetrisGrid::draw()
{
  int					i;
  int					j;

  i = 0;
  while (i < GRID_HEIGHT)
    {
      j = 0;
      while (j < GRID_WIDTH)
  	{
  	  this->grid_[i][j].draw();
  	  ++j;
  	}
      ++i;
    }
}

void					TetrisGrid::update()
{
  int					i;
  int					j;
  static double				time = al_get_time();

  i = 0;
  while (i < GRID_HEIGHT)
    {
      j = 0;
      while (j < GRID_WIDTH)
  	{
  	  this->grid_[i][j].update();
  	  ++j;
  	}
      ++i;
    }
  if (al_get_time() - time >= SPEED)
    {
      this->p_moveForm(0, 1);
      time = al_get_time();
    }
}

void					TetrisGrid::input(int key)
{
  if (key == ALLEGRO_KEY_LEFT)
    this->p_moveForm(-1, 0);
}

void					TetrisGrid::p_newForm()
{
  this->form_.c1_x = 6;
  this->form_.c1_y = 4;
  this->form_.c2_x = 7;
  this->form_.c2_y = 4;
  this->form_.c3_x = 6;
  this->form_.c3_y = 5;
  this->form_.c4_x = 7;
  this->form_.c4_y = 5;
}

void					TetrisGrid::p_hideForm()
{
  this->grid_[this->form_.c1_y][this->form_.c1_x].setVisible(false);
  this->grid_[this->form_.c2_y][this->form_.c2_x].setVisible(false);
  this->grid_[this->form_.c3_y][this->form_.c3_x].setVisible(false);
  this->grid_[this->form_.c4_y][this->form_.c4_x].setVisible(false);
}

void					TetrisGrid::p_showForm()
{
  this->grid_[this->form_.c1_y][this->form_.c1_x].setVisible(true);
  this->grid_[this->form_.c2_y][this->form_.c2_x].setVisible(true);
  this->grid_[this->form_.c3_y][this->form_.c3_x].setVisible(true);
  this->grid_[this->form_.c4_y][this->form_.c4_x].setVisible(true);
}

void					TetrisGrid::p_moveForm(int x, int y)
{
  this->p_hideForm();
  this->p_copyForm(&this->form_, &this->pastForm_);
  this->form_.c1_x += x;
  this->form_.c1_y += y;
  this->form_.c2_x += x;
  this->form_.c2_y += y;
  this->form_.c3_x += x;
  this->form_.c3_y += y;
  this->form_.c4_x += x;
  this->form_.c4_y += y;
  this->p_showForm();
  if (this->form_.c4_y >= GRID_HEIGHT - 1 || this->grid_[this->form_.c4_y + 1][this->form_.c4_x].getVisible())
    this->p_newForm();
}

void					TetrisGrid::p_copyForm(t_formTetris *src, t_formTetris *dest)
{
  dest->c1_x = src->c1_x;
  dest->c1_y = src->c1_y;
  dest->c2_x = src->c2_x;
  dest->c2_y = src->c2_y;
  dest->c3_x = src->c3_x;
  dest->c3_y = src->c3_y;
  dest->c4_x = src->c4_x;
  dest->c4_y = src->c4_y;
}
