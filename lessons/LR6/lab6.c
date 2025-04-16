#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

int data_ready = 0;
int inf = 0;

pthread_mutex_t mutex;
pthread_cond_t condvar;

void print_time(const char* tag) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    struct tm* tm_info = localtime(&tv.tv_sec);

    printf("[%02d:%02d:%02d.%03ld] %s\n",
        tm_info->tm_hour,
        tm_info->tm_min,
        tm_info->tm_sec,
        tv.tv_usec / 1000,
        tag);
}

void* consumer(void* notused) {
    printf("This is consumer\n");
    while (1) {
        pthread_mutex_lock(&mutex);
        print_time("W1");
        while (!data_ready) {
            print_time("W2");
            pthread_cond_wait(&condvar, &mutex);
            print_time("W3");
        }
        printf("Data from producer = %d\n", inf);
        data_ready = 0;
        pthread_cond_signal(&condvar);
        pthread_mutex_unlock(&mutex);
    }
}

void* producer(void* notused) {
    printf("This is producer\n");
    while (1) {
        sleep(2);
        printf("Producer has received data from h/w = %d\n", inf);
        pthread_mutex_lock(&mutex);
        print_time("Wp1");
        while (data_ready) {
            print_time("Wp2");
            pthread_cond_wait(&condvar, &mutex);
        }
        inf++;
        data_ready = 1;
        print_time("Wp3");
        pthread_cond_signal(&condvar);
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    printf("Start\n");

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condvar, NULL);

    pthread_t t1, t2;

    pthread_create(&t1, NULL, consumer, NULL);
    sleep(1);
    pthread_create(&t2, NULL, producer, NULL);

    sleep(10);
    return 0;
}
