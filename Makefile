NAME = scop
CFLAGS = -Wall -Wextra -Werror -Wno-c++11-extensions -std=c++11
LDFLAGS = -L/Users/${USER}/.brew/Cellar/glfw/3.4/lib -lglfw -framework OpenGL -framework CoreGraphics -framework CoreFoundation
INCLUDES = -I/Users/${USER}/.brew/Cellar/glfw/3.4/include
SRC =	src/scop.cpp \
		src/object.cpp \
		src/objectParser.cpp \
		src/runObject.cpp \
		src/mouseUtils.cpp \
		src/shader.cpp \
		src/keyHook.cpp \
		src/defaultMaterials.cpp \
		src/shape.cpp \
		src/uvUnwrapping.cpp


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