/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 07:37:08 by ilinhard          #+#    #+#             */
/*   Updated: 2022/09/22 04:23:51 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

struct	s_conditions;

enum state
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
	int					lfork;
	int					rfork;
	int					state;
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
	long long				first_timer;
	struct s_philosopher	*philo;
	pthread_mutex_t			m_eating;
	pthread_mutex_t			*forks;
	pthread_mutex_t			writing;
}							t_conditions;

int			ft_atoi(char *str);
int			ft_parsing(char **av, t_conditions *rules);
int			ft_mutex_init(t_conditions *rules);
long long	ft_get_time(void);

#endif