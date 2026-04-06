/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 10:16:49 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/06 18:26:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int ac, char **av)
{
	t_pars		stock;
	pthread_t	*coders;
	p_thread_mutex_t	*dongles;

	if (ac != 9)
	{
		printf("ERROR");
		return (0);
	}
	parsing_input(&stock, av);
	if (check_parsing(&stock))
	{
		printf("ERROR");
		return (0);
	}
	coders = create_threads(&stock);
	dongles = create_mutex(&stcok);
	free(threads);
}
