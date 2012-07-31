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
