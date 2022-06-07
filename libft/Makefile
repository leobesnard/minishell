# DIRECTORIES

SRCDIR = src/
OBJDIR = bin/
INCDIR = include/
MANDIR = $(OBJDIR)mandatory/
EXTDIR = $(OBJDIR)extra/
PRINTDIR = $(EXTDIR)printf/

# NAME
SRCS = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_strlen.c ft_isprint.c ft_toupper.c ft_strlcpy.c ft_strlcat.c ft_tolower.c ft_putendl_fd.c ft_strchr.c ft_strrchr.c ft_strdup.c ft_strncmp.c ft_strnstr.c ft_atoi.c ft_memset.c ft_bzero.c ft_calloc.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c
SRCSBNS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
XFILES = get_next_line_bonus.c\
		printf/ft_printf.c\
		printf/ft_printf_utils.c\
		printf/ft_putfct.c

# FILES

OBJS = ${addprefix $(OBJDIR),$(SRCS:.c=.o)}
OBJSBNS = $(addprefix $(OBJDIR),$(SRCSBNS:.c=.o))
MANOBJ = $(addprefix $(MANDIR), $(SRCS:.c=.o))
EXTOBJ = $(addprefix $(EXTDIR), $(XFILES:.c=.o))

# SHORTCUTS

AR = ar rc
CC = gcc
RM = rm -f

# FLAGS

CFLAGS = -Wall -Wextra -Werror

# INCLUDES

INCPATH = -I$(INCDIR)

# BINARY

NAME = libft.a

# COMANDS

all: ${NAME}

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir $(OBJDIR) $(MANDIR) $(EXTDIR) $(PRINTDIR) 2> /dev/null || true
	$(CC) -c ${CGLAGS} $(INCPATH) $< -o $@

${NAME}: ${MANOBJ} $(EXTOBJ)
	$(AR) ${NAME} ${MANOBJ} $(EXTOBJ)

clean:
	$(RM) ${MANOBJ} ${EXTOBJ}
	rmdir $(PRINTDIR) $(MANDIR) $(EXTDIR) $(OBJDIR) 2> /dev/null || true

fclean: clean
	$(RM) ${NAME}

re: fclean all

.PHONY: all libft clean fclean re
