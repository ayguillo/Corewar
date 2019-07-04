CC				=	/usr/bin/gcc

CFLAGS			=	

MAKE			=	/usr/bin/make

RM				=	/bin/rm

MKDIR			=	/bin/mkdir -p

NAME			=	corewar

TARGET			=	../$(NAME)

SRC_DIR			=	srcs

VM_DIR			=	vm

VM_SRC			= 	$(addprefix $(VM_DIR)/, \
		vm_main.c vm_options.c vm_process.c vm_read_player.c vm_errors.c \
		vm_arena.c vm_game.c)

PROC_DIR		=	process

PROC_SRC		=	$(addprefix $(PROC_DIR)/, \
		process_execute.c get_instruction_parameter.c local_debug.c \
		op_and.c op_jmpz.c op_live.c op_st.c read_from_register.c \
		read_from_vm.c vm_query.c vm_set.c write_to_register.c \
		write_to_vm.c ocp_tools.c)

DISP_DIR		=	display

DISP_SRC		=	$(addprefix $(DISP_DIR)/, \
		print_memory.c)

SRC_NAME		=	$(VM_SRC) $(PROC_SRC) $(DISP_SRC)

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

all				:	$(TARGET)

$(TARGET)		:	$(OBJ)
	@ $(MAKE) -C $(LIB_DIR) 2> /dev/null 1> /dev/null
	@ $(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@
	@ echo "$(GREEN)$(NAME) compilé$(WHITE)"

$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.c
	 @ $(MKODIR)
	 @ $(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean			:
	@ echo "$(RED)Suppression des .o$(WHITE)"
	@ $(RM) -rf $(OBJ_DIR)

fclean			:	clean
		@ $(RM) -f $(TARGET)

re				:	fclean all

MKODIR			=	if [ ! -d $(OBJ_DIR) ]; then \
		 $(MKDIR) $(OBJ_DIR); \
		 $(MKDIR) $(OBJ_DIR)/$(VM_DIR); \
		 $(MKDIR) $(OBJ_DIR)/$(PROC_DIR); \
		 $(MKDIR) $(OBJ_DIR)/$(DISP_DIR); fi

############################## DISPLAY #########################################

YELLOW			=	\033[0;33m
RED				=	\033[0;31m
GREEN			=	\033[0;32m
WHITE			=	\x1b[0m

############################## OTHER ###########################################

.PHONY			:	clean fclean re all
