#include <time.h>
#include "window.hpp"
#include "cam.hpp"
#include "map"

window::window()
{
  _size_x = 160;
  _size_y = 90;
}

window::~window()
{

}

void	window::init()
{
  _app.create(sf::VideoMode(_size_x, _size_y, 32), _name, sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, (double) _size_x / _size_y, 0.01, 10000);
  glEnable(GL_DEPTH_TEST);
  _app.setFramerateLimit(60);
  _app.setVerticalSyncEnabled(true);
  _app.setJoystickThreshold(100);
}

void	drow_cube(int x, int y)
{
  glColor4d(255,255,255, 25);
  glVertex3d(x + 0, y + 0, 0);
  glVertex3d(x + 1, y + 0, 0);
  glVertex3d(x + 1, y + 1, 0);
  glVertex3d(x + 0, y + 1, 0);

  glColor4d(0,255,0, 25);
  glVertex3d(x + 0, y + 0, 0);
  glVertex3d(x + 0, y + 0, 1);
  glVertex3d(x + 1, y + 0, 1);
  glVertex3d(x + 1, y + 0, 0);

  glColor4d(0,255,0, 25);
  glVertex3d(x + 0, y + 0, 0);
  glVertex3d(x + 0, y + 0, 1);
  glVertex3d(x + 0, y + 1, 1);
  glVertex3d(x + 0, y + 1, 0);


  glColor4d(255,255,255, 25);
  glVertex3d(x + 0, y + 0, 1);
  glVertex3d(x + 1, y + 0, 1);
  glVertex3d(x + 1, y + 1, 1);
  glVertex3d(x + 0, y + 1, 1);

  glColor4d(0,255,0, 25);
  glVertex3d(x + 0, y + 1, 0);
  glVertex3d(x + 0, y + 1, 1);
  glVertex3d(x + 1, y + 1, 1);
  glVertex3d(x + 1, y + 1, 0);

  glColor4d(0,255,0, 25);
  glVertex3d(x + 1, y + 0, 0);
  glVertex3d(x + 1, y + 0, 1);
  glVertex3d(x + 1, y + 1, 1);
  glVertex3d(x + 1, y + 1, 0);
}

void	clown(map &map)
{
  map.set(X/2 + 4,Y/2 + 4, 1);
  map.set(X/2 + 5,Y/2 + 4, 1);
  map.set(X/2 + 6,Y/2 + 4, 1);
  map.set(X/2 + 7,Y/2 + 4, 1);
  map.set(X/2 + 7,Y/2 + 5, 1);
  map.set(X/2 + 7,Y/2 + 3, 1);
}

int     al_gen(int min, int max)
{
  return (rand() % (max - min + 1)) + min;
}

void	random(map &map)
{
  int	x, y = 0;

  srand(time(NULL));
  while (y < Y)
    {
      x = 0;
      while (x < X)
	{
	  if (al_gen(0,5) == 1)
	    map.set(x, y, 1);
	  x++;
	}
      y++;
    }
}

void	clear(map &map)
{
  int	x, y = 0;

  while (y < Y)
    {
      x = 0;
      while (x < X)
	{
	  map.set(x, y, 0);
	  x++;
	}
      y++;
    }
}

void	drow(cam cam, map map)
{
  int	x, y = 0;


  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(cam.get_ccam().x, cam.get_ccam().y, cam.get_ccam().z, Y/2, X/2, 0, 0, 0, 1);
  glBegin(GL_QUADS);
  while (y < Y)
    {
      x = 0;
      while (x < X)
	{
	  if (map.get_life(x, y))
	    drow_cube(x, y);
	  x++;
	}
      y++;
    }
  glEnd();
  glFlush();
}

void	catch_event(sf::RenderWindow &_app, sf::Event &event, cam &cam, map &map, int &vitesse)
{
  while (_app.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
	_app.close();
      if (event.type == sf::Event::KeyPressed)
	{
	  if (event.key.code == sf::Keyboard::Escape)
	    _app.close();
	  else if (event.key.code == sf::Keyboard::A)
	    {
	      sf::Vector3f	f;

	      f = cam.get_ccam();
	      cam.set_ccam(f.x + 1, f.y + 1, f.z + 1);
	    }
	  else if (event.key.code == sf::Keyboard::E)
	    {
	      sf::Vector3f	f;

	      f = cam.get_ccam();
	      cam.set_ccam(f.x - 1, f.y - 1, f.z - 1);
	    }
	  else if (event.key.code == sf::Keyboard::Z)
	    {
	      sf::Vector3f	f;

	      f = cam.get_ccam();
	      cam.set_ccam(f.x, f.y, f.z + 1);
	    }
	  else if (event.key.code == sf::Keyboard::S)
	    {
	      sf::Vector3f	f;

	      f = cam.get_ccam();
	      cam.set_ccam(f.x, f.y, f.z - 1);
	    }
	  else if (event.key.code == sf::Keyboard::Space)
	    map.pause();
	  else if (event.key.code == sf::Keyboard::Up)
	    vitesse--;
	  else if (event.key.code == sf::Keyboard::Down)
	    vitesse++;
	  else if (event.key.code == sf::Keyboard::I)
	    clown(map);
	  else if (event.key.code == sf::Keyboard::R)
	    random(map);
	  else if (event.key.code == sf::Keyboard::C)
	    clear(map);
	}
    }
}

void		window::start()
{
  sf::Event	event;
  cam		cam;
  map		map;
  int		time = 0;
  int		vitesse = 10;

  cam.set_ccam(X/2 + 10,Y/2 + 10,10);
  while (_app.isOpen())
    {
      if (time > vitesse)
	{
	  map.refresh();
	  time = 0;
	}
      time++;
      catch_event(_app, event, cam, map, vitesse);
      drow(cam, map);
      _app.display();
    }
}
