#ifndef LAB0_H
#define LAB0_H

#include <stdio.h>
#include <kernel.h>

extern unsigned long ctr1000;
#define PROCESSLIMIT 50

#define CALLLIMIT 27

struct syscall_summary {
    int occurance_cnt;
    long run_times;
    int isTracingOn;
    char syscall_name[30];
};

extern struct syscall_summary all_syscalls_info[PROCESSLIMIT][CALLLIMIT];
extern int trackingOn;

extern long zfunction(long param);
extern void printprocstks(int priority);
extern void syscallsummary_start();
extern void syscallsummary_stop();
extern void printsyscallsummary();

#endif
