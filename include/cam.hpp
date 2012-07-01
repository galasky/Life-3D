#ifndef		__CAM_HPP__
#define		__CAM_HPP__

#include	<SFML/Graphics.hpp>

class		cam
{
public:

  cam();
  ~cam();
  void		set_ccam(double cx, double cy, double cz);
  void		set_vcam(double vx, double vy, double vz);
  void		set_ccam(sf::Vector3f c);
  void		set_vcam(sf::Vector3f v);
  sf::Vector3f	get_ccam();
  sf::Vector3f	get_vcam();

private:

  sf::Vector3f	_c;
  sf::Vector3f	_v;
};

#endif
