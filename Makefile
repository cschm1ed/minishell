# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 21:12:07 by lspohle           #+#    #+#              #
#    Updated: 2023/04/26 11:11:16 by cschmied         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH			:= sources:sources/utils

NAME			:= minishell
				
LIBFT			:= libft

UTILS			:= ft_isspace.c str_arr_add.c

SRCS			:= $(UTILS) main.c lexer.c parser.c ft_readline.c

OBJS			:= ${SRCS:.c=.o}

CC				:= cc

CFLAGS			:= -g -Wall -Wextra -Werror -O2

LDFLAGS			:= -Wall -Werror -Wextra -g -lreadline

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
