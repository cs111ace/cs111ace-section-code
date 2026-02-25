// Enable and disable interrupts (x86/x86-64).
// Use with care: only in kernel/low-level code; not available in user space.

void disable_interrupts()
{
#if defined(__x86_64__) || defined(__i386__)
    __asm__ volatile("cli" ::: "memory");
#else
#error "disable_interrupts() not implemented for this architecture"
#endif
}

void enable_interrupts()
{
#if defined(__x86_64__) || defined(__i386__)
    __asm__ volatile("sti" ::: "memory");
#else
#error "enable_interrupts() not implemented for this architecture"
#endif
}