#ifndef	__WINDOW_HPP__
#define	__WINDOW_HPP__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fmodex/fmod.h>
#include <string>
#include <fstream>
#include <iostream>
#include "map.hpp"

class	window
{
public:

  window();
  ~window();
  void	init();
  void	load();
  void	start(char name[256]);

private:

  sf::RenderWindow	_app;
  sf::Event		_event;
  sf::Music		_music;
  std::string		_name;
  int			_size_x;
  int			_size_y;
};

#endif
