#include "cam.hpp"

cam::cam()
{
  _c.x = 0;
  _c.y = 0;
  _c.z = 0;

  _v.x = 0;
  _v.y = 0;
  _v.z = 1;
}

cam::~cam()
{

}

void	cam::set_ccam(double cx, double cy, double cz)
{
  _c.x = cx;
  _c.y = cy;
  _c.z = cz;
}

void	cam::set_vcam(double vx, double vy, double vz)
{
  _v.x = vx;
  _v.y = vy;
  _v.z = vz;
}

void	cam::set_ccam(sf::Vector3f c)
{
  _c.x = c.x;
  _c.y = c.y;
  _c.z = c.z;
}

void	cam::set_vcam(sf::Vector3f v)
{
  _v.x = v.x;
  _v.y = v.y;
  _v.z = v.z;
}

sf::Vector3f	cam::get_ccam()
{
  return (_c);
}

sf::Vector3f	cam::get_vcam()
{
  return (_v);
}
