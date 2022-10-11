/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 05:17:18 by ilinhard          #+#    #+#             */
/*   Updated: 2022/10/11 03:11:53 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

int	main(int ac, char **av)
{
	t_conditions	rules;

	if (ac != 5 && ac != 6)
		return (write(2, "Wrong numbers of args\n", 22), 1);
	if (ft_parsing(av, &rules))
		return (write(2, "Error parsing args / init args\n", 31), 1);
	sem_wait(rules.ending);
	if (ft_start(&rules))
		sem_post(rules.ending);
	sem_wait(rules.ending);
	sem_post(rules.cleaner);
	ft_exit_clean(&rules);
	return (0);
}
