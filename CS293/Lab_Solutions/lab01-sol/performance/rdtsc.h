#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <iostream>

#ifndef DS_LAB_RDTSC_H
#define DS_LAB_RDTSC_H

static __inline__ unsigned long long startRDTSC (void) {
    unsigned cycles_low, cycles_high;
    asm volatile ("CPUID\n\t"
            "RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
            "%rax", "%rbx", "%rcx", "%rdx");
    return (static_cast<unsigned long long>(cycles_high) << 32) | cycles_low;
}

static __inline__ unsigned long long stopRDTSCP (void) {
    unsigned cycles_low, cycles_high;
    asm volatile("RDTSCP\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "CPUID\n\t": "=r" (cycles_high), "=r" (cycles_low):: "%rax",
            "%rbx", "%rcx", "%rdx");
    return (static_cast<unsigned long long>(cycles_high) << 32) | cycles_low;
}

class ClockCounter {
public:
    ClockCounter() :
        ticktime(0) {
        start();
    }

    unsigned long long ticktime;

    void start() {
        ticktime = startRDTSC();
    }

    unsigned long long stop() {
        return stopRDTSCP() - ticktime;

    }
};

#endif
