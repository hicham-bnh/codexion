/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:04:08 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/09 21:07:43 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int main(int ac, char **av)
{
	t_env	env;

	memset(&env, 0, sizeof(t_env));
	if (ac != 9 || pars_input(&env, av))
	{
		printf("ERROR\n");
		return (1);
	}
	init_env(&env);
	create_threads(&env);
}