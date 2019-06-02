// Trabalho - Banheiro na Escola
// Aluno: João Lucas Azevedo Yamin Rodrigues da Cunha
// Matrícula: 17/0013731

//Inclusões
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <semaphore.h>

//Definição de cores para printf
#define COLOR_RED "\x1b[31m"            //Utilizada para as meninas da A
#define COLOR_GREEN "\x1b[32m"          //Utilizada para a professora da A
#define COLOR_YELLOW "\x1b[33m"         //Utilizada para a professora da B
#define COLOR_BLUE "\x1b[34m"           //Utilizada para os meninos da A
#define COLOR_MAGENTA "\x1b[35m"        //Utilizada para as meninas da B
#define COLOR_CYAN "\x1b[36m"           //Utilizada para os meninos da B
#define COLOR_RESET "\x1b[0m"

//Definição de tamanhos
#define X 6
#define Y 6
#define A 1
#define B 2

//Declaração de threads, mutex e semáforos
pthread_t profA, profB, alunasA[X], alunasB[X], alunosA[Y], alunosB[Y];
pthread_mutex_t mutexA, mutexB;
pthread_mutex_t mutexM, mutexF;
sem_t passeAM, passeAF, passeBM, passeBF, banheiroM, banheiroF;

int explicaA = 0, explicaB = 0;
int qntF = 0, qntM = 0;

void *alunaA(void *arg) {
    int i = *((int *)arg);

    while (1) {
        sem_wait(&passeAF);                     //Espera para pegar o passe
        if(explicaA) {                          //Se a professora quiser explicar
            pthread_mutex_lock(&mutexA);        //Espera a explicação
            pthread_mutex_unlock(&mutexA);
        }
        printf(COLOR_RED "Aluna %d da Turma A pegou o passe e está indo ao banheiro\n", i);
        sleep(1);
        sem_wait(&banheiroF);                   //Espera para usar o banheiro
        pthread_mutex_lock(&mutexF);            //Incrementa quantidade de alunos no banheiro
        qntF++;
        printf(COLOR_RED "Aluna %d da A entrou no banheiro. %d menina(s) no banheiro\n", i, qntF);
        pthread_mutex_unlock(&mutexF);
        sleep(2);
        pthread_mutex_lock(&mutexF);            //Decrementa quantidade de alunos no banheiro
        qntF--;
        printf(COLOR_RED "Aluna %d da A saiu do banheiro. %d menina(s) no banheiro\n", i, qntF);
        sem_post(&banheiroF);                   //Libera espaço no banheiro
        pthread_mutex_unlock(&mutexF);
        sleep(1);
        printf(COLOR_RED "Aluna %d da Turma A voltou para a sala\n", i);
        sem_post(&passeAF);                     //Libera o passe
        sleep(6);                               //Anotando
            
    }
}

void *alunaB(void *arg) {
    int i = *((int *)arg);

    while (1) {
        sem_wait(&passeBF);                             //Espera para pegar o passe
        if (explicaB) {                                 //Se a professora quiser explicar
            pthread_mutex_lock(&mutexB);                //Espera a explicação
            pthread_mutex_unlock(&mutexB);
        }
        printf(COLOR_MAGENTA "Aluna %d da Turma B pegou o passe e está indo ao banheiro\n", i);
        sleep(1);
        sem_wait(&banheiroF);                           //Espera para usar o banheiro
        pthread_mutex_lock(&mutexF);                    //Incrementa quantidade de alunos no banheiro
        qntF++;
        printf(COLOR_MAGENTA "Aluna %d da B entrou no banheiro. %d menina(s) no banheiro\n", i, qntF);
        pthread_mutex_unlock(&mutexF);
        sleep(2);
        pthread_mutex_lock(&mutexF);                    //Decrementa quantidade de alunos no banheiro
        qntF--;
        printf(COLOR_MAGENTA "Aluna %d da B saiu do banheiro. %d menina(s) no banheiro\n", i, qntF);
        sem_post(&banheiroF);                           //Libera espaço no banheiro
        pthread_mutex_unlock(&mutexF);
        sleep(1);
        printf(COLOR_MAGENTA "Aluna %d da Turma B voltou para a sala\n", i);
        sem_post(&passeBF);                             //Libera o passe
        sleep(6);                                       //Anotando
    }
}

void *alunoA(void *arg) {
    int i = *((int *)arg);

    while (1) {
        sem_wait(&passeAM); //Espera para pegar o passe
        if (explicaA) {                                //Se a professora quiser explicar
            pthread_mutex_lock(&mutexA); //Espera a explicação
            pthread_mutex_unlock(&mutexA);
        }
        printf(COLOR_BLUE "Aluno %d da Turma A pegou o passe e está indo ao banheiro\n", i);
        sleep(1);
        sem_wait(&banheiroM);        //Espera para usar o banheiro
        pthread_mutex_lock(&mutexM); //Incrementa quantidade de alunos no banheiro
        qntM++;
        printf(COLOR_BLUE "Aluno %d da A entrou no banheiro. %d menino(s) no banheiro\n", i, qntM);
        pthread_mutex_unlock(&mutexM);
        sleep(2);
        pthread_mutex_lock(&mutexM); //Decrementa quantidade de alunos no banheiro
        qntM--;
        printf(COLOR_BLUE "Aluno %d da A saiu do banheiro. %d menino(s) no banheiro\n", i, qntM);
        sem_post(&banheiroM); //Libera espaço no banheiro
        pthread_mutex_unlock(&mutexM);
        sleep(1);
        printf(COLOR_BLUE "Aluno %d da Turma A voltou para a sala\n", i);
        sem_post(&passeAM); //Libera o passe
        sleep(6);           //Anotando
    }
}

