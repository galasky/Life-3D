#include <iostream>
#include "map.hpp"

map::map()
{
  int	x, y = 0;

  while (y < Y)
    {
      x = 0;
      while (x < X)
	{
	  _new_zone[y][x] = 0;
	  x++;
	}
      y++;
    }
  _start = 0;
  _new_zone[Y/2 + 4][X/2 + 4] = 1;
  _new_zone[Y/2 + 4][X/2 + 5] = 1;
  _new_zone[Y/2 + 4][X/2 + 6] = 1;
  _new_zone[Y/2 + 4][X/2 + 7] = 1;
  _new_zone[Y/2 + 5][X/2 + 7] = 1;
  _new_zone[Y/2 + 3][X/2 + 7] = 1;
}

map::~map()
{

}

void	algo_life(int oz[Y][X], int nz[Y][X], int x, int y)
{
  int	c = 0;

  if (y > 0 && x > 0)
    if (oz[y - 1][x - 1] == 1)
      c++;
  if (y > 0)
    if (oz[y - 1][x] == 1)
      c++;
  if (y > 0 && x < X - 1)
    if (oz[y - 1][x + 1] == 1)
      c++;
  if (x > 0)
    if (oz[y][x - 1] == 1)
      c++;
  if (x > 0 && y < Y - 1)
    if (oz[y + 1][x - 1] == 1)
      c++;
  if (y < Y - 1)
    if (oz[y + 1][x] == 1)
      c++;
  if (y < Y - 1 && x < X - 1)
    if (oz[y + 1][x + 1] == 1)
      c++;
  if (x < X - 1)
    if (oz[y][x + 1] == 1)
      c++;

  if (c == 3)
    nz[y][x] = 1;
  else if (c == 2 && oz[y][x] == 0)
    nz[y][x] = 0;
  else if (c == 2 && oz[y][x] == 1)
    nz[y][x] = 1;
  else
    nz[y][x] = 0;
}

void	cp_zone(int oz[Y][X], int nz[Y][X])
{
  int	x, y = 0;

  while (y < Y)
    {
      x = 0;
      while (x < X)
	{
	  oz[y][x] = nz[y][x];
	  x++;
	}
      y++;
    }
}

void	map::refresh()
{
  int	x, y = 0;
  
  if (!_start)
    return ;
  cp_zone(_old_zone, _new_zone);
  while (y < Y)
    {
      x = 0;
      while (x < X)
	{
	  algo_life(_old_zone, _new_zone, x, y);
	  x++;
	}
      y++;
    }
}

void	map::set(int x, int y, int value)
{
  _new_zone[y][x] = value;
}

void	map::pause()
{
  if (_start)
    _start = 0;
  else
    _start = 1;
}

int	map::get_life(int x, int y)
{
  return (_new_zone[y][x]);
}
