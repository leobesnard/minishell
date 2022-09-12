SRCDIR = src/
OBJDIR = bin/
INCDIR = include/
FTPATH = libft/
INDIR = $(FTPATH)include/
LIBFT = $(FTPATH)libft.a

SRC = main.c lexer.c parser.c parser_utils.c print_tools.c \
	free.c lexer_utils.c env.c env_utils.c builtin.c redirection.c command.c \
	builtin2.c command_utils.c signal.c global.c builtin_exit.c heredoc.c \
	command_exec.c expand.c command_bis.c builtin_utils.c expand_utils.c \
	command_fd.c command_path.c free2.c


OBJS = $(addprefix $(OBJDIR),$(SRC:.c=.o))

CFLAGS = -Wall -Wextra -Werror 
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
