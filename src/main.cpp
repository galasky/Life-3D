#include	"window.hpp"
#include	<iostream>

int		main()
{
  window	window;
  char		name[256];

  std::cout << "music : ";
  std::cin >> name;
  window.init();
  window.start(name);
  return (0);
}
