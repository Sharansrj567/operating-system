/* getpid.c - getpid */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 * getpid  --  get the process id of currently executing process
 *------------------------------------------------------------------------
 */
SYSCALL getpid()
{
	int syscall_num = 2;
    long start_time = ctr1000;
	if (trackingOn) {
		all_syscalls_info[currpid][syscall_num].occurance_cnt++;
	}
	if (trackingOn) {
		all_syscalls_info[currpid][syscall_num].run_times += (ctr1000 - start_time);
	}	
	return(currpid);
}
