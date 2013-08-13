#include				"TetrisGrid.hh"

TetrisGrid::TetrisGrid()
{
  this->shapeModel_[0][0] = 0x0F00;
  this->shapeModel_[0][1] = 0x2222;
  this->shapeModel_[0][2] = 0x00F0;
  this->shapeModel_[0][3] = 0x4444;

  this->shapeModel_[1][0] = 0x44C0;
  this->shapeModel_[1][1] = 0x8E00;
  this->shapeModel_[1][2] = 0x6440;
  this->shapeModel_[1][3] = 0x0E20;

  this->shapeModel_[2][0] = 0x4460;
  this->shapeModel_[2][1] = 0x0E80;
  this->shapeModel_[2][2] = 0xC440;
  this->shapeModel_[2][3] = 0x2E00;

  this->shapeModel_[3][0] = 0xCC00;
  this->shapeModel_[3][1] = 0xCC00;
  this->shapeModel_[3][2] = 0xCC00;
  this->shapeModel_[3][3] = 0xCC00;

  this->shapeModel_[4][0] = 0x06C0;
  this->shapeModel_[4][1] = 0x8C40;
  this->shapeModel_[4][2] = 0x6C00;
  this->shapeModel_[4][3] = 0x4620;

  this->shapeModel_[5][0] = 0x0E40;
  this->shapeModel_[5][1] = 0x4C40;
  this->shapeModel_[5][2] = 0x4E00;
  this->shapeModel_[5][3] = 0x4640;

  this->shapeModel_[6][0] = 0x0C60;
  this->shapeModel_[6][1] = 0x4C80;
  this->shapeModel_[6][2] = 0xC600;
  this->shapeModel_[6][3] = 0x2640;

  srand(time(NULL));
}

TetrisGrid::~TetrisGrid()
{}

void					TetrisGrid::newGame(int *score)
{
  int					i;

  i = 0;
  while (i < GRID_HEIGHT * GRID_WIDTH)
    {
      IMAGE(&(this->entityPool_[i]))->setBitmap("assets/imgs/tetris-sprite.jpg");
      SPRITE(&(this->entityPool_[i]))->config(8, CELL_SIZE, CELL_SIZE, 0, 8, 0, 0.13);
      VISIBILITY(&(this->entityPool_[i]))->setVisible(false);
      POSITION(&(this->entityPool_[i]))->setPos(- CELL_SIZE, - CELL_SIZE);
      ++i;
    }

  memset(this->grid_, 0, sizeof(this->grid_[0][0]) * GRID_WIDTH * GRID_HEIGHT);
  this->p_newShape();
  *score = 0;
  this->score_ = score;
  this->isGameOVer_ = false;
}

void					TetrisGrid::draw()
{
  // int					i;
  // int					j;

  // i = 0;
  // while (i < GRID_HEIGHT)
  //   {
  //     j = 0;
  //     while (j < GRID_WIDTH)
  // 	{
  // 	  if (this->grid_[i][j])
  // 	    this->grid_[i][j]->draw();
  // 	  ++j;
  // 	}
  //     ++i;
  //   }
  int						i;

  i = 0;
  while (i < GRID_WIDTH * GRID_HEIGHT)
    {
      this->entityPool_[i].draw();
      ++i;
    }
  // this->p_drawShape();
}

void					TetrisGrid::update()
{
  int						i;
  static double					time = al_get_time();
  double					ctime = al_get_time();

  p_updateShape();
  i = 0;
  while (i < GRID_WIDTH * GRID_HEIGHT)
    {
      if (VISIBILITY(&(this->entityPool_[i]))->visible)
	this->entityPool_[i].update();
      ++i;
    }
  if (ctime - time >= SPEED)
    {
      this->p_checkGridState();
      this->p_moveShape(0, 1);
      time = ctime;
    }


  // int					i;
  // int					j;
  // static double				time = al_get_time();

  // i = 0;
  // p_updateShape();
  // while (i < GRID_HEIGHT)
  //   {
  //     j = 0;
  //     while (j < GRID_WIDTH)
  // 	{
  // 	  if (this->grid_[i][j])
  // 	    this->grid_[i][j]->update();
  // 	  ++j;
  // 	}
  //     ++i;
  //   }
  // if (al_get_time() - time >= SPEED)
  //   {
  //     this->p_checkGridState();
  //     this->p_moveShape(0, 1);
  //     time = al_get_time();
  //   }
}

