# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 21:12:07 by lspohle           #+#    #+#              #
#    Updated: 2023/05/12 16:20:37 by lspohle          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH			:= sources:sources/utils:sources/lexer:sources/parser:sources/builtins:sources/executer:libft

BUILDDIR		:= build

NAME			:= minishell
				
LIBFTDIR		:= libft

LIBFT			:= libft.a

UTILS			:= ft_isspace.c ft_isspecial.c str_arr_add.c ft_isredirect.c ft_isquote.c info_init.c\
					ft_lstrmone.c delete_struct.c var_lst_add.c lst_get_struct.c find_var_val.c lst_find_var_val.c\
					str_in_arr.c ft_strcmp.c str_arr_to_lst.c ft_isvariable.c utils.c\
					unexpected_token.c ft_strsjoin.c lst_new_node.c

LEXER			:= lexer.c lexer_checks.c lexer_utils.c lexer_split.c lexer_trim.c lexer_replace_vars.c

PARSER			:= find_and_remove_redirects.c find_and_remove_delimiter_and_append.c\
					parser.c

BUILTINS		:= echo.c env.c pwd.c export.c exit.c unset.c export_utils.c cd.c

EXECUTER		:= executer.c execute_builtin_if.c executer_utils.c pipex_main.c pipex_execute.c

SRCS			:= $(UTILS) $(BUILTINS) $(LEXER) $(PARSER) $(EXECUTER) ft_readline.c main.c

OBJS			:= $(SRCS:%.c=$(BUILDDIR)/%.o)

CC				:= cc

CFLAGS			:= -g -Wall -Wextra -O2

LDFLAGS			:= -lreadline -g -Wall -Wextra

RM				:= rm -f

MAKE			:= make

# Colors
GREEN			:= \033[92m
YELLOW			:= \033[0;33m
BLUE			:= \033[0;34m
MAGENTA			:= \033[0;35m
ESCAPE			:= \033[0m

$(BUILDDIR)/%.o: %.c $(BUILDDIR)
				@${CC} $(CFLAGS) -c $< -o $@

${NAME}:		$(OBJS) $(LIBFTDIR)/$(LIBFT)
				@$(CC) $(LDFLAGS) $^ $(LIBFTDIR)/$(LIBFT) -o $(NAME)
				@echo "$(GREEN)******************  COMPILED  *******************$(ESCAPE)"
				@echo "$(BLUE)********* WE GOT THIS! TEAM COMPETENCE! *********$(ESCAPE)"


${LIBFTDIR}/libft.a:
				@echo "$(YELLOW)******************  COMPILING  ******************$(ESCAPE)"
				@$(MAKE) bonus -C $(LIBFTDIR)

$(BUILDDIR):
				@mkdir $(BUILDDIR)

all:			$(NAME)

clean:
				@$(RM) -rf $(BUILDDIR)
				@$(MAKE) clean -C $(LIBFTDIR)
				@echo "$(GREEN)*******************  CLEANED  *******************$(ESCAPE)"

fclean:			clean
				@$(RM) $(NAME)
				@$(MAKE) fclean -C $(LIBFTDIR)

re:				fclean all

.PHONY:			all clean fclean re
