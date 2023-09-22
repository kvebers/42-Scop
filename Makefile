NAME = scop
CFLAGS = -Wall -Wextra -Werror -std=c++20
LDFLAGS = -lGL -lGLU -lglfw3
SRC = 

SRC_O = $(SRC:%.cpp=%.o)
RM = rm -f

all: $(NAME)

$(NAME): $(SRC_O)
		c++ $(CFLAGS) $(SRC_O) -o $(NAME) $(LDFLAGS)

clean:
		$(RM) $(SRC_O)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re