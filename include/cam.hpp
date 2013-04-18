#ifndef		__CAM_HPP__
#define		__CAM_HPP__

#include	<SFML/Graphics.hpp>

class		cam
{
public:

  cam();
  ~cam();
  void		set_c(double cx, double cy, double cz);
  void		set_v(double vx, double vy, double vz);
  void		set_c(sf::Vector3f c);
  void		set_v(sf::Vector3f v);
  sf::Vector3f	look();
  sf::Vector3f	get_c();
  sf::Vector3f	get_v();
  void		advance(double k);
  void		back(double k);
  void		left(double k);
  void		right(double k);
  void		up(double k);
  void		down(double k);
  void		look_up(double a);
  void		look_down(double a);
  void		look_left(double a);
  void		look_right(double a);  

private:

  sf::Vector3f	_c;
  sf::Vector3f	_r;
  sf::Vector3f	_v;
  sf::Vector3f	_vi;
};

#endif
