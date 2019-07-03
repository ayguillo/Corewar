CC				=	/usr/bin/gcc

CFLAGS			=	

MAKE			=	/usr/bin/make

RM				=	/bin/rm

MV				=	/bin/mv

NAME_ASM		=	asm

ASM_DIR			=	asmsrc

NAME_VM			=	corewar

VM_DIR			=	vm

############################## RULES ###########################################

all				:	$(NAME_ASM) $(NAME_VM)

$(NAME_ASM)		:
	@ $(MAKE) $(CFLAGS) -C $(ASM_DIR)
	@ $(MV) $(ASM_DIR)/$(NAME_ASM) .

$(NAME_VM)		:
	@ $(MAKE) $(CFLAGS) -C $(VM_DIR)
	@ $(MV) $(VM_DIR)/$(NAME_VM) .

clean			:
	@ $(MAKE) clean -C $(ASM_DIR)
	@ $(MAKE) clean -C $(VM_DIR)

fclean			:	clean
	@ $(MAKE) fclean -C $(ASM_DIR)
	@ $(MAKE) fclean -C $(VM_DIR)
	@ $(RM) $(NAME_ASM) $(NAME_VM)

re				:	fclean all

############################## DISPLAY #########################################

YELLOW			=	\033[0;33m
RED				=	\033[0;31m
GREEN			=	\033[0;32m
WHITE			=	\x1b[0m

############################## OTHER ###########################################

.PHONY			:	clean fclean re all
