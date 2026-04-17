/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:04:08 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/16 21:50:26 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int ac, char **av)
{
	t_env	env;

	memset(&env, 0, sizeof(t_env));
	if (ac != 9 || pars_input(&env, av))
	{
		print_error();
		return (1);
	}
	if (init_env(&env) || init_mutex_env(&env))
	{
		finish(&env);
		return (1);
	}
	create_threads(&env);
	start_threads(&env);
	finish(&env);
	return (0);
}
