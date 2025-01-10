#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

struct syscall_summary all_syscalls_info[NPROC][CALLLIMIT];
int trackingOn = 0;

extern struct pentry proctab[];

void syscallsummary_start() {
int x,y;
    for (x = 0; x < NPROC; x++) {
        for (y = 0; y < CALLLIMIT; y++) {
            all_syscalls_info[x][y].occurance_cnt = 0;
            all_syscalls_info[x][y].run_times = 0;
            all_syscalls_info[x][y].isTracingOn = 1;
            switch (y) {
                case 0: strncpy(all_syscalls_info[x][y].syscall_name, "freemem", 30); break;
                case 1: strncpy(all_syscalls_info[x][y].syscall_name, "chprio", 30); break;
                case 2: strncpy(all_syscalls_info[x][y].syscall_name, "getpid", 30); break;
                case 3: strncpy(all_syscalls_info[x][y].syscall_name, "getprio", 30); break;
                case 4: strncpy(all_syscalls_info[x][y].syscall_name, "gettime", 30); break;
                case 5: strncpy(all_syscalls_info[x][y].syscall_name, "kill", 30); break;
                case 6: strncpy(all_syscalls_info[x][y].syscall_name, "receive", 30); break;
                case 7: strncpy(all_syscalls_info[x][y].syscall_name, "recvclr", 30); break;
                case 8: strncpy(all_syscalls_info[x][y].syscall_name, "recvtim", 30); break;
                case 9: strncpy(all_syscalls_info[x][y].syscall_name, "resume", 30); break;
                case 10: strncpy(all_syscalls_info[x][y].syscall_name, "scount", 30); break;
                case 11: strncpy(all_syscalls_info[x][y].syscall_name, "sdelete", 30); break;
                case 12: strncpy(all_syscalls_info[x][y].syscall_name, "send", 30); break;
                case 13: strncpy(all_syscalls_info[x][y].syscall_name, "setdev", 30); break;
                case 14: strncpy(all_syscalls_info[x][y].syscall_name, "setnok", 30); break;
                case 15: strncpy(all_syscalls_info[x][y].syscall_name, "screate", 30); break;
                case 16: strncpy(all_syscalls_info[x][y].syscall_name, "signal", 30); break;
                case 17: strncpy(all_syscalls_info[x][y].syscall_name, "signaln", 30); break;
                case 18: strncpy(all_syscalls_info[x][y].syscall_name, "sleep", 30); break;
                case 19: strncpy(all_syscalls_info[x][y].syscall_name, "sleep10", 30); break;
                case 20: strncpy(all_syscalls_info[x][y].syscall_name, "sleep100", 30); break;
                case 21: strncpy(all_syscalls_info[x][y].syscall_name, "sleep1000", 30); break;
                case 22: strncpy(all_syscalls_info[x][y].syscall_name, "sreset", 30); break;
                case 23: strncpy(all_syscalls_info[x][y].syscall_name, "stacktrace", 30); break;
                case 24: strncpy(all_syscalls_info[x][y].syscall_name, "suspend", 30); break;
                case 25: strncpy(all_syscalls_info[x][y].syscall_name, "unsleep", 30); break;
                case 26: strncpy(all_syscalls_info[x][y].syscall_name, "wait", 30); break;
                default: strncpy(all_syscalls_info[x][y].syscall_name, "sys_unknown", 30); break;
            }
        }
    }
    trackingOn = 1;
}

void syscallsummary_stop() {
    int d;
    for (d = 0; d < CALLLIMIT; d++) {
        all_syscalls_info[currpid][d].isTracingOn = 0;
    }
}

void printsyscallsummary() {
    int f, g;
    kprintf("\nvoid printsyscallsummary()\n");
    for (f = 0; f < NPROC; f++) {
        int pid_printed = 0;
        for (g = 0; g < CALLLIMIT; g++) {
            if (all_syscalls_info[f][g].occurance_cnt > 0) {
                if (!pid_printed) {
                    char *process_name = proctab[f].pname;
                    if (strlen(process_name) == 0) {
                        process_name = "unknown";
                    }
                    kprintf("Process [pid:%d]\n", f, process_name);
                    pid_printed = 1;
                }
                int occurrences = all_syscalls_info[f][g].occurance_cnt;
                long total_runtime = all_syscalls_info[f][g].run_times;
                long avg_runtime = total_runtime / occurrences;
                kprintf("    Syscall: sys_%s, count: %d, average execution time: %ld (ms)\n",
                        all_syscalls_info[f][g].syscall_name, occurrences, avg_runtime);
            }
        }
    }
}