#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];

void *philosopher(void *num);
void take_forks(int left_fork, int right_fork);
void put_forks(int left_fork, int right_fork);
void think();
void eat();

int main() {
    pthread_t phil[NUM_PHILOSOPHERS];
    int i;

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&phil[i], NULL, philosopher, (void *)(long)i);
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(phil[i], NULL);
    }

    return 0;
}

void *philosopher(void *num) {
    int id = (long)num;

    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        think();
        if (left_fork < right_fork) {
            take_forks(left_fork, right_fork);
        } else {
            take_forks(right_fork, left_fork);
        }

        eat();

        put_forks(left_fork, right_fork);
    }
}

void take_forks(int left_fork, int right_fork) {
    pthread_mutex_lock(&forks[left_fork]);
    pthread_mutex_lock(&forks[right_fork]);
}

void put_forks(int left_fork, int right_fork) {
    pthread_mutex_unlock(&forks[left_fork]);
    pthread_mutex_unlock(&forks[right_fork]);
}

void think() {
    sleep(rand() % 3 + 1);
}

void eat() {
    printf("Philosopher is eating.\n");
    sleep(rand() % 3 + 1);
}
