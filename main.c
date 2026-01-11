#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

sem_t mesa_vazia;
sem_t s_tabaco;
sem_t s_papel;
sem_t s_fosforo;

void* funcao_agente(void* arg) {
    while(1) {
        sem_wait(&mesa_vazia);
        int item = rand() % 3;

        if (item == 0) {
            printf("\n[AGENTE] Colocou Papel e Fosforo na mesa.\n");
            sem_post(&s_tabaco);
        } else if (item == 1) {
            printf("\n[AGENTE] Colocou Tabaco e Fosforo na mesa.\n");
            sem_post(&s_papel);
        } else {
            printf("\n[AGENTE] Colocou Tabaco e Papel na mesa.\n");
            sem_post(&s_fosforo);
        }
        sleep(1);
    }
}

void* fumante_tabaco(void* arg) {
    while(1) {
        sem_wait(&s_tabaco);
        printf("Fumante 1 (tem Tabaco): Pegou os itens e esta fumando...\n");
        sleep(2);
        sem_post(&mesa_vazia);
    }
}

void* fumante_papel(void* arg) {
    while(1) {
        sem_wait(&s_papel);
        printf("Fumante 2 (tem Papel): Pegou os itens e esta fumando...\n");
        sleep(2);
        sem_post(&mesa_vazia);
    }
}

void* fumante_fosforo(void* arg) {
    while(1) {
        sem_wait(&s_fosforo);
        printf("Fumante 3 (tem Fosforo): Pegou os itens e esta fumando...\n");
        sleep(2);
        sem_post(&mesa_vazia);
    }
}

int main() {
    srand(time(NULL));

    sem_init(&mesa_vazia, 0, 1);
    sem_init(&s_tabaco, 0, 0);
    sem_init(&s_papel, 0, 0);
    sem_init(&s_fosforo, 0, 0);

    pthread_t a, f1, f2, f3;

    pthread_create(&a, NULL, funcao_agente, NULL);
    pthread_create(&f1, NULL, fumante_tabaco, NULL);
    pthread_create(&f2, NULL, fumante_papel, NULL);
    pthread_create(&f3, NULL, fumante_fosforo, NULL);

    pthread_join(a, NULL);

    return 0;
}