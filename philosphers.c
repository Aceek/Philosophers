/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 00:43:38 by ilinhard          #+#    #+#             */
/*   Updated: 2022/09/22 07:21:37 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_eat(t_philosopher *philo, t_conditions *rules)
{
	pthread_mutex_lock(&rules->forks[philo->lfork]);
	ft_writing(philo, FORK);
	pthread_mutex_lock(&rules->forks[philo->rfork]);
	ft_writing(philo, FORK);
	// pthread_mutex_lock(&rules->m_eating);
	ft_writing(philo, EATING);
	philo->time_last_meal = ft_get_time();
	// pthread_mutex_unlock(&rules->m_eating);
	ft_sleeping(rules->time_eat);
	philo->eat_count++;
	pthread_mutex_unlock(&rules->forks[philo->lfork]);
	pthread_mutex_unlock(&rules->forks[philo->rfork]);
}

void	*ft_routine(void *arg)
{
	t_philosopher	*philo;
	t_conditions	*rules;

	philo = (t_philosopher *)arg;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(15000);
	while (!rules->state)
	{
		ft_eat(philo, rules);
		// break condition if philo tous mange
		ft_writing(philo, SLEEPING);
		ft_sleeping(rules->time_sleep);
		ft_writing(philo, THINKING);
	}
	return (NULL);
}

void	ft_state_check(t_philosopher *philo, t_conditions *rules)
{
	int	i;

	i = 0;
	while (!rules->state && i < rules->nb_philo)
	{
		pthread_mutex_lock(&rules->m_eating);
		if (philo[i].time_last_meal - ft_get_time() < (rules->time_death))
		{
			ft_writing(&philo[i], DIED);
			rules->state = 1;
		}
		pthread_mutex_unlock(&rules->m_eating);
		i++;
	}
}

void	ft_start(t_conditions *rules)
{
	int					i;
	t_philosopher	*philo;

	i = 0;
	philo = rules->philo;
	rules->first_timer = ft_get_time();
	while (i < rules->nb_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, &ft_routine, &(philo[i])))
			return ;
		philo[i].time_last_meal = ft_get_time();
		i++;
	}
	ft_state_check(philo, rules);
	// exit_launcher(...);
}

int	main(int ac, char **av)
{
	t_conditions	rules;

	if (ac != 5 && ac != 6)
		return (write(2, "Wrong numbers of args\n", 22), 1);
	if (ft_parsing(av, &rules))
		return (1);
	ft_start(&rules); // protect ??
	return (0);
}
