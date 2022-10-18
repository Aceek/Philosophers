# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/21 14:37:12 by ilinhard          #+#    #+#              #
#    Updated: 2022/10/18 22:21:05 by ilinhard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	philo

HEAD				=	-I include

SRCS				=	philosophers.c utils.c initialisation.c main.c cleaning.c

OBJ					=	${addprefix srcs/,${SRCS:.c=.o}}

CC					=	gcc

CFLAGS				=	-Wall -Werror -Wextra -g -pthread #-fsanitize=thread

${NAME}				:	${OBJ}
					${CC} ${CFLAGS} ${OBJ} -o ${NAME}

all					:	${NAME}

.c.o				:
					${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

clean				:
					@rm -rf ${OBJ}

fclean				:	clean
					@rm -rf ${NAME}

bonus				:
					make -C ../philo_bonus

re					:	fclean all

.PHONY				:	all clean fclean re