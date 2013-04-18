#include <sdlglutils.h>
#include <time.h>
#include <string>
#include <iostream>
#include "window.hpp"
#include "cam.hpp"
#include "map"

#define	TAILLE_SPECTRE	X

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
  glEnable(GL_TEXTURE_2D);
  tex = loadTexture("floor.jpg");
  _app.setFramerateLimit(60);
  _app.setVerticalSyncEnabled(true);
  _app.setJoystickThreshold(100);
}

void		drow_cube(int x, int y, float spectre[TAILLE_SPECTRE], int l)
{
  float		hauteur;
  
  hauteur = spectre[x / 2] * l * (x / 10);
  hauteur += spectre[y / 2] * l * (y / 10);

  glColor4d(0,0,0, 25);
  glVertex3d(x + 0, y + 0, 0);
  glVertex3d(x + 1, y + 0, 0);
  glVertex3d(x + 1, y + 1, 0);
  glVertex3d(x + 0, y + 1, 0);

  glColor4d(0,0,0, 25);
  glVertex3d(x + 0, y + 0, 0);
  glColor4d(0,255,0, 25);
  glVertex3d(x + 0, y + 0, 1 + hauteur);
  glVertex3d(x + 1, y + 0, 1 + hauteur);
  glColor4d(0,0,0, 25);  
  glVertex3d(x + 1, y + 0, 0);

  glVertex3d(x + 0, y + 0, 0);
  glColor4d(0,255,0, 25);
  glVertex3d(x + 0, y + 0, 1 + hauteur);
  glVertex3d(x + 0, y + 1, 1 + hauteur);
  glColor4d(0,0,0, 25);
  glVertex3d(x + 0, y + 1, 0);


  glColor4d(255,255,255, 25);
  glVertex3d(x + 0, y + 0, 1 + hauteur);
  glVertex3d(x + 1, y + 0, 1 + hauteur);
  glVertex3d(x + 1, y + 1, 1 + hauteur);
  glVertex3d(x + 0, y + 1, 1 + hauteur);

  glColor4d(0,0,0, 25);
  glVertex3d(x + 0, y + 1, 0);
  glColor4d(0,255,0, 25);
  glVertex3d(x + 0, y + 1, 1 + hauteur);
  glVertex3d(x + 1, y + 1, 1 + hauteur);
  glColor4d(0,0,0, 25);
  glVertex3d(x + 1, y + 1, 0);


  glVertex3d(x + 1, y + 0, 0);
  glColor4d(0,255,0, 25);
  glVertex3d(x + 1, y + 0, 1 + hauteur);
  glVertex3d(x + 1, y + 1, 1 + hauteur);
  glColor4d(0,0,0, 25);
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

void	drow(cam cam, map map, float spectre[TAILLE_SPECTRE], int l, GLuint tex)
{
  int	x, y = 0;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(cam.get_c().x, cam.get_c().y, cam.get_c().z, cam.look().x, cam.look().y, cam.look().z, 0, 0, 1);
  glBegin(GL_QUADS);

  glColor4d(255,255,255, 25);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexCoord2i(0,0);		glVertex3d(0,0,0);
  glTexCoord2i(X,0);		glVertex3d(X,0,0);
  glTexCoord2i(X,Y);		glVertex3d(X,Y,0);
  glTexCoord2i(0,Y);		glVertex3d(0,Y,0);
  while (y < Y)
    {
      x = 0;
      while (x < X)
	{
	  if (map.get_life(x, y))
	    drow_cube(x, y, spectre, l);
	  x++;
	}
      y++;
    }
  glEnd();
  glFlush();
}

void	catch_event(sf::RenderWindow &_app, sf::Event &event, cam &cam, map &map, int &vitesse, int &l, std::vector<bool> &key, std::vector<bool> &mouse)
{
  while (_app.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
	_app.close();
      else if (event.type == sf::Event::KeyPressed)
        {
          if (event.key.code == sf::Keyboard::Escape)
            _app.close();
          else if (event.key.code == sf::Keyboard::Up)
            key[0] = true;
          else if (event.key.code == sf::Keyboard::Down)
            key[1] = true;
          else if (event.key.code == sf::Keyboard::Left)
            key[2] = true;
          else if (event.key.code == sf::Keyboard::Right)
            key[3] = true;
          else if (event.key.code == sf::Keyboard::Z)
            key[4] = true;
          else if (event.key.code == sf::Keyboard::S)
            key[5] = true;
          else if (event.key.code == sf::Keyboard::Q)
            key[6] = true;
          else if (event.key.code == sf::Keyboard::D)
            key[7] = true;
          else if (event.key.code == sf::Keyboard::A)
            key[8] = true;
          else if (event.key.code == sf::Keyboard::E)
            key[9] = true;
	  else if (event.key.code == sf::Keyboard::Space)
	    map.pause();
	  else if (event.key.code == sf::Keyboard::V)
	    vitesse--;
	  else if (event.key.code == sf::Keyboard::B)
	    vitesse++;
	  else if (event.key.code == sf::Keyboard::I)
	    clown(map);
	  else if (event.key.code == sf::Keyboard::R)
	    random(map);
	  else if (event.key.code == sf::Keyboard::C)
	    clear(map);
	  else if (event.key.code == sf::Keyboard::P)
	    l++;
	  else if (event.key.code == sf::Keyboard::M)
	    l--;
	  else if (event.key.code == sf::Keyboard::O)
	    l = 0;
        }
      else if (event.type == sf::Event::KeyReleased)
        {
          if (event.key.code == sf::Keyboard::Up)
            key[0] = false;
          else if (event.key.code == sf::Keyboard::Down)
            key[1] = false;
          else if (event.key.code == sf::Keyboard::Left)
            key[2] = false;
          else if (event.key.code == sf::Keyboard::Right)
            key[3] = false;
          else if (event.key.code == sf::Keyboard::Z)
            key[4] = false;
          else if (event.key.code == sf::Keyboard::S)
            key[5] = false;
          else if (event.key.code == sf::Keyboard::Q)
            key[6] = false;
          else if (event.key.code == sf::Keyboard::D)
            key[7] = false;
          else if (event.key.code == sf::Keyboard::A)
            key[8] = false;
          else if (event.key.code == sf::Keyboard::E)
            key[9] = false;
        }
      if (event.type == sf::Event::MouseButtonPressed)
        {
          if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            mouse[0] = true;
          else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            mouse[1] = true;
        }
      if (event.type == sf::Event::MouseButtonReleased)
        {
          mouse[0] = false;
          mouse[1] = false;
        }
      if (event.type == sf::Event::MouseMoved)
        {

        }
    }
}

void    key_action(std::vector<bool> key, cam &cam)
{
  if (key[0])
    {
      cam.look_down(0.1);
    }
  if (key[1])
    {
      cam.look_up(0.1);
    }
  if (key[2])
    {
      cam.look_right(0.1);
    }
  if (key[3])
    {
      cam.look_left(0.1);
    }
  if (key[4])
    {
      cam.advance(0.5);
    }
  if (key[5])
    {
      cam.back(0.5);
    }
  if (key[6])
    {
      cam.right(0.5);
    }
  if (key[7])
    {
      cam.left(0.5);
    }
  if (key[8])
    {
      cam.up(0.5);
    }
  if (key[9])
    {
      cam.down(0.5);
    }
}

int     add_cube(sf::Vector3f v, sf::Vector3f c, map &_map, int mx, int my)
{
  float k;
  sf::Vector2i p;

  if (-1 * v.z + 0 == 0)
    return (0);
  else
    k = (-1 * c.z + 0) / (-1 * (-1 * v.z));
  p.x = v.x * k + c.x;
  p.y = v.y * k + c.y;
  if (p.x >= 0 && p.x < mx && p.y >= 0 && p.y < my)
    _map.set(p.x, p.y, 1);
}

int     delet_cube(sf::Vector3f v, sf::Vector3f c, map &_map, int mx, int my)
{
  float k;
  sf::Vector2i p;

  if (-1 * v.z + 0 == 0)
    return (0);
  else
    k = (-1 * c.z + 0) / (-1 * (-1 * v.z));
  p.x = v.x * k + c.x;
  p.y = v.y * k + c.y;
  time_t t = time(NULL);  if (p.x >= 0 && p.x < mx && p.y >= 0 && p.y < my)
    _map.set(p.x, p.y, 0);
}

void    mouse_action(std::vector<bool> mouse, int mx, int my, sf::Vector3f v, sf::Vector3f c, map &_map)
{
  if (mouse[0])
    add_cube(v, c, _map, mx, my);
  if (mouse[1])
    delet_cube(v,c,_map,mx,my);
}

void		window::start()
{
  sf::Event	event;
  std::vector<bool>     key;
  std::vector<bool>     mouse;
  cam		cam;
  map		map;
  float		spectre[TAILLE_SPECTRE];
  int		time = 0;
  int		vitesse = 10;
  int		l = 2;
  int		i = -1;

  while (++i < 10)
    key.push_back(false);
  i = -1;
  while (++i < 3)
    mouse.push_back(false);
  cam.set_c(X/2 + 30,Y/2 + 30,30);
  while (_app.isOpen())
    {
      if (time > vitesse)
	{
	  map.refresh();
	  time = 0;
	}
      time++;
      catch_event(_app, event, cam, map, vitesse, l, key, mouse);
      key_action(key, cam);
      mouse_action(mouse, X, Y, cam.get_v(), cam.get_c(), map);
      drow(cam, map, spectre, l, tex);
      _app.display();
    }
}
