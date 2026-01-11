#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

// semaforos pra controlar a mesa e cada fumante
sem_t mesa_vazia;
sem_t s_tabaco;
sem_t s_papel;
sem_t s_fosforo;

void* funcao_sistema(void* arg) {
    while(1) {
        // trava aqui ate a mesa desocupar
        sem_wait(&mesa_vazia);
        int item = rand() % 3; // escolhe o que vai pra mesa

        if (item == 0) {
            printf("\n[SISTEMA] Colocou Papel e Fosforo na mesa.\n");
            sem_post(&s_tabaco); // libera quem tem tabaco
        } else if (item == 1) {
            printf("\n[SISTEMA] Colocou Tabaco e Fosforo na mesa.\n");
            sem_post(&s_papel); // libera quem tem papel
        } else {
            printf("\n[SISTEMA] Colocou Tabaco e Papel na mesa.\n");
            sem_post(&s_fosforo); // libera quem tem fosforo
        }
        sleep(1); 
    }
}

void* fumante_tabaco(void* arg) {
    while(1) {
        sem_wait(&s_tabaco); // espera os itens que faltam
        printf("Fumante 1 (tem Tabaco): Pegou os itens e esta fumando...\n");
        sleep(2); 
        sem_post(&mesa_vazia); // avisa que a mesa esvaziou
    }
}

void* fumante_papel(void* arg) {
    while(1) {
        sem_wait(&s_papel); // espera os itens que faltam
        printf("Fumante 2 (tem Papel): Pegou os itens e esta fumando...\n");
        sleep(2);
        sem_post(&mesa_vazia); // avisa que a mesa esvaziou
    }
}

void* fumante_fosforo(void* arg) {
    while(1) {
        sem_wait(&s_fosforo); // espera os itens que faltam
        printf("Fumante 3 (tem Fosforo): Pegou os itens e esta fumando...\n");
        sleep(2);
        sem_post(&mesa_vazia); // avisa que a mesa esvaziou
    }
}

int main() {
    srand(time(NULL)); 

    // inicia os controles (mesa começa liberada)
    sem_init(&mesa_vazia, 0, 1);
    sem_init(&s_tabaco, 0, 0);
    sem_init(&s_papel, 0, 0);
    sem_init(&s_fosforo, 0, 0);

    pthread_t s, f1, f2, f3;

    // cria as threads de cada um
    pthread_create(&s, NULL, funcao_sistema, NULL);
    pthread_create(&f1, NULL, fumante_tabaco, NULL);
    pthread_create(&f2, NULL, fumante_papel, NULL);
    pthread_create(&f3, NULL, fumante_fosforo, NULL);

    // mantem o processo rodando
    pthread_join(s, NULL);

    return 0;
}
