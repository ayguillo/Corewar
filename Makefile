CC				=	/usr/bin/gcc

CFLAGS			=	

MAKE			=	/usr/bin/make

RM				=	/bin/rm

LN				=	ln -s

NAME_ASM		=	asm

ASM_DIR			=	asmsrc

NAME_VM			=	corewar

VM_DIR			=	vm

LIB_DIR			=	libft

############################## RULES ###########################################

all				:
	@ $(MAKE) $(CFLAGS) -C $(LIB_DIR)
	@ $(MAKE) $(CFLAGS) -C $(ASM_DIR)
	@ $(MAKE) $(CFLAGS) -C $(VM_DIR)

$(NAME_ASM)		:
	@ $(MAKE) $(CFLAGS) -C $(ASM_DIR)

$(NAME_VM)		:
	@ $(MAKE) $(CFLAGS) -C $(VM_DIR)

clean			:
	@ $(MAKE) clean -C $(LIB_DIR)
	@ $(MAKE) clean -C $(ASM_DIR)
	@ $(MAKE) clean -C $(VM_DIR)

fclean			:	clean
	@ $(MAKE) fclean -C $(LIB_DIR)
	@ $(MAKE) fclean -C $(ASM_DIR)
	@ $(MAKE) fclean -C $(VM_DIR)

re				:	fclean all

############################## DISPLAY #########################################

YELLOW			=	\033[0;33m
RED				=	\033[0;31m
GREEN			=	\033[0;32m
WHITE			=	\x1b[0m

############################## OTHER ###########################################

.PHONY			:	clean fclean re all $(NAME_VM) $(NAME_ASM)
