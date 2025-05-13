#include <sys/neutrino.h>
#include <sys/syspage.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <hw/inout.h>

volatile uintptr_t timer_base;
volatile int counter = 0;


const struct sigevent* timer_isr(void* arg, int id) {
    counter++;
    printf("Timer ISR called: %d\n", counter);
    out32(timer_base + 0x0, 0x1);
    return NULL;
}

int main() {
    int intr;
    struct sigevent event;
    struct _clockperiod period;

    printf("\nVladislav Lyakhov\nGroup I914B\n");
        timer_base = (uintptr_t)mmap_device_io(4, 0x80810000); 

    intr = InterruptAttach(0, timer_isr, NULL, 0, 0);
    if (intr == -1) {
        perror("InterruptAttach failed");
        return EXIT_FAILURE;
    }

    period.nsec = 1000000;
    period.fract = 0;
    ClockPeriod(CLOCK_REALTIME, &period, NULL, 0);

    printf("Timer ISR is running. Press Enter to exit...\n");
    getchar();

    InterruptDetach(intr);
    munmap_device_io((void*)timer_base, 4);
    return EXIT_SUCCESS;
}