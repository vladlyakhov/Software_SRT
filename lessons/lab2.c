#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>

void* thread_function(void* arg) {
    int thread_num = *(int*)arg;
    for (int i = 0; i < 5; i++) {
        printf("Thread %d (prioritet %d) - шаг %d\n", 
               thread_num, 
               sched_getparam(getpid(), &(struct sched_param){0}),
               i);
        usleep(500000);
    }
    return NULL;
}

int main() {
    printf("Vladislav Lyakhov\nGroup I914B\n");
    pthread_t thread1, thread2;
    int thread1_num = 1, thread2_num = 2;

    pthread_attr_t attr1, attr2;
    struct sched_param param1 = {.sched_priority = 8};  
    struct sched_param param2 = {.sched_priority = 12}; 

    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    pthread_attr_setschedpolicy(&attr1, SCHED_RR);
    pthread_attr_setschedpolicy(&attr2, SCHED_RR);

    pthread_attr_setschedparam(&attr1, &param1);
    pthread_attr_setschedparam(&attr2, &param2);

    pthread_create(&thread1, &attr1, thread_function, &thread1_num);
    pthread_create(&thread2, &attr2, thread_function, &thread2_num);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
