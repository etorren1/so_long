# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etorren <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/20 19:32:45 by etorren           #+#    #+#              #
#    Updated: 2021/03/20 19:32:49 by etorren          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCFILES = 	main.c \
			core.c \
			move.c \
			A_star.c \
			draw_back.c \
			draw_utils.c \
			draw_utils_2.c \
			init_textures.c \
			parser.c \
			parser_utils.c \
			shutdown_game.c
			

SRCFOLDER	= source/

OBJFOLDER 	= objects/

SRCS		= $(addprefix $(SRCFOLDER), $(SRCFILES))

OBJS		= $(addprefix $(OBJFOLDER), $(SRCFILES:.c=.o))

FLAGS		= -Wall -Wextra -Werror -g 

LIB_PATH	= ./libft/libft.a ./mlx_linux/libmlx.a

NAME		= so_long

$(OBJFOLDER)%.o: $(SRCFOLDER)%.c
	@gcc  -I/usr/include -Imlx_linux -O3 -c $< -o $@

all: $(NAME)

$(OBJFOLDER):
	mkdir -p objects

$(NAME): $(OBJFOLDER) $(OBJS)
#	@$(MAKE) bonus -C ./libft
	@gcc $(FLAGS) $(OBJS) $(LIB_PATH) -lbsd -lXext -lX11 -lm -lz -o $(NAME)
	@echo "\033[33mCompiling complete\033[0m"

clean:
#	@$(MAKE) clean -C ./libft
	@rm -rf $(OBJS)
	@echo "\033[33mClean objects files\033[0m"

fclean: clean
#	@$(MAKE) fclean -C ./libft
	@rm -rf $(NAME)
	@echo "\033[33mAll cleaned\033[0m"

re: fclean all


norm:
	@echo "\033[46m\033[30mLIBFT\033[0m"; \
	cd libft; \
	norminette *.c *.h; \
	cd ../includes; \
	echo "\033[46m\033[30mHEADERS\033[0m"; \
	norminette *.h; \
	cd ../sourse; \
	echo "\033[46m\033[30mSOURSE\033[0m"; \
	norminette *.c; \
	cd ./draw_core; \
	echo "\033[46m\033[30mDRAW_CORE\033[0m"; \
	norminette *.c; \
	cd ../parser; \
	echo "\033[46m\033[30mPARSER\033[0m"; \
	norminette *.c; \
	cd ../movement; \
	echo "\033[46m\033[30mMOVEMENT\033[0m"; \
	norminette *.c; \
	cd ../soft_function; \
	echo "\033[46m\033[30mSOFT_FUNCTION\033[0m"; \
	norminette *.c; 