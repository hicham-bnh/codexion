/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cond.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 21:00:14 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/11 01:56:26 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_dongles(void *arg)
{
	t_coders	*coder;

	coder = (t_coders *)arg;
	if (coder->l_dongle->free == 1)
		return (0);
	if (coder->r_dongle->free == 1)
		return (0);
	if (coder->l_dongle->free == 0)
		if (ft_time(coder->l_dongle->last_use)
			< coder->env->pars.dongle_cooldown)
			return (0);
	if (coder->r_dongle->free == 0)
		if (ft_time(coder->r_dongle->last_use)
			< coder->env->pars.dongle_cooldown)
			return (0);
	return (1);
}
