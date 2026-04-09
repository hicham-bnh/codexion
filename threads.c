/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:16:25 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/09 20:22:30 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	create_threads(t_env *env)
{
	int	i;

	i = 0 ;
	while (i < env->pars.number_coders)
	{
		env->coders[i].id = i + 1;
		env->coders[i].compile = 0;
		env->coders[i].l_dongle = &env->dongles[i];
		env->coders[i].r_dongle = &env->dongles[(i + 1) % env->pars.number_coders];
		
		if (pthread_create(&env->coders[i].thread, NULL, NULL, NULL))
			return (1);
	}
	i = 0;
	while (i < env->pars.number_coders)
	{
		if (pthread_join(env->coders[i].thread, NULL))
			return (1);
	}
	return (0);
}
