/* sleep1000.c - sleep1000 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 * sleep1000 --  delay the caller for a time specified in 1/100 of seconds
 *------------------------------------------------------------------------
 */
SYSCALL sleep1000(int n)
{
	STATWORD ps;    
	int syscall_num = 21;
    long start_time = ctr1000;
	int pid = currpid;
	if (trackingOn) {
		all_syscalls_info[pid][syscall_num].occurance_cnt++;
	}
    if (n < 0  || clkruns == 0) {
		if (trackingOn) {
			all_syscalls_info[pid][syscall_num].run_times += (ctr1000 - start_time);
		}
        return (SYSERR);
    }

	if (n < 0  || clkruns==0){
		if (trackingOn) {
			all_syscalls_info[pid][syscall_num].run_times += (ctr1000 - start_time);
		}		
	         return(SYSERR);
}			 
	disable(ps);
	if (n == 0) {		/* sleep1000(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
        restore(ps);
	if (trackingOn) {
		all_syscalls_info[pid][syscall_num].run_times += (ctr1000 - start_time);
	}
	return(OK);
}
