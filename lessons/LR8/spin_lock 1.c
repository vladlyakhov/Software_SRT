#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/neutrino.h>
#include <sys/syspage.h>

static pthread_spinlock_t spinlock;
void* thread_func(void* arg) {
    int thread_num = *(int*)arg;

    printf("Thread %d try to catch spin-lock...\n", thread_num);
    pthread_spin_lock(&spinlock);
    printf("Thread %d catched spin-lock. Working...\n", thread_num);
    delay(500); 
    printf("Thread %d releases spin-lock\n", thread_num);
    pthread_spin_unlock(&spinlock);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int thread_num1 = 1, thread_num2 = 2;

    printf("\nVladislav Lyakhov\nGroup I914B\n");
        if (pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE) != 0) {
            perror("Error: Spin-lock inizializate");
            return EXIT_FAILURE;
        }

    printf("Creating threads...\n");

    pthread_create(&thread1, NULL, thread_func, &thread_num1);
    pthread_create(&thread2, NULL, thread_func, &thread_num2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_spin_destroy(&spinlock);
    printf("All threads finished work\n");
    return EXIT_SUCCESS;
}