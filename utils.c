/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 02:37:30 by ilinhard          #+#    #+#             */
/*   Updated: 2022/09/22 09:27:01 by ilinhard         ###   ########.fr       */
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

void	ft_putnbr(long long nbr)
{
	char	c;

	if (nbr >= 0 && nbr <= 9)
	{
		c = nbr + '0';
		write(1, &c, 1);
	}
	if (nbr > 9)
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
}

void	ft_sleeping(long long time, t_conditions *rules)
{
	// while (died ???)
	// si prog s'arrete pendant sleep ???
	(void)rules;
	usleep(time * 1000);
}

// void	ft_writing(t_philosopher *philo, int state)
// {
// 	pthread_mutex_lock(&philo->rules->writing);
// 	ft_putnbr(ft_get_time() - philo->rules->first_timer);
// 	write(1, " ", 1);
// 	ft_putnbr(philo->id);
// 	write(1, " ", 1);
// 	if (state == FORK)
// 		write(1, "has taken a fork\n", 17);
// 	else if (state == EATING)
// 		write(1, "is eating\n", 10);
// 	else if (state == SLEEPING)
// 		write(1, "is sleeping\n", 12);
// 	else if (state == THINKING)
// 		write(1, "is thinking\n", 12);
// 	else if (state == DIED)
// 		write(1, "died\n", 5);
// 	pthread_mutex_unlock(&philo->rules->writing);
// }

void	ft_writing(t_philosopher *philo, int state)
{
	long long	time_diff;
	char		*str;

	pthread_mutex_unlock(&philo->rules->writing);
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
	pthread_mutex_lock(&philo->rules->writing);
	printf("%lli %d %s", time_diff, philo->id, str);
	pthread_mutex_unlock(&philo->rules->writing);
}
