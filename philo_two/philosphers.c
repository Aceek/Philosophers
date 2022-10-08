/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 07:40:04 by ilinhard          #+#    #+#             */
/*   Updated: 2022/10/08 05:16:38 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*ft_state_check(void *philo)
{
	t_philosopher	*phi;
	t_conditions	*rules;

	phi = (t_philosopher *)philo;
	rules = phi->rules;
	while (!rules->state)
	{
		sem_wait(rules->m_eating);
		if (rules->m_eating == 0)
			printf("oui\n");
		if ((ft_get_time() - phi->time_last_meal) > rules->time_death)
		{
			ft_writing(philo, DIED);
			// rules->state = 1;
			exit (0);
		}
		sem_post(rules->m_eating);
		usleep(50);
	}
	return (NULL);
}

void	ft_eat(t_philosopher *philo ,t_conditions *rules)
{
	sem_wait(rules->forks);
	ft_writing(philo, FORK);
	sem_wait(rules->forks);
	ft_writing(philo, FORK);
	sem_wait(rules->m_eating);
	ft_writing(philo, EATING);
	philo->time_last_meal = ft_get_time();
	sem_post(rules->m_eating);
	ft_sleeping(rules->time_eat, rules);
	sem_post(rules->forks);
	sem_post(rules->forks);
}

void	ft_create_process(t_philosopher *philo)
{
	t_conditions *rules;

	rules = philo->rules;
	philo->time_last_meal = ft_get_time();
	pthread_create(&(philo->thread_id), NULL, &ft_state_check, (void *)philo);
	pthread_detach(philo->thread_id);
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
	// free(philo);
	// pthread_join(philo->thread_id, NULL);
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
			return ;
		if (phi[i].process_id == 0)
			ft_create_process(&phi[i]);
		i++;
	}
	return ;
}