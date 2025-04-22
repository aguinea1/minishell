# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 20:05:41 by aguinea           #+#    #+#              #
#    Updated: 2025/04/22 11:59:56 by aguinea          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                              CONFIGURATION                                   #
################################################################################

NAME			= minishell
NAME_BONUS		= minishell_bonus

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g -fsanitize=address
DEPFLAGS		= -MMD -MF $(DEPDIR)/$*.d
LDFLAGS			= -lreadline

INCLUDE			= -Iinc -Ilibft -I/usr/include

SRCDIR			= src
OBJDIR			= obj
DEPDIR			= deps
LIBFT_DIR		= libft
INCLUDE_DIR		= inc

################################################################################
#                              SOURCE FILES                                    #
################################################################################

SRCS = \
	src/main/main.c \
	src/shell_loop/shell_loop.c \
	src/init/init_env.c \
	src/init/init_no_env.c \
	src/init/tokenizer.c \
	src/init/parser.c \
	src/init/parser_utils.c \
	src/init/tokenizer_handle_word.c \
	src/init/tokenizer_utils.c \
	src/init/expansor.c \
	src/init/parse_cmd.c \
	src/init/syntax_analize.c \
	src/setup_exec/open_files.c \
	src/setup_exec/setup_heredoc.c \
	src/setup_exec/expand_heredoc.c \
	src/setup_exec/setup_shell.c \
	src/exec/exec_cmd.c \
	src/exec/make_dup.c \
	src/exec/set_dup.c \
	src/exec/manage_heredoc.c \
	src/exec/check_builtins.c \
	src/exec/mini_cd.c \
	src/exec/mini_env_echo_pwd.c \
	src/exec/mini_unset.c \
	src/exec/mini_export.c \
	src/exec/mini_export_utils.c \
	src/exec/mini_export_create.c \
	src/exec/minicd_utils.c \
	src/exec/signals.c \
	src/clean_free/clean_fds.c \
	src/clean_free/free_structs.c \
	src/clean_free/put_errors.c

SRCS_BONUS = \
	src/main/main.c \
	src/shell_loop/shell_loop_bonus.c \
	src/init/init_env.c \
	src/init/init_no_env.c \
	src/init/tokenizer_bonus.c \
	src/init/parser.c \
	src/init/parser_utils.c \
	src/init/tokenizer_handle_word.c \
	src/init/tokenizer_utils.c \
	src/init/expansor.c \
	src/init/parse_cmd.c \
	src/init/syntax_analize.c \
	src/init/wildcard_bonus.c \
	src/init/wildcard_match_bonus.c \
	src/init/wildcard_utils_bonus.c \
	src/setup_exec/open_files.c \
	src/setup_exec/setup_heredoc.c \
	src/setup_exec/expand_heredoc.c \
	src/setup_exec/setup_shell.c \
	src/exec/exec_cmd.c \
	src/exec/make_dup.c \
	src/exec/set_dup.c \
	src/exec/manage_heredoc.c \
	src/exec/check_builtins.c \
	src/exec/mini_cd.c \
	src/exec/mini_env_echo_pwd.c \
	src/exec/mini_unset.c \
	src/exec/mini_export.c \
	src/exec/mini_export_utils.c \
	src/exec/mini_export_create.c \
	src/exec/minicd_utils.c \
	src/exec/signals.c \
	src/clean_free/clean_fds.c \
	src/clean_free/free_structs.c \
	src/clean_free/put_errors.c	\
	src/init/utils_normi.c

################################################################################
#                             OBJECTS & DEPS                                   #
################################################################################

OBJS			= $(SRCS:%.c=$(OBJDIR)/%.o)
OBJS_BONUS		= $(SRCS_BONUS:%.c=$(OBJDIR)/%.o)
DEPS			= $(OBJS:%.o=$(DEPDIR)/%.d)
DEPS_BONUS		= $(OBJS_BONUS:%.o=$(DEPDIR)/%.d)

LIBFT_A			= $(LIBFT_DIR)/libft.a
HEADERS			= inc/minishell.h libft/libft.h
HEADERS_BONUS	= inc/minishell_bonus.h libft/libft.h

################################################################################
#                              RULES                                           #
################################################################################

all: dir $(LIBFT_A) $(NAME)

bonus: dir $(LIBFT_A) $(NAME_BONUS)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(LDFLAGS) -o $@
	@echo "\033[1;33mMINI\033[0m"

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT_A) $(LDFLAGS) -o $@
	@echo "\033[1;33mMINI BONUS\033[0m"

$(OBJDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@) $(dir $(DEPDIR)/$*.d)
	@$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT_A):
	@make -C $(LIBFT_DIR) --silent

dir:
	@mkdir -p $(OBJDIR) $(DEPDIR)

clean:
	@make -C $(LIBFT_DIR) clean --silent
	@rm -rf $(OBJDIR) $(DEPDIR)
	@echo "\033[1;33mCHAU\033[0m"

fclean: clean
	@make -C $(LIBFT_DIR) fclean --silent
	@rm -f $(NAME) $(NAME_BONUS)

re: fclean all

-include $(DEPS)
-include $(DEPS_BONUS)

.PHONY: all clean fclean re dir bonus
