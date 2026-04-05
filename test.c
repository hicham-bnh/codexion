/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:05:30 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/02 17:23:41 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* routine(void* arg) {
    int id = *(int*)arg;
    printf("Salut ! Je suis le thread n°%d\n", id);
    free(arg);
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <nombre_de_threads>\n", argv[0]);
        return 1;
    }
    int nb = atoi(argv[1]);
    pthread_t *threads = malloc(sizeof(pthread_t) * nb);

    for (int i = 0; i < nb; i++) {
        int* id_thread = malloc(sizeof(int));
        *id_thread = i;

        if (pthread_create(&threads[i], NULL, &routine, id_thread) != 0) {
            perror("Erreur création thread");
        }
    }

    for (int i = 0; i < nb; i++) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    printf("Tous les threads ont terminé.\n");
    return 0;
}