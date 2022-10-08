/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 02:37:30 by ilinhard          #+#    #+#             */
/*   Updated: 2022/10/08 05:29:10 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_atoi(char *str)
{
	int			i;
	int			sig;
	long long	nb;
	int			count;

	i = 0;
	sig = 1;
	nb = 0;
	count = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sig *= -1;
		i++;
	}
	while (str[i + count] >= '0' && str[i + count] <= '9')
	{
		nb = (nb * 10) + (str[i + count] - '0');
		count++;
	}
	if (count > 10 || (nb * sig) < 0 || nb > INT_MAX)
		return (-1);
	return ((int)nb * sig);
}

long long	ft_get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_sleeping(long long time, t_conditions *rules)
{
	long long	i;

	i = ft_get_time();
	while (!rules->state)
	{
		if ((ft_get_time() - i) >= time)
			break ;
		usleep(50);
	}
}

void	ft_writing(t_philosopher *philo, int state)
{
	long long	time_diff;
	char		*str;

	sem_wait(philo->rules->writing);
	time_diff = ft_get_time() - philo->rules->first_timer;
	if (state == FORK)
		str = "has taken a fork\n";
	else if (state == EATING)
		str = "is eating\n";
	else if (state == SLEEPING)
		str = "is sleeping\n";
	else if (state == THINKING)
		str = "is thinking\n";
	else if (state == DIED)
		str = "died\n";
	printf("%lli %d %s", time_diff, (philo->id + 1), str);
	if (state != DIED)
		sem_post(philo->rules->writing);
}

void	ft_exit_clean(t_conditions *rules)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	philo = rules->philo;
	// waitpid(-1, NULL, 0);
	while (i < rules->nb_philo)
	{
		kill(philo[i].process_id, SIGKILL);
		i++;
	}
	sem_close(rules->writing);
	sem_close(rules->test);
	sem_close(rules->m_eating);
	sem_close(rules->forks);
	free(philo);
}
