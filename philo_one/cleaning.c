/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 05:36:22 by ilinhard          #+#    #+#             */
/*   Updated: 2022/10/09 05:38:13 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_init_cleaning(t_conditions *rules)
{
	rules->init_fail = 1;
	rules->verify_cleaning = malloc(sizeof(t_cleaner));
	if (!rules->verify_cleaning)
		return (1);
	rules->init_fail = 0;
	rules->verify_cleaning->eating_c = 0;
	rules->verify_cleaning->writing_c = 0;
	rules->verify_cleaning->malloc_forks_c = 0;
	rules->verify_cleaning->forks_c = 0;
	rules->verify_cleaning->philo_c = 0;
	rules->verify_cleaning->thread_c = 0;
	return (0);
}

void	ft_cleaning_mutex(t_conditions *rules)
{
	int	i;

	if (rules->init_fail)
		return ;
	if (rules->verify_cleaning->eating_c)
		pthread_mutex_destroy(&rules->m_eating);
	if (rules->verify_cleaning->writing_c)
		pthread_mutex_destroy(&rules->writing);
	i = 0;
	while (i < rules->verify_cleaning->forks_c)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	if (rules->verify_cleaning->philo_c)
		free(rules->philo);
	if (rules->verify_cleaning->malloc_forks_c)
		free(rules->forks);
	if (rules->verify_cleaning)
		free(rules->verify_cleaning);
}

void	ft_cleaning(t_conditions *rules)
{
	int	i;

	i = 0;
	while (i < rules->verify_cleaning->thread_c)
	{
		if (&rules->philo[i].thread_id)
			pthread_join(rules->philo[i].thread_id, NULL);
		i++;
	}
	ft_cleaning_mutex(rules);
}
