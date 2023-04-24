# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 21:12:07 by lspohle           #+#    #+#              #
#    Updated: 2023/04/24 21:29:47 by cschmied         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH			:= sources

NAME			= minishell
				
LIBFT			= libft

SRCS			:= main.c lexer.c ft_readline.c

#SRCS			= mandatory/main.c \
#				  mandatory/execute.c \
#				  mandatory/exit.c \
#				  mandatory/split.c \

OBJS			= ${SRCS:.c=.o}

CC				= cc

CFLAGS			= -Wall -Wextra -Werror -g -lreadline

RM				= rm -f

# Colors
GREEN			= \033[92m
YELLOW			= \033[0;33m
BLUE			= \033[0;34m
MAGENTA			= \033[0;35m
ESCAPE			= \033[0m

%.o: %.c		
				@${CC} -c $^ -o $@

${NAME}:		${OBJS} ${LIBFT}/libft.a
				@${CC} ${CFLAGS} ${OBJS} -L ${LIBFT} -lft -o ${NAME}
				@echo "${GREEN}******************  COMPILED  *******************${ESCAPE}"
				@echo "${BLUE}********* WE GOT THIS! TEAM COMPETENCE! *********${ESCAPE}"

${LIBFT}/libft.a:
				@echo "${YELLOW}******************  COMPILING  ******************${ESCAPE}"
				@make bonus -C ${LIBFT}		

all:			${NAME}

clean:	
				@${RM} ${OBJS}
				@${RM} ${BOBJS}
				@make clean -C ${LIBFT}
				@echo "${GREEN}*******************  CLEANED  *******************${ESCAPE}"

fclean:			clean
				@${RM} ${NAME}
				@make fclean -C ${LIBFT}

re:				fclean all

.PHONY:			all clean fclean re
