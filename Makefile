NAME		=	minishell
LIBFT		=	libft.a
CCF			=	@gcc $(CFLAGS)
RM			=	@rm -f
CFLAGS		=	-Wall -Wextra -Werror -g
PARSER_PATH	=	parser/
PARSER_SRCS	=	parser.c
GNL_PATH	=	gnl_dir/
GNL_SRCS	=	get_next_line.c get_next_line_utils.c
SRCS		=	$(addprefix $(PARSER_PATH), $(PARSER_SRCS)) \
				$(addprefix $(GNL_PATH), $(GNL_SRCS))
OBJS		=	$(SRCS:.c=.o)
LIB_DIR		=	libft/
HDR			=	includes/minishell.h $(GNL_PATH)/get_next_line.h
CYAN		=	\x1B[36m
MAGENTA		=	\x1B[35m
GREEN		=	\033[92m
ENDCOLOR	=	\x1B[0m

all:		$(NAME)

$(NAME):	$(OBJS) $(HDR)
			@make bonus -C $(LIB_DIR)
			@mv $(LIB_DIR)$(LIBFT) $(LIBFT)
			$(CCF) $(OBJS) $(LIBFT) -o $(NAME)
			@echo "${GREEN}"$(NAME)" is compiled${ENDCOLOR}"

clean:
			@make clean -C $(LIB_DIR)
			$(RM) $(LIBFT)
			$(RM) $(OBJS)
			@echo objs deleted

fclean:		clean
			@make fclean -C $(LIB_DIR)
			$(RM) $(NAME)
			@echo $(NAME) deleted

re:			fclean all

%.o:		%.c $(HDR)
			$(CCF) -c $< -o $@
			@echo $@ compilled

norm:
			norminette $(SRCS) ./includes

.PHONY:		all clean fclean re so bonus norm
