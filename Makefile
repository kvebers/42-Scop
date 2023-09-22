NAME = scop
CFLAGS = -Wall -Wextra -Werror -std=c++20
LDFLAGS = -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib -lglfw -framework OpenGL
INCLUDES = -I/Users/${USER}/.brew/Cellar/glfw/3.3.8/glfw
SRC =	scop.cpp \
		object.cpp \
		objectParser.cpp \
		runObject.cpp


SRC_O = $(SRC:%.cpp=%.o)
RM = rm -f

all: libs $(NAME)

$(NAME): $(SRC_O)
		c++ $(CFLAGS) $(INCLUDES) $(SRC_O) $(LDFLAGS) -o $(NAME)

libs:
		@if ! brew ls --versions glfw > /dev/null; then \
			brew install glfw; \
		fi

clean:
		$(RM) $(SRC_O)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re