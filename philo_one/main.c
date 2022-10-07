/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 05:17:18 by ilinhard          #+#    #+#             */
/*   Updated: 2022/10/07 00:43:52 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char **av)
{
	t_conditions	rules;

	if (ac != 5 && ac != 6)
		return (write(2, "Wrong numbers of args\n", 22), 1);
	if (ft_parsing(av, &rules))
	{
		write(2, "Error parsing args / init args\n", 31);
		ft_cleaning_mutex(&rules);
		return (1);
	}
	ft_start(&rules);
	ft_cleaning(&rules);
	return (0);
}
