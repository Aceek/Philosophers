/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 07:40:04 by ilinhard          #+#    #+#             */
/*   Updated: 2022/10/09 06:59:00 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*ft_state_check(void *philo)
{
	t_philosopher	*phi;
	t_conditions	*rules;
	// int				done;

	phi = (t_philosopher *)philo;
	rules = phi->rules;
	// done = 0;
	while (!rules->state)
	{
		sem_wait(rules->m_eating);
		if ((ft_get_time() - phi->time_last_meal) > rules->time_death)
		{
			ft_writing(philo, DIED);
			sem_post(rules->ending);
			// rules->state = 1;
			// exit (0);
		}
		sem_post(rules->m_eating);
		// if (!done && rules->nb_eat && phi->eat_count >= rules->nb_eat)
		// {
		// 	sem_post(rules->all_eat);
		// 	done = 1;
		// }
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
	philo->eat_count += 1;
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
	// sem_wait(rules->all_eat);
	philo->time_last_meal = ft_get_time();
	pthread_create(&(philo->thread_id), NULL, &ft_state_check, (void *)philo);
	// verif thread init
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

void	*ft_check_eat_count(void *conditions)
{
	int	i;
	t_conditions *rules;

	rules = (t_conditions *)conditions;
	i = -1;
	while (++i < rules->nb_philo)
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
	// pthread_create(&(rules->t_eat), NULL, &ft_check_eat_count, (void *)rules);
	//verif thread init
	return ;
}