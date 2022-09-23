/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 00:43:38 by ilinhard          #+#    #+#             */
/*   Updated: 2022/09/23 07:21:35 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_eat(t_philosopher *philo, t_conditions *rules)
{
	pthread_mutex_lock(&rules->forks[philo->lfork]);
	ft_writing(philo, FORK);
	pthread_mutex_lock(&rules->forks[philo->rfork]);
	ft_writing(philo, FORK);
	pthread_mutex_lock(&rules->m_eating);
	ft_writing(philo, EATING);
	philo->time_last_meal = ft_get_time();
	pthread_mutex_unlock(&rules->m_eating);
	ft_sleeping(rules->time_eat, rules);
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
		if (rules->state)
			break ;
		ft_writing(philo, SLEEPING);
		ft_sleeping(rules->time_sleep, rules);
		ft_writing(philo, THINKING);
	}
	return (NULL);
}

int	ft_check_nb_eat(t_philosopher *philo, t_conditions *rules)
{
	int	i;

	i = 0;
	while (1)
	{
		if (rules->nb_eat > philo[i].eat_count)
			return (0);
		if (i + 1 >= rules->nb_philo)
			return (1);
		i++;
	}
	return (0);
}

void	ft_state_check(t_philosopher *philo, t_conditions *rules)
{
	int	i;

	i = 0;
	while (!rules->state && i < rules->nb_philo)
	{
		pthread_mutex_lock(&rules->m_eating);
		if (ft_get_time() - philo[i].time_last_meal > (rules->time_death))
		{
			ft_writing(&philo[i], DIED);
			rules->state = 1;
		}
		pthread_mutex_unlock(&rules->m_eating);
		i++;
		if (i + 1 >= rules->nb_philo)
			i = 0;
		if (rules->nb_eat && ft_check_nb_eat(philo, rules))
			rules->state = 1;
		usleep(50);
	}
}

void	ft_start(t_conditions *rules)
{
	int					i;
	t_philosopher		*philo;

	i = 0;
	philo = rules->philo;
	rules->first_timer = ft_get_time();
	while (i < rules->nb_philo)
	{
		if (pthread_create(&(philo[i].thread_id),
				NULL, &ft_routine, &(philo[i])))
			return ;
		philo[i].time_last_meal = ft_get_time();
		i++;
	}
	ft_state_check(philo, rules);
}
