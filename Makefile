# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 20:05:41 by arcebria          #+#    #+#              #
#    Updated: 2025/03/27 12:23:25 by aguinea          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


################################################################################
#                             COMPILATION & MORE                               #
################################################################################

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -fsanitize=address
DEPFLAGS	= -MMD -MF $(DEPDIR)/$*.d
INCLUDE		= -Iinc -Ilibft



################################################################################
#                                 PATH/TO/SRCS                                 #
################################################################################

SRCDIR		= src

OBJDIR		= obj

DEPDIR		= deps

LIBFT_DIR	= libft

INCLUDE_DIR	= inc

################################################################################
#                           SRCS & OBJS & DEPS                                 #
################################################################################


LIBFT_A		= $(LIBFT_DIR)/libft.a

HEADER		= $(INCLUDE_DIR)/minishell.h
HEAD_LIBFT	= $(LIBFT_DIR)/libft.h
ALL_HEADERS	= $(HEADER) $(HEAD_LIBFT)


SRCS 		= src/main/main.c src/init/init_env.c src/init/tokenizer.c src/init/expansor.c				\
       		src/exit_and_frees/free_stuff.c 										\
       		src/init/parser.c src/init/syntax_analize.c src/init/parse_cmd.c 		\
       		src/exec/exec_cmd.c src/exec/redirections.c 							\
       		src/others/open_files.c src/exit_and_frees/handler_errors.c 			\
       		src/others/utils.c  src/exec/built_ins_commands.c						\
       		src/others/signals.c src/init/init_no_env.c

OBJS 		= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS 		= $(OBJS:$(OBJDIR)/%.o=$(DEPDIR)/%.d)


################################################################################
#                              MAKEFILE RULES                                  #
################################################################################


all				: dir $(LIBFT_A) $(NAME)

$(NAME)			: $(OBJS) $(LIBFT_A) Makefile
				@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME) -lreadline
				@echo "\033[31mPLVS VLTRA\033[0m"

dir				:
				@mkdir -p $(OBJDIR) $(DEPDIR) $(dir $(OBJS)) $(dir $(DEPS))

$(LIBFT_A)		:
				@make -C $(LIBFT_DIR) --silent

$(OBJDIR)/%.o	: $(SRCDIR)/%.c $(ALL_HEADERS) | dir
				@$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDE) -c $< -o $@

clean			:
				@make -C $(LIBFT_DIR) clean --silent
				@rm -rf $(OBJDIR) $(DEPDIR)
				@echo "\033[31mNON PLVS VLTRA\033[0m"

fclean			: clean
				@make -C $(LIBFT_DIR) fclean --silent
				@rm -f $(NAME)	

re				: fclean all

-include $(DEPS)

.PHONY: all clean fclean re dir
