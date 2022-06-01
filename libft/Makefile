SRCDIR = src/
OBJDIR = bin/
INCDIR = include/
#####################################################################
MANDIR = mandatory/
EXTDIR = extra/
#####################################################################
SRCS = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_strlen.c ft_isprint.c ft_toupper.c ft_strlcpy.c ft_strlcat.c ft_tolower.c ft_putendl_fd.c ft_strchr.c ft_strrchr.c ft_strdup.c ft_strncmp.c ft_strnstr.c ft_atoi.c ft_memset.c ft_bzero.c ft_calloc.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c
SRCSBNS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
XFILES = get_next_line_bonus.c\
		printf/ft_printf.c\
		printf/ft_printf_utils.c\
		printf/ft_putfct.c

OBJS = ${addprefix $(OBJDIR),$(SRCS:.c=.o)}
OBJSBNS = ${addprefix $(OBJDIR),$(SRCSBNS:.c=.o)}
#####################################################################
MANOBJ = $(addprefix $(OBJDIR), $(addprefix $(MANDIR), $(SRCS:.c=.o)))
EXTOBJ = $(addprefix $(OBJDIR), $(addprefix $(EXTDIR), $(XFILES:.c=.o)))
#####################################################################
AR = ar rc
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCPATH = -I$(INCDIR)

NAME = libft.a

all: ${NAME}

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) -c ${CGLAGS} $(INCPATH) $< -o $@

${NAME}: ${MANOBJ} $(EXTOBJ)
	$(AR) ${NAME} ${MANOBJ} $(EXTOBJ)

clean:
	rm -f ${MANOBJ} ${EXTOBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all libft clean fclean re
