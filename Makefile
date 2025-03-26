# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 20:05:41 by arcebria          #+#    #+#              #
#    Updated: 2025/03/25 18:08:48 by aguinea          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = src/main.c src/init_env.c src/tokenizer.c src/free_stuff.c src/parser.c src/syntax_analize.c src/parse_cmd.c src/exec_cmd.c src/redirections.c src/open_files.c src/handler_errors.c src/utils.c src/heredoc.c src/built_ins_commands.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

INCLUDE = inc/minishell.h libft/libft.h libft/ft_printf.h
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address


all: dir $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) Makefile
		@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME) -lreadline
		@echo "\033[31mPLVS VLTRA\033[0m"

dir:
	@make -C $(LIBFT_DIR) --silent

%.o: %.c $(INCLUDE)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean --silent
	@rm -f $(OBJS)
	@echo "\033[31mNON PLVS VLTRA\033[0m"

fclean: clean
	@make -C $(LIBFT_DIR) fclean --silent
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean
