CC				=	/usr/bin/gcc

CFLAGS			=	

MAKE			=	/usr/bin/make

RM				=	/bin/rm

NAME			=	proc

SRC_DIR			=	srcs

SRC_NAME		=	process_execute.c get_instruction_parameter.c local_debug.c \
		local_main.c op_and.c op_jmpz.c op_live.c op_st.c read_from_register.c \
		read_from_vm.c vm_query.c vm_set.c vm_read_player.c \
		write_to_register.c write_to_vm.c ocp_tools.c ncurse_print_mem.c

SRC				=	$(addprefix $(SRC_DIR)/,$(SRC_NAME))

OBJ_DIR			=	objs

OBJ_NAME		=	$(SRC_NAME:.c=.o)

OBJ				=	$(addprefix $(OBJ_DIR)/,$(OBJ_NAME))

LIB_DIR			=	./../../libft

LDLIBS			=	-lft -lncurses

LDFLAGS			=	-L $(LIB_DIR)

INC				=	./../../includes/

CPPFLAGS		=	$(addprefix -I, $(VMINC) $(PROCINC))

############################## RULES ###########################################

all				:	$(NAME)

$(NAME)			:	$(OBJ)
	$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@
	@ echo "$(GREEN)$(NAME) compilé$(WHITE)"

$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.c
	@ mkdir $(OBJ_DIR) 2> /dev/null || true
	 $(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean			:
	@ echo "$(RED)Suppression des .o$(WHITE)"
	@ $(RM) -rf $(OBJ_DIR)

fclean			:	clean
	@ $(RM) -f $(NAME)

re				:	fclean all

############################## DISPLAY #########################################

YELLOW			=	\033[0;33m
RED				=	\033[0;31m
GREEN			=	\033[0;32m
WHITE			=	\x1b[0m

############################## OTHER ###########################################

.PHONY			:	clean fclean re all
