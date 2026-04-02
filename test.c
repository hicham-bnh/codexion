/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:05:30 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/02 16:00:46 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void* routine() {
    printf("test from thred\n");
    sleep(3);
    printf("ending thread\n");
    return NULL;
}

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    pthread_t test1, test2;
    if (pthread_create(&test1, NULL, &routine, NULL))
        return (1);
    if (pthread_create(&test2, NULL, &routine, NULL))
        return (1);
    if (pthread_join(test1, NULL))
        return (1);
    if (pthread_join(test2, NULL))
        return (1);
    return (0);
}