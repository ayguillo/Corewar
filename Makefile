# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/24 17:56:27 by ayguillo          #+#    #+#              #
#    Updated: 2019/06/21 10:25:42 by ayguillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAMEASM = asm
CFLAGS = -Wall -Wextra -Werror
SRCSASM = asmsrc/main.c asmsrc/print.c asmsrc/header.c asmsrc/free.c \
	   asmsrc/label.c asmsrc/instruction.c asmsrc/tools.c asmsrc/params.c \
	   asmsrc/fillparams.c

LIB = libft/libft.a

YELLOW = \033[0;33m
RED = \033[0;31m
GREEN = \033[0;32m
WHITE = \x1b[0m

OBJSASM = $(SRCSASM:.c=.o)

all : $(NAMEASM)

$(NAMEASM) : $(OBJSASM)
	@ make -C libft
	@ echo "$(YELLOW)Compilation de $(NAMEASM) . . . $(WHITE)"
	@ gcc $(CFLAGS) -o $(NAMEASM) $(OBJSASM) $(LIB)
	@ echo "$(GREEN)$(NAMEASM) compilé$(WHITE)"

$.o : %.c
	@ gcc $(CFLAGS) -c $<

clean :
	@ make clean -C libft
	@ rm $(OBJSASM)
	@ echo "$(RED)Suppression des .o$(WHITE)"

fclean : clean
	@ rm -rf $(LIB)
	@ rm -rf $(NAMEASM)
	@ echo "$(RED) Suppression de $(NAMEASM)$(WHITE)"

re : fclean all

.PHONY : clean fclean re all
