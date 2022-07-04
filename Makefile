SRCDIR = src/
OBJDIR = bin/
INCDIR = include/
FTPATH = libft/
INDIR = $(FTPATH)include/
LIBFT = $(FTPATH)libft.a

SRC = main.c lexer.c parser.c parser_utils.c print_tools.c command_utils.c command.c redirection.c

OBJS = $(addprefix $(OBJDIR),$(SRC:.c=.o))

CFLAGS = -Wall -Wextra -Werror -g
LINK = -lft -lreadline

CC = gcc -g

INCPATH = -I$(INCDIR) -I$(INDIR)
LIBPATH = -L$(FTPATH)


NAME = minishell

all: $(NAME)
 
$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) $(INCPATH) -c $< -o $@

$(NAME): $(OBJDIR) $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBPATH) $(LINK) -o $(NAME)

$(LIBFT): 
	@printf "Compiling libft...\n"
	@$(MAKE) -s -C $(FTPATH)
	@printf "Done!\n\n"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

libclean:
	$(MAKE) -C $(FTPATH) fclean

re: fclean all

.PHONY: all libft clean fclean re
