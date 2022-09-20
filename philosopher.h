/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 07:37:08 by ilinhard          #+#    #+#             */
/*   Updated: 2022/09/20 08:16:04 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_conditions
{
	int	nb_philo;
	int	time_death;
	int	time_eat;
	int	time_sleep;
	int	nb_eat;
}		t_conditions;

#endif