/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 07:37:08 by ilinhard          #+#    #+#             */
/*   Updated: 2022/10/08 00:51:59 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

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
	int					eating;
	int					id;
	int					eat_count;
	pid_t				process_id;
	long long			time_last_meal;
	pthread_t			thread_id;
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
	sem_t					*m_eating;
	sem_t					*forks;
	sem_t					*writing;
}							t_conditions;

//-----------------------initialisation.c-----------------------//
int			ft_parsing(char **av, t_conditions *rules);
int			ft_philo_init(t_conditions *rules, int nb_philo);
int			ft_semaphore_init(t_conditions *rules);

//-----------------------Philosopher.c--------------------------//
void		ft_start(t_conditions *rules);
void		*ft_state_check(void *philo);
void		ft_eat(t_philosopher *philo ,t_conditions *rules);
int			ft_check_nb_eat(t_philosopher *philo, t_conditions *rules);
void		*ft_routine(void *arg);

//-----------------------Utils.c-------------------------------//
void		ft_exit_clean(t_conditions *rules);
void		ft_writing(t_philosopher *philo, int state);
void		ft_sleeping(long long time, t_conditions *rules);
long long	ft_get_time(void);
int			ft_atoi(char *str);

#endif