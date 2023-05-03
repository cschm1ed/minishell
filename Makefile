# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 21:12:07 by lspohle           #+#    #+#              #
#    Updated: 2023/05/01 12:06:45 by cschmied         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH			:= sources:sources/utils:sources/lexer:sources/parser:sources/builtins

BUILDDIR		:= build

NAME			:= minishell
				
LIBFTDIR		:= libft

LIBFT			:= libft.a

UTILS			:= ft_isspace.c ft_isspecial.c str_arr_add.c ft_isredirect.c ft_isquote.c info_init.c\
					ft_lstrmone.c delete_variable.c var_lst_add.c lst_get_var.c find_var_val.c lst_find_var_val.c\
					str_in_arr.c ft_strcmp.c str_arr_to_lst.c replace_variables.c

LEXER			:= lexer.c lexer_checks.c lexer_utils.c

PARSER			:= find_and_remove_redirects.c find_and_remove_delimiter_and_append.c\
					parser.c

BUILTINS		:= echo.c env.c pwd.c export.c

SRCS			:= $(UTILS) $(BUILTINS) $(LEXER) $(PARSER) ft_readline.c main.c

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
