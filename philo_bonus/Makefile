# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/21 14:37:12 by ilinhard          #+#    #+#              #
#    Updated: 2022/10/11 05:59:54 by ilinhard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	philo_bonus

HEAD				=	-I include_bonus

SRCS				=	philosophers_bonus.c utils_bonus.c initialisation_bonus.c main_bonus.c cleaning_bonus.c

OBJ					=	${addprefix srcs/,${SRCS:.c=.o}}

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