void					TetrisGrid::input(int key)
{
  switch (key)
    {
    case ALLEGRO_KEY_UP:
      p_rotateShape();
      break;
    case ALLEGRO_KEY_DOWN:
      this->p_dropShape();
      break;
    case ALLEGRO_KEY_LEFT:
      this->p_moveShape(-1, 0);
      break;
    case ALLEGRO_KEY_RIGHT:
      this->p_moveShape(1, 0);
      break;
    case ALLEGRO_KEY_SPACE:
      p_dropShape();
      break;
    }
  (void)key;
}

bool					TetrisGrid::getGameOver() const
{
  return this->isGameOVer_;
}


void					TetrisGrid::p_newShape()
{
  int					i;
  int					count;

  this->shape_.rotation = 0;
  this->shape_.x = 4;
  this->shape_.y = 0;
  this->shape_.postX = 4;
  this->shape_.postY = 0;
  this->shape_.type = floor(rand() % SHAPE_NUMBER);
  i = 0;
  count = 0;
  while (count < 4 && i < GRID_WIDTH * GRID_HEIGHT)
    {
      if (!VISIBILITY(&(this->entityPool_[i]))->visible)
  	{
  	  this->shape_.blocks[count] = &(this->entityPool_[i]);
	  POSITION(&(this->entityPool_[i]))->setPos(-CELL_SIZE, -CELL_SIZE);
  	  SPRITE(&(this->entityPool_[i]))->from = this->shape_.type * 8;
  	  SPRITE(&(this->entityPool_[i]))->currentStep = this->shape_.type * 8;
  	  VISIBILITY(&(this->entityPool_[i]))->setVisible(true);
  	  VISIBILITY(&(this->entityPool_[i]))->opacity = 255;
  	  ROTATION_FORCE(&(this->entityPool_[i]))->stop();
  	  ROTATION(&(this->entityPool_[i]))->angle = 0;
	  this->entityPool_[i].removeComponent(T_MOVE);
	  ++count;
  	}
      ++i;
    }
}

bool					TetrisGrid::p_moveShape(int x, int y)
{
  this->shape_.postX = this->shape_.x;
  this->shape_.postY = this->shape_.y;
  this->shape_.x += x;
  this->shape_.y += y;
  if (this->p_invalidateCollision())
    {
      this->shape_.x = this->shape_.postX;
      this->shape_.y = this->shape_.postY;
      return false;
    }
  else if (this->p_shapeCollision())
    {
      this->shape_.x = this->shape_.postX;
      this->shape_.y = this->shape_.postY;
      this->p_updateShape();
      this->p_registerShape();
      this->p_newShape();
      return false;
    }
  return true;
}

void					TetrisGrid::p_drawShape()
{
  int					i;

  i = 0;
  while (i < 4)
    this->shape_.blocks[i++]->draw();
}

void					TetrisGrid::p_updateShape()
{
  int					bit;
  int					row;
  int					column;
  int					i;

  bit = 0x8000;
  i = 0;
  column = 0;
  row = 0;
  for (; bit > 0; bit = bit >> 1)
    {
      if (this->shapeModel_[this->shape_.type][this->shape_.rotation] & bit)
  	{
  	  POSITION(this->shape_.blocks[i])->x = (this->shape_.x + column) * CELL_SIZE;
  	  POSITION(this->shape_.blocks[i])->y = (this->shape_.y + row) * CELL_SIZE - GRID_TOP_PADDING * CELL_SIZE;
  	  this->shape_.blocks[i]->update();
  	  ++i;
  	}
      if (++column == 4)
  	{
  	  column = 0;
  	  ++row;
  	}
    }
}

