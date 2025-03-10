#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/neutrino.h>

#define SEC_NSEC 1000000000LL

void* long_thread(void* notused)
{
    printf("This thread is going more than 10 secons \n");
    sleep(20);
}

int main(void)
{
    uint64_t   timeout;
    struct sigevent event;
    int rval;
    pthread_t thread_id;

    printf("Prog timer  \n");
    event.sigev_notify = SIGEV_UNBLOCK;
    //SIGEV_UNBLOCK_INIT(&event);
    pthread_create(&thread_id, NULL, long_thread, NULL);

    timeout = 10LL * SEC_NSEC;
    TimerTimeout(CLOCK_REALTIME, _NTO_TIMEOUT_JOIN, &event, &timeout, NULL);
    rval = pthread_join(thread_id, NULL);
    if (rval == ETIMEDOUT)
    {
        printf("10 seconds has passed, thread %d is still going!\n", thread_id);
    }
    sleep(10);

    TimerTimeout(CLOCK_REALTIME, _NTO_TIMEOUT_JOIN, &event, &timeout, NULL);
    rval = pthread_join(thread_id, NULL);
    if (rval == ETIMEDOUT)
    {
        printf("Thread %d >25 sek!", thread_id);
    }
    else
    {
        printf("Thread %d complete\n", thread_id);
    }

    printf("\nVladislav Lyakhov\nGroup I914B\n")
    return(1);
}
