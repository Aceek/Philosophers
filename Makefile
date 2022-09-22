# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/21 14:37:12 by ilinhard          #+#    #+#              #
#    Updated: 2022/09/21 02:41:14 by ilinhard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	philosophers

HEAD				=	-I .

SRCS				=	philosphers.c utils.c initialisation.c

OBJ					=	${SRCS:.c=.o}

CC					=	gcc

CFLAGS				=	-Wall -Werror -Wextra -g -pthread

${NAME}				:	${OBJ}
					${CC} ${CFLAGS} ${OBJ} -o ${NAME}
all					:	${NAME}

.c.o				:
					${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

clean				:
					@rm -rf ${OBJ}

fclean				:	clean
					@rm -rf ${NAME}
					
re					:	fclean all

.PHONY				:	all clean fclean re