NAME=fdf
FLAGS=-Wall -Wextra -Werror -I includes/
LIBFLAGS=-lft -L libft/ -lmlx -L minilibx_macos -framework OpenGL -framework AppKit -lm
SRCSF=tools.c draw.c events_handling.c parse.c errors_handling.c main.c
OBJSF=$(SRCSF:.c=.o)
SRCS=$(addprefix srcs/, $(SRCSF))
OBJS=$(addprefix objs/, $(OBJSF))

all: $(NAME)

$(OBJS):
	gcc $(FLAGS) -c $(SRCS)
	mkdir -p objs/
	mv $(OBJSF) objs/

$(NAME): $(OBJS)
	make -C minilibx_macos
	make -C libft
	gcc $(LIBFLAGS) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf objs/
	make -C libft/ clean
	make -C minilibx_macos clean

fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
