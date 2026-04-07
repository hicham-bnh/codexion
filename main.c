/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 10:16:49 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/07 19:47:23 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int mails = 0;
pthread_mutex_t	mutex;

void *coder_routine()
{
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
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
                if (pthread_create(&threads[i], NULL, &coder_routine, NULL))
                        return (NULL);
		printf("thread %d cree\n", i);
		i++;
        }
	i = 0;
	while (i < stock->number_of_coders)
	{
		if (pthread_join(threads[i], NULL))
                        return (NULL);
		printf("thread %d finish\n", i);
		i++;
	}
	return (threads);
}

int	main(int ac, char **av)
{
	t_pars		stock;
	pthread_t	*coders;

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
	pthread_mutex_init(&mutex, NULL);
	coders = create_threads(&stock);
	pthread_mutex_destroy(&mutex);
	printf("Number : %d\n", mails);
	free(coders);
}
