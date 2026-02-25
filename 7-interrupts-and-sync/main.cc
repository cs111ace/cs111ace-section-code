// include from lecture 19's timer.hh code
#include "/afs/ir/class/cs111/lecture-code/lect19/timer.cc"
#include "util.hh"
#include <iostream>

using namespace std;

void thread_func() {
    // TODO
}

Thread main_thread;
Thread second_thread;

Thread* running_thread;
Thread* nonrunning_thread;

void timer_interrupt_handler()
{
    Thread* temp = running_thread;
    running_thread = nonrunning_thread;
    nonrunning_thread = temp;

    // context switch in here
    context_switch(*nonrunning_thread, *running_thread);
}


int main()
{

    running_thread = &main_thread;
    nonrunning_thread = &second_thread;

    // "setup" the interrupt handler
    timer_init(100, timer_interrupt_handler);

    while(true) {
        cout << "Hello from the main thread!" << endl;
    }

    return 0;
}