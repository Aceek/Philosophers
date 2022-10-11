/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 07:40:04 by ilinhard          #+#    #+#             */
/*   Updated: 2022/10/11 04:03:07 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	*ft_state_check(void *philo)
{
	t_philosopher	*phi;
	t_conditions	*rules;
	int				done;

	phi = (t_philosopher *)philo;
	rules = phi->rules;
	done = 0;
	while (!rules->state)
	{
		sem_wait(rules->m_eating);
		if ((ft_get_time() - phi->time_last_meal) > rules->time_death)
		{
			ft_writing(philo, DIED);
			rules->state = 1;
			sem_post(rules->ending);
		}
		sem_post(rules->m_eating);
		if (!done && rules->nb_eat && phi->eat_count >= rules->nb_eat)
		{
			sem_post(rules->all_eat);
			done = 1;
		}
		usleep(50);
	}
	return (NULL);
}

int	ft_eat(t_philosopher *philo, t_conditions *rules)
{
	sem_wait(rules->forks);
	ft_writing(philo, FORK);
	if (rules->nb_philo < 2)
		return (1);
	sem_wait(rules->forks);
	ft_writing(philo, FORK);
	sem_wait(rules->m_eating);
	ft_writing(philo, EATING);
	philo->eat_count += 1;
	philo->time_last_meal = ft_get_time();
	sem_post(rules->m_eating);
	ft_sleeping(rules->time_eat, rules);
	sem_post(rules->forks);
	sem_post(rules->forks);
	return (0);
}

void	ft_create_process(t_philosopher *philo)
{
	t_conditions	*rules;

	if (philo->id % 2)
		usleep(30000);
	rules = philo->rules;
	sem_wait(rules->all_eat);
	philo->time_last_meal = ft_get_time();
	pthread_create(&(philo->t_cleaner), NULL, &ft_end_clean, (void *)rules);
	pthread_create(&(philo->thread_id), NULL, &ft_state_check, (void *)philo);
	while (!rules->state)
	{
		if (ft_eat(philo, rules))
			ft_sleeping((rules->time_death * 2), rules);
		if (rules->state)
			break ;
		ft_writing(philo, SLEEPING);
		ft_sleeping(rules->time_sleep, rules);
		ft_writing(philo, THINKING);
	}
	ft_exit(rules, philo);
	exit (0);
}

void	*ft_check_eat_count(void *conditions)
{
	int				i;
	t_conditions	*rules;

	rules = (t_conditions *)conditions;
	i = 0;
	while (!rules->state && i < rules->nb_philo)
	{
		sem_wait(rules->all_eat);
		i++;
		if (rules->state || i >= rules->nb_philo)
		{
			sem_post(rules->ending);
			return (NULL);
		}
		usleep(50);
	}
	return (NULL);
}

int	ft_start(t_conditions *rules)
{
	int				i;
	t_philosopher	*phi;

	phi = rules->philo;
	rules->first_timer = ft_get_time();
	i = 0;
	while (i < rules->nb_philo)
	{
		phi[i].process_id = fork();
		if (phi[i].process_id < 0)
			return (1);
		if (phi[i].process_id == 0)
			ft_create_process(&phi[i]);
		i++;
	}
	if (pthread_create(&(rules->t_eat), NULL,
			&ft_check_eat_count, (void *)rules))
		return (1);
	sem_wait(rules->cleaner);
	return (0);
}
