// include from lecture 19's timer code (for intr_enable, IntrGuard)
#include "/afs/ir/class/cs111/lecture-code/lect19/timer.hh"
#include "/afs/ir/class/cs111/lecture-code/lect19/timer.cc"
#include "util.hh"
#include <csignal>
#include <cstdio>
#include <sys/time.h>
#include <iostream>

using namespace std;

void thread_func() {
    intr_enable(true);
    while (1) {
        cout << "hi from the second thread" << endl;
    }    
}

Thread main_thread;
Thread second_thread;

Thread* running_thread;
Thread* nonrunning_thread;

void timer_interrupt_handler();

// Wrapper with correct signature for sigaction; re-enables SIGALRM so timer keeps firing
static void sigalrm_handler(int) {
    timer_interrupt_handler();
    // Allow another SIGALRM to be delivered (like the library's timer_interrupt does)
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);
    sigprocmask(SIG_UNBLOCK, &mask, nullptr);
}

void timer_interrupt_handler()
{
    Thread* temp = running_thread;
    running_thread = nonrunning_thread;
    nonrunning_thread = temp;

    intr_enable(false);
    context_switch(*nonrunning_thread, *running_thread);
    intr_enable(true);
}


int main()
{
    second_thread = create_thread(thread_func);
    running_thread = &main_thread;
    nonrunning_thread = &second_thread;

    // Register our handler directly as the SIGALRM handler (no library wrapper)
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = &sigalrm_handler;
    if (sigaction(SIGALRM, &sa, nullptr) == -1) {
        perror("sigaction");
        return 1;
    }

    // Arm the timer: fire every 50 microseconds
    struct itimerval itv;
    itv.it_interval.tv_sec = 0;
    itv.it_interval.tv_usec = 50000;
    itv.it_value = itv.it_interval;
    if (setitimer(ITIMER_REAL, &itv, nullptr) == -1) {
        perror("setitimer");
        return 1;
    }

    while(true) {
        cout << "Hello from the main thread!" << endl;
    }

    return 0;
}