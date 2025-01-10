/* sleep.c - sleep */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
#include <lab0.h>
#include <proc.h>

/*------------------------------------------------------------------------
 * sleep  --  delay the calling process n seconds
 *------------------------------------------------------------------------
 */
SYSCALL	sleep(int n)
{
	STATWORD ps;    
	int syscall_num = 18;
    long start_time = ctr1000;
	if (trackingOn) {
		all_syscalls_info[currpid][syscall_num].occurance_cnt++;
	}
	if (n<0 || clkruns==0){
		if (trackingOn) {
			all_syscalls_info[currpid][syscall_num].run_times += (ctr1000 - start_time);
		}			
		return(SYSERR);
	}
	if (n == 0) {
	        disable(ps);
		resched();
		restore(ps);
		if (trackingOn) {
			all_syscalls_info[currpid][syscall_num].run_times += (ctr1000 - start_time);
		}			
		return(OK);
	}
	while (n >= 1000) {
		sleep10(10000);
		n -= 1000;
	}
	if (n > 0)
		sleep10(10*n);
	if (trackingOn) {
		all_syscalls_info[currpid][syscall_num].run_times += (ctr1000 - start_time);
	}			
	return(OK);
}
