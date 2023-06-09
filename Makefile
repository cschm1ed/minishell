# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 21:12:07 by lspohle           #+#    #+#              #
#    Updated: 2023/06/14 08:22:55 by lspohle          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH       := sources:sources/utils:sources/lexer:sources/parser:sources/builtins:sources/executer:libft

BUILDDIR    := build
LIBFTDIR    := libft

# File names
NAME        := minishell
LIBFT       := libft.a

# Source files
UTILS       := ft_isspace.c ft_isspecial.c str_arr_utils.c ft_isredirect.c ft_isquote.c  \
               init_and_delete_structs.c lst_utils1.c lst_utils2.c ft_strcmp.c free_and_exit.c \
               unexpected_token.c ft_strsjoin.c signals.c

LEXER       := lexer.c lexer_checks.c lexer_utils.c lexer_split.c lexer_trim.c lexer_replace_vars.c
PARSER      := parser.c parser_utils.c
BUILTINS    := echo.c env.c pwd.c export.c exit.c unset.c export_utils.c cd.c
EXECUTER    := execute_builtin_if.c executer_utils.c executer_main.c executer_execute.c execute_heredoc.c executer_path.c
OTHER_SRCS  := ft_readline.c main.c

SRCS        := $(UTILS) $(LEXER) $(PARSER) $(BUILTINS) $(EXECUTER) $(OTHER_SRCS)

# Objects
OBJS        := $(SRCS:%.c=$(BUILDDIR)/%.o)

# Compiler
CC          := cc
CFLAGS      := -g -Wall -Werror -Wextra -I ./includes -I ./libft -O2 -D BUFFER_SIZE=25
LDFLAGS     := -g -Wall -Werror -Wextra -I ./includes -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline
MAKE        := make
RM          := rm -f

# Colors
GREEN       := \033[92m
YELLOW      := \033[0;33m
BLUE        := \033[0;34m
ESCAPE      := \033[0m

# Build rules
$(NAME): $(OBJS)
	@$(CC) $(LDFLAGS) $^ $(LIBFTDIR)/$(LIBFT) -o $(NAME)
	@echo "$(BLUE)$$HEADER $(ESCAPE)"

$(BUILDDIR)/%.o: %.c | $(BUILDDIR) $(LIBFTDIR)/$(LIBFT)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW)compiling > $< $(ESCAPE)"

$(BUILDDIR):
	@mkdir $(BUILDDIR)

$(LIBFTDIR)/$(LIBFT):
	@$(MAKE) bonus -C $(LIBFTDIR)

# Standard rules
all: $(NAME)

clean:
	@$(RM) -rf $(BUILDDIR)
	@$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re

.PHONY: all clean fclean re

info: header

define HEADER
    __  ____       _      __         ____
   /  |/  (_____  (______/ /_  ___  / / /
  / /|_/ / / __ \/ / ___/ __ \/ _ \/ / /
 / /  / / / / / / (__  / / / /  __/ / /
/_/  /_/_/_/ /_/_/____/_/ /_/\___/_/_/

endef
export HEADER
