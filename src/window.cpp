#include <time.h>
#include <string>
#include <iostream>
#include "window.hpp"
#include "cam.hpp"
#include "map"

#define	TAILLE_SPECTRE	(X + Y) / 2

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

void		drow_cube(int x, int y, float spectre[TAILLE_SPECTRE], int l)
{
  float		hauteur;
  int		i = 0;
  
  hauteur = spectre[x / 2] * l * (x / 10);
  hauteur += spectre[y / 2] * l * (y / 10);

  glColor4d(255,255,255, 25);
  glVertex3d(x + 0, y + 0, 0 + hauteur);
  glVertex3d(x + 1, y + 0, 0 + hauteur);
  glVertex3d(x + 1, y + 1, 0 + hauteur);
  glVertex3d(x + 0, y + 1, 0 + hauteur);

  glColor4d(0,255,0, 25);
  glVertex3d(x + 0, y + 0, 0 + hauteur);
  glVertex3d(x + 0, y + 0, 1 + hauteur);
  glVertex3d(x + 1, y + 0, 1 + hauteur);
  glVertex3d(x + 1, y + 0, 0 + hauteur);

  glColor4d(0,255,0, 25);
  glVertex3d(x + 0, y + 0, 0 + hauteur);
  glVertex3d(x + 0, y + 0, 1 + hauteur);
  glVertex3d(x + 0, y + 1, 1 + hauteur);
  glVertex3d(x + 0, y + 1, 0 + hauteur);


  glColor4d(255,255,255, 25);
  glVertex3d(x + 0, y + 0, 1 + hauteur);
  glVertex3d(x + 1, y + 0, 1 + hauteur);
  glVertex3d(x + 1, y + 1, 1 + hauteur);
  glVertex3d(x + 0, y + 1, 1 + hauteur);

  glColor4d(0,255,0, 25);
  glVertex3d(x + 0, y + 1, 0 + hauteur);
  glVertex3d(x + 0, y + 1, 1 + hauteur);
  glVertex3d(x + 1, y + 1, 1 + hauteur);
  glVertex3d(x + 1, y + 1, 0 + hauteur);

  glColor4d(0,255,0, 25);
  glVertex3d(x + 1, y + 0, 0 + hauteur);
  glVertex3d(x + 1, y + 0, 1 + hauteur);
  glVertex3d(x + 1, y + 1, 1 + hauteur);
  glVertex3d(x + 1, y + 1, 0 + hauteur);
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

void	drow(cam cam, map map, float spectre[TAILLE_SPECTRE], int l)
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
	    drow_cube(x, y, spectre, l);
	  x++;
	}
      y++;
    }
  glEnd();
  glFlush();
}

void	catch_event(sf::RenderWindow &_app, sf::Event &event, cam &cam, map &map, int &vitesse, int &l)
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
	  else if (event.key.code == sf::Keyboard::P)
	    l++;
	  else if (event.key.code == sf::Keyboard::M)
	    l--;
	  else if (event.key.code == sf::Keyboard::O)
	    l = 0;
	}
    }
}

void		window::start(char name[256])
{
  sf::Event	event;
  cam		cam;
  map		map;
  float		spectre[TAILLE_SPECTRE];
  int		time = 0;
  int		vitesse = 10;
  int		l = 10;

  FMOD_SYSTEM *system;
  FMOD_SOUND *musique;
  FMOD_CHANNEL *canal;
  FMOD_RESULT resultat;
  FMOD_System_Create(&system);
  FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL); 
  resultat = FMOD_System_CreateSound(system, name, FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
  if (resultat != FMOD_OK)
    {
      fprintf(stderr, "Impossible de lire le fichier mp3\n");
      exit(EXIT_FAILURE);
    }
  FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
  FMOD_System_GetChannel(system, 0, &canal);
  cam.set_ccam(X/2 + 30,Y/2 + 30,30);
  while (_app.isOpen())
    {
      if (time > vitesse)
	{
	  map.refresh();
	  time = 0;
	}
      FMOD_Channel_GetSpectrum(canal, spectre, TAILLE_SPECTRE, 0,  FMOD_DSP_FFT_WINDOW_RECT);
      time++;
      catch_event(_app, event, cam, map, vitesse, l);
      drow(cam, map, spectre, l);
      _app.display();
    }
}
