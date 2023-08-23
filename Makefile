NAME = cub3D
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
CC = @clang
FT_SRC = cub3d.c parsing/parsing.c parsing/utils.c parsing/infos.c parsing/error.c parsing/floorDetails.c\
parsing/ceilingDetails.c parsing/mapDetails.c parsing/playerDetails.c parsing/reformMap.c\
reycasting/reycasting.c reycasting/utils.c \
get_next_line/get_next_line_utils.c get_next_line/get_next_line.c \
libft/ft_strchr.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_strjoin.c libft/ft_strcmp.c libft/ft_isdigit.c\
libft/ft_atoi.c libft/ft_split.c libft/ft_substr.c



OBJ = $(FT_SRC:.c=.o)


all: $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@


$(NAME): $(OBJ)
	@make -C costumizing/
	@$(CC) $(CFLAGS) $(OBJ) -Lmlx_Linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
# @$(CC) $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	@rm -f $(OBJ)
	@make -C libft clean

fclean: clean
	@make -C costumizing/ mse7
	@rm -f $(NAME)

re: fclean all
