/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 20:33:27 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/06 18:41:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void* lunch()
{
	// la routine des threads compile debug et factor
        // lock le mutex au debut et le unlock a la fin
}

pthread_mutex_t *create_mutex(t_pars *stock)
{
	pthread_mutex_t *muetxs;

        mutexs = malloc(sizepf(pthread_mutex_t) * stock->number_of_coders);
        if (!mutexs)
                return (NULL);
        return (mutexs);
}

pthread_t       *create_threads(t_pars *stock)
{
	pthread_t	*threads;
        int     i;
        
        i = 0;
	threads = malloc(sizeof(pthread_t) * stock->number_of_coders);
	if (!threads)
		return (NULL);
        while (i < stock->number_of_coders)
        {
                if (pthread_create(&threads[i], NULL, NULL, NULL))
                        return (1);
                if (pthread_join(threads[i], NULL))
                        return (1);
        }
	return (threads);
}
