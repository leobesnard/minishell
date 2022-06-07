SRCDIR = src/
OBJDIR = bin/
INCDIR = include/
FTPATH = libft/
INDIR = $(FTPATH)include/
LIBFT = $(FTPATH)libft.a

#################################################################
src = main.c\

OBJS = ${addprefix $(OBJDIR),$(src:.c=.o)}
#################################################################
CFLAGS = -Wall -Wextra -Werror
LINK = -lft -lreadline
CC = gcc
INCPATH = -I$(INCDIR) -I$(INDIR)
LIBPATH = -L$(FTPATH)
NAME = minishell

all: ${NAME}
 
$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) $(INCPATH) -c $< -o $@

${NAME}: ${OBJS} $(LIBFT) $(MLX)
	$(CC) ${OBJS} $(LIBPATH) $(LINK) -o $(NAME)

$(LIBFT): 
	make -C $(FTPATH)

lft:
	make -C $(FTPATH)

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all libft clean fclean re
