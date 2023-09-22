NAME = scop
CFLAGS = -Wall -Wextra -Werror -std=c++20
LDFLAGS = -lGL -lGLU -lglfw
SRC = 

SRC_O = $(SRC:%.cpp=%.o)
RM = rm -f

all: libs $(NAME)

$(NAME): $(SRC_O)
		c++ $(CFLAGS) $(SRC_O) -o $(NAME) $(LDFLAGS)

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