# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/24 17:56:27 by ayguillo          #+#    #+#              #
#*   Updated: 2019/07/02 18:29:54 by bopopovi         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

CC			=	/usr/bin/gcc

CFLAGS		=	-Wall -Wextra -Werror

LFLAGS		=	

MAKE		=	make

RM			=	/bin/rm

DIRINC		=	includes

# **************************************************************************** #
# ASM :

NAMEASM		=	asm

DIRASM		=	asmsrc

INCASM		=	$(addprefix $(DIRINC)/, \
		asm.h op.h)

SRCSASM		=	$(addprefix $(DIRASM)/, \
		main.c print.c header.c free.c label.c instruction.c tools.c params.c \
		fillparams.c filllabel.c fillgeneric.c params2.c paramgen.c)

OBJSASM		=	$(SRCSASM:.c=.o)

# **************************************************************************** #
# VM :

NAMEVM		=	corewar

DIRVM		=	vm

DIRPROC		=	process

PROC_SRC_NAME	=	\
		process_execute.c get_instruction_parameter.c local_debug.c \
		op_and.c op_jmpz.c op_live.c op_st.c read_from_register.c \
		read_from_vm.c vm_query.c vm_set.c \
		write_to_register.c write_to_vm.c ocp_tools.c ncurse_print_mem.c

PROC_SRC		=	$(addprefix $(DIRVM)/$(DIRPROC)/srcs/, $(PROC_SRC_NAME))

OBJSPROC	=	$(PROC_SRC:$(DIRVM)/$(DIRPROC)/srcs/.c=$(DIRVM)/$(DIRPROC)/objs/.o)

INCVM		=	$(addprefix $(DIRINC)/, \
		vm.h options.h)

SRCSVM		=	$(addprefix $(DIRVM)/, \
		vm_main.c vm_options.c vm_process.c vm_read_player.c vm_errors.c \
		vm_arena.c vm_game.c)

OBJSVM		=	$(SRCSVM:.c=.o)

# **************************************************************************** #
# LIB :

NAMELIB		=	libft.a

DIRLIB		=	libft

LIB			=	$(DIRLIB)/$(NAMELIB)

############################## RULES ###########################################

all			:	make_lib $(NAMEASM) $(NAMEVM)

$(NAMEASM)	:	$(LIB) $(INCASM) $(OBJSASM)
	@ echo "$(YELLOW)Compilation de $(NAMEASM) . . . $(WHITE)"
	@ $(CC) $(LFLAGS) -o $(NAMEASM) $(OBJSASM) $(LIB)
	@ echo "$(GREEN)$(NAMEASM) compilé$(WHITE)"

$(NAMEVM)	:	$(LIB) $(INCVM) $(OBJSVM) $(OBJSPROC)
	@ echo "$(YELLOW)Compilation de $(NAMEVM) . . . $(WHITE)"
	@ $(CC) $(LFLAGS) -o $(NAMEVM) $(OBJSVM) $(OBJSPROC) $(LIB) -lncurses
	@ echo "$(GREEN)$(NAMEVM) compilé$(WHITE)"

%.o			:	%.c
	@ $(CC) $(CFLAGS) -c $< -o $@

$(LIB)		: make_lib

make_lib	:
	@ $(MAKE) -C $(DIRLIB) CFLAGS="$(CFLAGS)"

clean		:
	@ echo "$(RED)Suppression des .o$(WHITE)"
	@ $(MAKE) clean -C $(DIRLIB)
	@ $(RM) -f $(OBJSASM)
	@ $(RM) -f $(OBJSVM)

fclean		:	clean
	@ $(MAKE) fclean -C $(DIRLIB)
	@ echo "$(RED)Suppression de $(NAMEASM)$(WHITE)"
	@ $(RM) -rf $(NAMEASM)
	@ echo "$(RED)Suppression de $(NAMEVM)$(WHITE)"
	@ $(RM) -rf $(NAMEVM)

re			:	fclean all

############################## DISPLAY #########################################

YELLOW		=	\033[0;33m
RED			=	\033[0;31m
GREEN		=	\033[0;32m
WHITE		=	\x1b[0m

############################## OTHER ###########################################

.PHONY : clean fclean re all
