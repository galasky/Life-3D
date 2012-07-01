##
## Makefile for raytracer in /home/teisse_l//Documents/projet/raytracer
## 
## Made by lambert teisserenc-bonesteve
## Login   <teisse_l@epitech.net>
## 
## Started on  Wed Jan 25 01:05:57 2012 lambert teisserenc-bonesteve
## Last update Sun Jul  1 18:23:09 2012 lambert teisserenc-bonesteve
##

NAME		=	life-3d

CXXFLAGS	=	-I include/ -Wextra -Wall

LDFLAGS		=	-lsfml-window -lsfml-graphics -lsfml-audio -lGL -lGLU -lfmodex -lm

CC		=	g++
RM		=	rm -fv

SRC		=	src/main.cpp	\
			src/window.cpp	\
			src/cam.cpp	\
			src/map.cpp

OBJ		=	$(SRC:.cpp=.o)

all:	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(CXXFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	fclean all
