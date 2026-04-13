/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:34:25 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/13 23:04:58 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*routine(void *arg)
{
	t_coders	*coder;

	coder = (t_coders *)arg;
	if (coder->id % 2 == 0)
		usleep(coder->env->pars.to_compile * 1000);
	while (!check_end(coder->env))
	{
		if (check_compile(coder))
		{
			add_finish(coder->env);
			break ;
		}
		take_dongle(coder);
		if (compile(coder))
			break ;
		put_dongle(coder);
		if (debug(coder))
			break ;
		if (refctor(coder))
			break ;
	}
	return (NULL);
}

void	*monitor(void	*arg)
{
	t_env	*env;
	int		i;
	int		stop;

	stop = 0;
	env = (t_env *)arg;
	while (!check_compil_end(env))
	{
		i = 0;
		if (stop)
			break ;
		while (i < env->pars.number_coders && !stop)
		{
			if (check_burnout(&env->coders[i]))
			{
				stop_simul(env);
				burnout(env, i);
				stop = 1;
				break ;
			}
			i++;
		}
	}
	return (NULL);
}
