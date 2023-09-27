NAME = scop
CFLAGS = -Wall -Wextra -Werror -Wno-c++11-extensions -std=c++11
LDFLAGS = -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib -lglfw -framework OpenGL
INCLUDES = -I/Users/${USER}/.brew/Cellar/glfw/3.3.8/include
SRC =	src/scop.cpp \
		src/object.cpp \
		src/objectParser.cpp \
		src/runObject.cpp \
		src/mouseUtils.cpp \
		src/shader.cpp


SRC_O = $(SRC:%.cpp=%.o)
RM = rm -f

all: libs $(NAME)

$(NAME): $(SRC_O)
		c++ $(CFLAGS) $(INCLUDES) $(SRC_O) $(LDFLAGS) -o $(NAME)


%.o: %.cpp
	c++ $(CFLAGS) $(INCLUDES) -c $< -o $@

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