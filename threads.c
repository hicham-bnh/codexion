/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 20:33:27 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/05 21:19:25 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

pthread_t	*create_threads(t_pars *stock)
{
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * stock->number_of_coders);
	if (!threads)
		return (NULL);
	return (threads);
}