void *alunoB(void *arg) {
    int i = *((int *)arg);

    while (1) {
        sem_wait(&passeBM);                             //Espera para pegar o passe
        if (explicaB) {                                 //Se a professora quiser explicar
            pthread_mutex_lock(&mutexB);                //Espera a explicação
            pthread_mutex_unlock(&mutexB);
        }
        printf(COLOR_CYAN "Aluno %d da Turma B pegou o passe e está indo ao banheiro\n", i);
        sleep(1);
        sem_wait(&banheiroM);                           //Espera para usar o banheiro
        pthread_mutex_lock(&mutexM);                    //Incrementa quantidade de alunos no banheiro
        qntM++;
        printf(COLOR_CYAN "Aluno %d da B entrou no banheiro. %d menino(s) no banheiro\n", i, qntM);
        pthread_mutex_unlock(&mutexM);
        sleep(2);
        pthread_mutex_lock(&mutexM);                    //Decrementa quantidade de alunos no banheiro
        qntM--;
        printf(COLOR_CYAN "Aluno %d da B saiu do banheiro. %d menino(s) no banheiro\n", i, qntM);
        sem_post(&banheiroM);                           //Libera espaço no banheiro
        pthread_mutex_unlock(&mutexM);
        sleep(1);
        printf(COLOR_CYAN "Aluno %d da Turma B voltou para a sala\n", i);
        sem_post(&passeBM);                             //Libera o passe
        sleep(6);                                       //Anotando
    }
}

void *professoraA (void *arg) {
    while (1) {
        sleep(rand() % 10);          // Escrevendo no quadro
        printf(COLOR_GREEN "Professora A quer explicar\n");
        pthread_mutex_lock(&mutexA);
        explicaA = 1;
        printf(COLOR_GREEN "Professora A está explicando...\n");
        sleep(rand() % 7);
        printf(COLOR_GREEN "Professora A terminou de explicar.\n");
        explicaA = 0;
        pthread_mutex_unlock(&mutexA);
    }
}

void *professoraB(void *arg) {
    while (1) {
        sleep(rand() % 10); // Escrevendo no quadro
        printf(COLOR_YELLOW "Professora B quer explicar\n");
        pthread_mutex_lock(&mutexB);
        explicaB = 1;
        printf(COLOR_YELLOW "Professora B está explicando...\n");
        sleep(rand() % 7);
        printf(COLOR_YELLOW "Professora B terminou de explicar.\n");
        explicaA = 0;
        pthread_mutex_unlock(&mutexB);
    }
}

int main () {

    int i = 0;
    int * id;

    //Inicialização dos semáforos
    sem_init(&banheiroF, 0, 3);          //Semáforo para o banheiro feminino
    sem_init(&banheiroM, 0, 3);          //Semáforo para o banheiro masculino
    sem_init(&passeAF, 0, 2);            //Semáforo para o passe feminino da sala A
    sem_init(&passeAM, 0, 2);            //Semáforo para o passe masculino da sala A
    sem_init(&passeBM, 0, 2);            //Semáforo para o passe masculino da sala B
    sem_init(&passeBF, 0, 2);            //Semáforo para o passe feminino da sala B

    //Inicialização dos locks
    pthread_mutex_init(&mutexA, NULL);      //Lock para a professora A
    pthread_mutex_init(&mutexB, NULL);      //Lock para a professora B

    //Criação das threads
    for (i = 0; i < Y; i++) {
        id  = (int *)malloc(sizeof(int));
        *id = i;
        pthread_create(&(alunasA[i]), NULL, alunaA, (void *) id); //Alunas da turma A
    }

    for (i = 0; i < Y; i++) {
        id = (int *)malloc(sizeof(int));
        *id = i;
        pthread_create(&(alunasB[i]), NULL, alunaB, (void *)id); //Alunas da turma B
    }

    for(i = 0; i < X; i++) {
        id = (int *) malloc(sizeof(int));
        *id = i;
        pthread_create(&(alunosA[i]), NULL, alunoA, (void *) id); //Alunos da turma A
    }

    for (i = 0; i < X; i++) {
        id = (int *)malloc(sizeof(int));
        *id = i;
        pthread_create(&(alunosB[i]), NULL, alunoB, (void *)id); //Alunos da turma B
    }

    pthread_create(&profA, NULL, professoraA, NULL);
    pthread_create(&profB, NULL, professoraB, NULL);

    pthread_join(alunosA[0], NULL);

    free(id);

    return 0;
}