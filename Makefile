NAME	=	philo

all		:	${NAME}
			make -C philo

${NAME} :
			all

bonus	:
			make -C philo_bonus

clean	:
			make clean -C philo
			make clean -C philo_bonus

fclean	:	clean
			make fclean -C philo
			make fclean -C philo_bonus

re		:	fclean all bonus