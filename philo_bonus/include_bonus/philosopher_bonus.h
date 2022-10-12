/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 07:37:08 by ilinhard          #+#    #+#             */
/*   Updated: 2022/10/12 03:01:29 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

struct	s_conditions;

enum e_state
{
	FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

typedef struct s_philosopher
{
	int					id;
	int					eat_count;
	pid_t				process_id;
	long long			time_last_meal;
	pthread_t			thread_id;
	pthread_t			t_cleaner;
	struct s_conditions	*rules;
}						t_philosopher;

typedef struct s_conditions
{
	int						nb_philo;
	int						time_death;
	int						time_eat;
	int						time_sleep;
	int						nb_eat;
	int						state;
	long long				first_timer;
	struct s_philosopher	*philo;
	pthread_t				t_eat;
	sem_t					*cleaner;
	sem_t					*ending;
	sem_t					*all_eat;
	sem_t					*m_eating;
	sem_t					*forks;
	sem_t					*writing;
}							t_conditions;

//-----------------------initialisation.c-----------------------//
void		ft_empty_sem(t_conditions *rules);
int			ft_semaphore_init(t_conditions *rules);
int			ft_philo_init(t_conditions *rules, int nb_philo);
int			ft_parsing(char **av, t_conditions *rules);

//-----------------------Philosopher.c--------------------------//
void		*ft_state_check(void *philo);
void		ft_create_process(t_philosopher *philo);
void		*ft_check_eat_count(void *conditions);
int			ft_eat(t_philosopher *philo, t_conditions *rules);
int			ft_start(t_conditions *rules);

//-----------------------Utils.c-------------------------------//
int			ft_atoi(char *str);
long long	ft_get_time(void);
void		ft_sleeping(long long time, t_conditions *rules);
void		ft_writing(t_philosopher *philo, int state);

//-----------------------Cleaning.c-------------------------------//
void		ft_exit_clean(t_conditions *rules);
void		*ft_end_clean(void *condition);
void		ft_exit(t_conditions *rules, t_philosopher *philo);

#endif