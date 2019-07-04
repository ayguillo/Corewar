CC				=	/usr/bin/gcc

CFLAGS			=	

MAKE			=	/usr/bin/make

RM				=	/bin/rm

MKDIR			=	/bin/mkdir -p

NAME			=	asm

SRC_DIR			=	srcs

ASM_SRC			=	\
		main.c print.c header.c free.c label.c instruction.c tools.c params.c \
		fillparams.c filllabel.c fillgeneric.c params2.c paramgen.c

SRC_NAME		=	$(ASM_SRC)

SRC				=	$(addprefix $(SRC_DIR)/,$(SRC_NAME))

OBJ_DIR			=	objs

OBJ_NAME		=	$(SRC_NAME:.c=.o)

OBJ				=	$(addprefix $(OBJ_DIR)/,$(OBJ_NAME))

LIB_DIR			=	../libft

LDLIBS			=	-lft -lncurses

LDFLAGS			=	-L $(LIB_DIR)

INC				=	../includes

CPPFLAGS		=	$(addprefix -I, $(INC))

############################## RULES ###########################################

all				:	$(NAME)

$(NAME)			:	$(OBJ)
	@ $(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@
	@ echo "$(GREEN)$(NAME) compilé$(WHITE)"

$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.c
	@ $(MKODIR)
	@ $(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean			:
	@ echo "$(RED)Suppression des .o$(WHITE)"
	@ $(RM) -rf $(OBJ_DIR)

fclean			:	clean
		@ $(RM) -f $(NAME)

re				:	fclean all

MKODIR			=	if [ ! -d $(OBJ_DIR) ]; then \
		$(MKDIR) $(OBJ_DIR); fi

############################## DISPLAY #########################################

YELLOW			=	\033[0;33m
RED				=	\033[0;31m
GREEN			=	\033[0;32m
WHITE			=	\x1b[0m

############################## OTHER ###########################################

.PHONY			:	clean fclean re all