/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 07:37:08 by ilinhard          #+#    #+#             */
/*   Updated: 2022/09/21 04:52:26 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

struct s_conditions;

typedef struct s_philosopher
{
	int					eating;
	int					time_last_meal;
	int					id;
	int					eat_count;
	int					lfork;
	int					rfork;
	struct s_conditions	*rules;
}						t_philosopher;


typedef struct s_conditions
{
	int						nb_philo;
	int						time_death;
	int						time_eat;
	int						time_sleep;
	int						nb_eat;
	struct s_philosopher	*philo;
	pthread_mutex_t			m_eating;
	pthread_mutex_t			*forks;
	pthread_mutex_t			writing;
}							t_conditions;

int	ft_atoi(char *str);

int	ft_parsing(char **av, t_conditions *rules);
int	ft_mutex_init(t_conditions *rules);

#endif