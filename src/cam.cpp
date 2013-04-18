#include <math.h>
#include "cam.hpp"

#define	PI	3.14159265

void		rotation_x(double a, sf::Vector3f &f)
{
  sf::Vector3f  tempo;

  tempo.x = f.x;
  tempo.y = f.y;
  tempo.z = f.z;
  f.x *= 1;
  f.y = cos(a) * tempo.y - sin(a) * tempo.z;
  f.z = sin(a) * tempo.y + cos(a) * tempo.z;
}

void		rotation_y(double a, sf::Vector3f &f)
{
  sf::Vector3f  tempo;

  tempo.x = f.x;
  tempo.y = f.y;
  tempo.z = f.z;
  f.x = cos(a) * tempo.x + sin(a) * tempo.z;
  f.y *= 1;
  f.z = -sin(a) * tempo.x + cos(a) * tempo.z;
}

void		rotation_z(double a, sf::Vector3f &f)
{
  sf::Vector3f  tempo;

  tempo.x = f.x;
  tempo.y = f.y;
  tempo.z = f.z;
  f.x = cos(a) * tempo.x - sin(a) * tempo.y;
  f.y = sin(a) * tempo.x + cos(a) * tempo.y;
  f.z *= 1;
}


cam::cam()
{
  _c.x = 0;
  _c.y = 0;
  _c.z = 0;

  _r.x = -0.74;
  _r.y = 0;
  _r.z = 2.40159;

  _vi.x = 0;
  _vi.y = 1;
  _vi.z = 0;

  _v = _vi;

  rotation_x(_r.x, _v);
  rotation_y(_r.y, _v);
  rotation_z(_r.z, _v);
}

cam::~cam()
{

}

void	cam::set_c(double cx, double cy, double cz)
{
  _c.x = cx;
  _c.y = cy;
  _c.z = cz;
}

void	cam::set_v(double vx, double vy, double vz)
{
  _v.x = vx;
  _v.y = vy;
  _v.z = vz;
}

void	cam::set_c(sf::Vector3f c)
{
  _c.x = c.x;
  _c.y = c.y;
  _c.z = c.z;
}

void	cam::set_v(sf::Vector3f v)
{
  _v.x = v.x;
  _v.y = v.y;
  _v.z = v.z;
}

sf::Vector3f	cam::look()
{
  sf::Vector3f	look;

  look.x = _c.x + _v.x;
  look.y = _c.y + _v.y;
  look.z = _c.z + _v.z;
  return (look);
}

sf::Vector3f	cam::get_c()
{
  return (_c);
}

sf::Vector3f	cam::get_v()
{
  return (_v);
}

void		cam::advance(double k)
{
  _c.x += _v.x * k;
  _c.y += _v.y * k;
  _c.z += _v.z * k;
}

void            cam::back(double k)
{
  _c.x -= _v.x * k;
  _c.y -= _v.y * k;
  _c.z -= _v.z * k;
}
 
void		cam::left(double k)
{
  sf::Vector3f	t;

  t = _vi;
  rotation_z(-PI / 2, t);
  rotation_x(_r.x, t);
  rotation_y(_r.y, t);
  rotation_z(_r.z, t);

  _c.x += t.x * k;
  _c.y += t.y * k;
  _c.z += t.z * k;
}

void		cam::right(double k)
{
  sf::Vector3f	t;

  t = _vi;
  rotation_z(PI / 2, t);
  rotation_x(_r.x, t);
  rotation_y(_r.y, t);
  rotation_z(_r.z, t);

  _c.x += t.x * k;
  _c.y += t.y * k;
  _c.z += t.z * k;
}

void		cam::up(double k)
{
  sf::Vector3f  t;

  t = _vi;
  rotation_x(PI / 2, t);
  _c.x += t.x * k;
  _c.y += t.y * k;
  _c.z += t.z * k;
}

void		cam::down(double k)
{
  sf::Vector3f  t;

  t = _vi;
  rotation_x(-PI / 2, t);

  _c.x += t.x * k;
  _c.y += t.y * k;
  _c.z += t.z * k;

}

void		cam::look_up(double a)
{
  _r.x -= a;
  _v = _vi;
  rotation_x(_r.x, _v);
  rotation_y(_r.y, _v);
  rotation_z(_r.z, _v);
}

void		cam::look_down(double a)
{
  _r.x += a;
  _v = _vi;
  rotation_x(_r.x, _v);
  rotation_y(_r.y, _v);
  rotation_z(_r.z, _v);
}

void		cam::look_left(double a)
{
  _r.z -= a;
  _v = _vi;
  rotation_x(_r.x, _v);
  rotation_y(_r.y, _v);
  rotation_z(_r.z, _v);
}

void		cam::look_right(double a)
{
  _r.z += a;
  _v = _vi;
  rotation_x(_r.x, _v);
  rotation_y(_r.y, _v);
  rotation_z(_r.z, _v);
}