void					TetrisGrid::p_registerShape()
{
  int					bit;
  int					row;
  int					column;
  int					i;

  bit = 0x8000;
  i = 0;
  column = 0;
  row = 0;
  for (; bit > 0; bit = bit >> 1)
    {
      if (this->shapeModel_[this->shape_.type][this->shape_.rotation] & bit)
  	{
  	  this->grid_[row + this->shape_.y][column + this->shape_.x] = this->shape_.blocks[i];
  	  i++;
  	}
      if (++column == 4)
  	{
  	  column = 0;
  	  ++row;
  	}
    }
}

bool					TetrisGrid::p_shapeCollision()
{
  int					bit;
  int					row;
  int					column;

  bit = 0x8000;
  column = 0;
  row = 0;
  for (; bit > 0; bit = bit >> 1)
    {
      if (this->shapeModel_[this->shape_.type][this->shape_.rotation] & bit)
  	{
  	  if (row + this->shape_.y >= GRID_HEIGHT
  	      || (this->grid_[row + this->shape_.y][column + this->shape_.x]
  		  && this->shape_.postY < this->shape_.y))
  	    return true;
  	}
      if (++column == 4)
  	{
  	  column = 0;
  	  ++row;
  	}
    }
  return false;
}

bool					TetrisGrid::p_invalidateCollision()
{
  int					bit;
  int					row;
  int					column;

  bit = 0x8000;
  column = 0;
  row = 0;
  for (; bit > 0; bit = bit >> 1)
    {
      if (this->shapeModel_[this->shape_.type][this->shape_.rotation] & bit)
  	{
  	  if (column + this->shape_.x < 0
  	      || column + this->shape_.x >= GRID_WIDTH
  	      || (this->grid_[row + this->shape_.y][column + this->shape_.x]
  		  && this->shape_.postY == this->shape_.y))
  	    return true;
  	}
      if (++column == 4)
  	{
  	  column = 0;
  	  ++row;
  	}
    }
  return false;
}

void					TetrisGrid::p_rotateShape()
{
  if (++this->shape_.rotation >= 4)
    this->shape_.rotation = 0;
  if (this->p_invalidateCollision() || this->p_shapeCollision())
    {
      if (--this->shape_.rotation < 0)
	this->shape_.rotation = 3;
    }
}

void					TetrisGrid::p_dropShape()
{
  while(this->p_moveShape(0, 1))
    ;
}

void					TetrisGrid::p_checkGridState()
{
  int					y;
  int					x;
  int					squareNumber;

  y = GRID_HEIGHT - 1;
  while (y > 0)
    {
      x = 0;
      squareNumber = 0;
      while (x < GRID_WIDTH)
	{
	  if (this->grid_[y][x])
	    ++squareNumber;
	  ++x;
	}
      if (squareNumber == 0)
	break;
      if (squareNumber == GRID_WIDTH)
	this->p_cleanLine(y);
      else if (y <= GRID_TOP_PADDING)
	this->p_gameOver();
      --y;
    }
}

void					TetrisGrid::p_cleanLine(int line)
{
  int					y;
  int					x;

  x = 0;
  while (x < GRID_WIDTH)
    {
      VISIBILITY(this->grid_[line][x])->fadeOut(0.12, 10);
      MOVE(this->grid_[line][x])->vx = rand() % 6 - 3;
      MOVE(this->grid_[line][x])->vy = rand() % 6 - 12;
      MOVE(this->grid_[line][x])->gravityY = 0.1;
      ROTATION_FORCE(this->grid_[line][x])->launch((float)rand()/RAND_MAX/2 - 0.5, 0.005);
      this->grid_[line][x] = NULL;
      ++x;
    }
  y = line - 1;
  while (y > 0)
    {
      x = 0;
      while (x < GRID_WIDTH)
	{
	  if (this->grid_[y][x])
	    POSITION(this->grid_[y][x])->y = POSITION(this->grid_[y][x])->y + CELL_SIZE;
	  this->grid_[y + 1][x] = this->grid_[y][x];
	  ++(*this->score_);
	  ++x;
	}
      --y;
    }
}

void					TetrisGrid::p_gameOver()
{
  this->isGameOVer_ = true;
}
