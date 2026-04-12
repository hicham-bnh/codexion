/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:04:08 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/12 20:46:19 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int ac, char **av)
{
	t_env	env;

	memset(&env, 0, sizeof(t_env));
	if (ac != 9 || pars_input(&env, av))
	{
		printf("ERROR\n");
		return (1);
	}
	if (init_env(&env))
		return (1);
	if (init_mutex_env(&env))
		return (1);
	if (create_threads(&env) || creat_monitor(&env))
		return (1);
	free(env.coders);
	free(env.dongles);
	return (0);
}
