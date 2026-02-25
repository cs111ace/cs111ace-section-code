// Taken from context-switch-premption.cc
typedef struct Thread
{
    char stack[8192];
    char *saved_rsp;
} Thread;

/* This function context_switch is written in assembly!  It switches from running 'current'
 * to running 'next'.  To do this, tt first pushes 'current's registers onto the stack
 * to save them, then updates 'current' with the new stack pointer.  Then it loads 'next's
 * stack pointer and from then on we are operating on 'next's stack, not current's!  So we
 * proceed to pop off all the registers we left on 'next's' stack from before, and then
 * return, and this will return back to the function that 'next' had been executing.
 * 'current' will be resumed when another thread calls context_switch to switch back to
 * its stack.
 */
extern "C" void context_switch(Thread &current, Thread &next);

asm(R"(.text
        .global context_switch
context_switch:
        pushq %rbp
        pushq %rbx
        pushq %r12
        pushq %r13
        pushq %r14
        pushq %r15
        movq %rsp,0x2000(%rdi)      # saved current's stack pointer
    movq 0x2000(%rsi),%rsp          # load next's stack pointer
        popq %r15
        popq %r14
        popq %r13
        popq %r12
        popq %rbx
        popq %rbp
        ret     # return back to the function **this stack** was running
)");

static const int kNumRegistersToSave = 6;
Thread create_thread(void (*func)()) { 
    Thread new_thread; 
    void *stack_top = new_thread.stack + sizeof(new_thread.stack); 
 
    // Make it look like this thread was about to start func, 
    // and then context switched.  In other words, once 
    // the saved registers are popped, ret should take us to 
    // the start of func. 
    *(void **)((char *)stack_top - sizeof(void *)) = (void *)func; 
    
    // Move the stack pointer downwards by 6 registers to make it appear like 
    // we pushed 6 registers on when we previously context switched 
    new_thread.saved_rsp = (char *)stack_top - sizeof(void *) - kNumRegistersToSave * sizeof(long);
    return new_thread;
}
