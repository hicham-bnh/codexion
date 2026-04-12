/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burnout.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:09:45 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/13 00:12:50 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*burnout(void *arg, int i)
{
	t_env	*env;

	env = (t_env *)arg;
	pthread_mutex_lock(&env->write);
	printf("%ld %d  burned out\n",
		ft_time(env->start), env->coders[i].id);
	pthread_mutex_unlock(&env->write);
	return (NULL);
}
