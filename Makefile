# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/24 17:56:27 by ayguillo          #+#    #+#              #
#    Updated: 2019/05/29 13:45:59 by ayguillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm
CFLAGS = -Wall -Wextra -Werror
SRCS = asmsrc/main.c asmsrc/print.c asmsrc/header.c asmsrc/free.c
LIB = libft/libft.a

YELLOW = \033[0;33m
RED = \033[0;31m
GREEN = \033[0;32m
WHITE = \x1b[0m

OBJ = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@ make -C libft
	@ echo "$(YELLOW)Compilation de $(NAME) . . . $(WHITE)"
	@ gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)
	@ echo "$(GREEN)$(NAME) compilé$(WHITE)"

$.o : %.c
	@ gcc $(CFLAGS) -c $<

clean :
	@ make clean -C libft
	@ rm $(OBJ)
	@ echo "$(RED)Suppression des .o$(WHITE)"

fclean : clean
	@ rm -rf $(LIB)
	@ rm -rf $(NAME)
	@ echo "$(RED) Suppression de $(NAME)$(WHITE)"

re : fclean all

.PHONY : clean fclean re all
