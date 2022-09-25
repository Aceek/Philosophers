/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 07:40:04 by ilinhard          #+#    #+#             */
/*   Updated: 2022/09/25 08:02:55 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_state_check(void *philo)
{
	t_philosopher	*phi;
	t_conditions	*rules;

	phi = (t_philosopher *)philo;
	rules = phi->rules;
	while (!rules->state)
	{
		if (ft_get_time() - phi->time_last_meal > rules->time_death)
		{
			ft_writing(philo, DIED);
			rules->state = 1;
			break ;
		}
	}
}

void	ft_create_process(t_philosopher *philo)
{
	t_conditions *rules;

	rules = philo->rules;
	philo->time_last_meal = ft_get_time();
	pthread_create(&(philo->thread_id), NULL, &ft_state_check, (void *)&philo);
	if (philo->id % 2)
		usleep(15000);
	while (!rules->state)
	{
		if (ft_eat(philo, rules))
			return (NULL);
		if (rules->state)
			return (NULL);
		ft_writing(philo, SLEEPING);
		ft_sleeping(rules->time_sleep, rules);
		ft_writing(philo, THINKING);
	}
	pthread_join(philo->thread_id, NULL);
	exit (0);
}

void	ft_start(t_conditions *rules)
{
	int	i;
	t_philosopher *phi;

	phi = rules->philo;
	rules->first_timer = ft_get_time();
	i = 0;
	while (i < rules->nb_philo)
	{
		phi[i].process_id = fork(); 
		if (phi[i].process_id < 0)
			return (1);
		if (phi[i].process_id < 0)
			ft_create_process(&phi[i]);
	}
	return (0);
}