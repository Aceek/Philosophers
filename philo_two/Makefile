# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/21 14:37:12 by ilinhard          #+#    #+#              #
#    Updated: 2022/10/11 03:30:43 by ilinhard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	philosphers_bonus

HEAD				=	-I .

SRCS				=	philosphers_bonus.c utils_bonus.c initialisation_bonus.c main_bonus.c cleaning_bonus.c

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