/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 02:37:30 by ilinhard          #+#    #+#             */
/*   Updated: 2022/10/14 06:33:32 by ilinhard         ###   ########.fr       */
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
	if (count > 10 || (nb * sig) <= 0 || nb > INT_MAX)
		return (-1);
	return ((int)nb * sig);
}

long long	ft_get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_is_died(t_conditions *rules)
{
	pthread_mutex_lock(&rules->time);
	if (rules->state == 1)
	{
		pthread_mutex_unlock(&rules->time);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&rules->time);
		return (0);
	}
}

void	ft_sleeping(long long time, t_conditions *rules)
{
	long long	i;

	i = ft_get_time();
	while (!ft_is_died(rules))
	{
		if ((ft_get_time() - i) >= time)
			break ;
		usleep(100);
	}
}

int	ft_writing(t_philosopher *philo, int state)
{
	long long	time_diff;
	char		*str;

	pthread_mutex_lock(&philo->rules->writing);
	if (ft_is_died(philo->rules))
		return (pthread_mutex_unlock(&philo->rules->writing), 1);
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
	{
		str = "died\n";
		pthread_mutex_lock(&philo->rules->time);
		philo->rules->state = 1;
		pthread_mutex_unlock(&philo->rules->time);
	}
	printf("%lli %d %s", time_diff, (philo->id + 1), str);
	pthread_mutex_unlock(&philo->rules->writing);
	return (0);
}
