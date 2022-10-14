/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 00:43:38 by ilinhard          #+#    #+#             */
/*   Updated: 2022/10/14 07:06:09 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_eat(t_philosopher *philo, t_conditions *rules)
{
	pthread_mutex_lock(&rules->forks[philo->lfork]);
	if (ft_writing(philo, FORK))
		return (ft_unlock_mutex(philo, rules, 1));
	if (rules->nb_philo < 2)
		return (ft_unlock_mutex(philo, rules, 1));
	pthread_mutex_lock(&rules->forks[philo->rfork]);
	if (ft_writing(philo, FORK))
		return (ft_unlock_mutex(philo, rules, 2));
	pthread_mutex_lock(&rules->m_eating);
	philo->time_last_meal = ft_get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&rules->m_eating);
	if (ft_writing(philo, EATING))
		return (ft_unlock_mutex(philo, rules, 2));
	ft_sleeping(rules->time_eat, rules);
	if (ft_writing(philo, SLEEPING))
		return (ft_unlock_mutex(philo, rules, 2));
	pthread_mutex_unlock(&rules->forks[philo->rfork]);
	pthread_mutex_unlock(&rules->forks[philo->lfork]);
	return (0);
}

void	*ft_routine(void *arg)
{
	t_philosopher	*philo;
	t_conditions	*rules;

	philo = (t_philosopher *)arg;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(10000);
	while (1)
	{
		if (ft_eat(philo, rules))
			return (NULL);
		ft_sleeping(rules->time_sleep, rules);
		if (ft_writing(philo, THINKING))
			return (NULL);
		if (rules->nb_philo % 2)
			usleep(10000);
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
	while (1)
	{
		pthread_mutex_lock(&rules->m_eating);
		if (ft_get_time() - philo[i].time_last_meal > (rules->time_death))
		{
			ft_writing(&philo[i], DIED);
			pthread_mutex_unlock(&rules->m_eating);
			return ;
		}
		if (rules->nb_eat && ft_check_nb_eat(philo, rules))
		{
			pthread_mutex_lock(&rules->time);
			rules->state = 1;
			pthread_mutex_unlock(&rules->time);
			pthread_mutex_unlock(&rules->m_eating);
			break ;
		}
		pthread_mutex_unlock(&rules->m_eating);
		i++;
		if (i >= rules->nb_philo)
			i = 0;
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
		{
			rules->state = 1;
			write(2, "Threads create probs\n", 21);
			return ;
		}
		rules->verify_cleaning->thread_c++;
		pthread_mutex_lock(&rules->m_eating);
		philo[i].time_last_meal = ft_get_time();
		pthread_mutex_unlock(&rules->m_eating);
		i++;
	}
	i = 0;
	ft_state_check(philo, rules);
}
