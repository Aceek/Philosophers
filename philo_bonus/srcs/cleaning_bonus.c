/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 03:25:20 by ilinhard          #+#    #+#             */
/*   Updated: 2022/10/12 03:02:33 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	ft_exit_clean(t_conditions *rules)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	philo = rules->philo;
	while (i < rules->nb_philo)
	{
		waitpid(philo[i].process_id, NULL, 0);
		if (philo[i].process_id)
			kill(philo[i].process_id, SIGKILL);
		i++;
	}
	pthread_join(rules->t_eat, NULL);
	sem_close(rules->writing);
	sem_close(rules->ending);
	sem_close(rules->cleaner);
	sem_close(rules->all_eat);
	sem_close(rules->m_eating);
	sem_close(rules->forks);
	free(philo);
}

void	*ft_end_clean(void *condition)
{
	t_conditions	*rules;

	rules = condition;
	sem_wait(rules->cleaner);
	rules->state = 1;
	sem_post(rules->all_eat);
	sem_post(rules->cleaner);
	return (NULL);
}

void	ft_exit(t_conditions *rules, t_philosopher *philo)
{
	pthread_join(philo->t_cleaner, NULL);
	pthread_join(philo->thread_id, NULL);
	sem_close(rules->writing);
	sem_close(rules->ending);
	sem_close(rules->cleaner);
	sem_close(rules->all_eat);
	sem_close(rules->m_eating);
	sem_close(rules->forks);
	free(rules->philo);
	return ;
}
