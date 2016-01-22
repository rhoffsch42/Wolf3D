# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/15 17:38:19 by rhoffsch          #+#    #+#              #
#    Updated: 2015/12/01 03:16:28 by rhoffsch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	wolf3d
CFLAGS	=	-Wall -Wextra -Ofast
MLX		=	../minilibx_macos/libmlx.a
CC		=	gcc
INCLUDE =	-I includes -I libft/includes -I ../minilibx_macos -I includes/fmod

CFILE	=	main.c \
			fmod.c \
			images.c \
			ft_mlx_image_put_pixel.c \
			mlx_hook.c \
			ft_keys.c \
			ft_keys2.c \
			ft_launch_mlx.c \
			ft_draw.c \
			ft_draw_bonus.c \
			ft_draw_bonus2.c \
			ft_draw_texture.c \
			ft_get_map.c \
			angle.c \
			find_wall.c \
			ft_get_walls.c \
			ft_iswall.c \
			ft_dec_to_rgb.c \
			gnl.c

HFILE	=	wolf3d.h

HDIR	=	includes/
HDR		=	$(patsubst %.h, $(HDIR)%.h, $(HFILE))
SDIR	=	src/
SRC		=	$(patsubst %.c, $(SDIR)%.c, $(CFILE))
ODIR	=	obj/
OBJ		=	$(patsubst %.c, $(ODIR)%.o, $(CFILE))

all: compile

$(NAME): $(SRC) $(OBJ)
	@make -C libft/
	@$(CC) $(CFLAGS) $(OBJ) libfmodex.dylib -L libft/ -lft -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "\033[33;32m$(NAME) \033[33;37mcreated"
	@echo "\033[33;35mwolf3d End\033[33;37m"

$(ODIR)%.o: $(SDIR)%.c $(HDR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "\033[33;33m\t$@ compiled\033[33;37m"

compile:
	@mkdir -p obj
	@$(MAKE) -C libft
	@$(MAKE) $(NAME)
	@$(MAKE) fclean
	@$(MAKE) $(NAME)

norm:
	norminette $(SDIR) $(HDR)

clean: 
	@rm -f $(OBJ)
	@echo "\033[33;33mAll objects \033[33;31mdeleted\033[33;37m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[33;32m$(NAME) \033[33;31mdeleted\033[33;37m"

re: fclean all
