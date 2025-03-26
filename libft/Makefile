
NAME = libft.a

FLAGS = -Wall -Wextra -Werror
HBONUS = .bonus

SRCS =  ft_isascii.c \
	ft_memcpy.c \
	ft_putstr_fd.c \
	ft_strlcat.c  \
	ft_strrchr.c \
	ft_atoi.c \
	ft_isdigit.c \
	ft_memmove.c \
	ft_split.c \
	ft_strlcpy.c \
	ft_strtrim.c \
	ft_bzero.c \
	ft_isprint.c \
	ft_memset.c \
	ft_strchr.c \
	ft_strlen.c \
	ft_substr.c \
	ft_calloc.c \
	ft_itoa.c \
	ft_putchar_fd.c \
	ft_strdup.c \
	ft_strmapi.c \
	ft_tolower.c \
	ft_isalnum.c \
	ft_memchr.c \
	ft_putendl_fd.c \
	ft_striteri.c \
	ft_strncmp.c \
	ft_toupper.c \
	ft_isalpha.c \
	ft_memcmp.c \
	ft_putnbr_fd.c \
	ft_strjoin.c \
	ft_strnstr.c \
	ft_free_array.c\
	ft_free_int_array.c\
	ft_strspn.c \
	ft_strcspn.c \
	ft_strcmp.c \
	ft_isspecial.c \
	ft_isspace.c \
	ft_strcpy.c \
	ft_strcat.c \
	ft_printf.c type_cs.c type_num.c type_xXp.c


BSRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: .bonus

$(HBONUS): $(BOBJS)
	ar rc $(NAME) $(BOBJS)

%.o : %.c libft.h ft_printf.h Makefile
	cc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BOBJS)
	rm -f .bonus
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: bonus all clean fclean re
