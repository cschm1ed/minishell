# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 21:12:07 by lspohle           #+#    #+#              #
#    Updated: 2023/04/28 21:03:11 by lspohle          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH			:= sources:sources/utils:sources/lexer:sources/parser:sources/builtin

NAME			:= minishell
				
LIBFT			:= libft

UTILS			:= ft_isspace.c ft_isspecial.c str_arr_add.c ft_isredirect.c ft_isquote.c

LEXER			:= lexer.c lexer_checks.c lexer_utils.c

SRCS			:= $(UTILS) $(LEXER) main.c parser.c ft_readline.c pwd.c echo.c

OBJS			:= ${SRCS:.c=.o}

CC				:= cc

CFLAGS			:= -g -Wall -Wextra -O2
# CFLAGS			:= -g -Wall -Wextra -Werror -O2

LDFLAGS			:= -Wall -Wextra -g -lreadline
# LDFLAGS			:= -Wall -Werror -Wextra -g -lreadline

RM				:= rm -f

MAKE			:= make

# Colors
GREEN			:= \033[92m
YELLOW			:= \033[0;33m
BLUE			:= \033[0;34m
MAGENTA			:= \033[0;35m
ESCAPE			:= \033[0m

%.o: %.c		
				@${CC} $(CFLAGS) -c $^ -o $@

${NAME}:		${OBJS} ${LIBFT}/libft.a
				@${CC} ${LDFLAGS} ${OBJS} -L ${LIBFT} -lft -o ${NAME}
				@echo "${GREEN}******************  COMPILED  *******************${ESCAPE}"
				@echo "${BLUE}********* WE GOT THIS! TEAM COMPETENCE! *********${ESCAPE}"


${LIBFT}/libft.a:
				@echo "${YELLOW}******************  COMPILING  ******************${ESCAPE}"
				@$(MAKE) bonus -C ${LIBFT}		

all:			${NAME}

clean:	
				@${RM} ${OBJS}
				@${RM} ${BOBJS}
				@$(MAKE) clean -C ${LIBFT}
				@echo "${GREEN}*******************  CLEANED  *******************${ESCAPE}"

fclean:			clean
				@${RM} ${NAME}
				@$(MAKE) fclean -C ${LIBFT}

re:				fclean all

.PHONY:			all clean fclean re
