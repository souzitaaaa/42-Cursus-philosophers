/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:31:53 by dinoguei          #+#    #+#             */
/*   Updated: 2023/07/11 15:40:25 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_num(int digit)
{
	if (digit >= '0' && digit <= '9')
		return (true);
	return (false);
}

bool	check_numerical(char **str)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!check_num(str[i][j]))
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

void	check_arg(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Invalid number of arguments\n");
		exit (EXIT_FAILURE);
	}
	if (check_numerical(argv))
	{
		printf("Arguments not numerical or negative number\n");
		exit (EXIT_FAILURE);
	}
}
