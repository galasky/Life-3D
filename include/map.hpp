#ifndef	__MAP_HPP__
#define	__MAP_HPP__

#define	X	600
#define	Y	600

class	map
{
public:

  map();
  ~map();
  void	refresh();
  void	set(int x, int y, int value);
  void	pause();
  int	get_life(int x, int y);

private:

  int	_start;
  int	_new_zone[Y][X];
  int	_old_zone[Y][X];
};

#endif
