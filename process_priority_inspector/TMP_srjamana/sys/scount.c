/* scount.c - scount */

#include <conf.h>
#include <kernel.h>
#include <sem.h>
#include <lab0.h>
#include <proc.h>

/*------------------------------------------------------------------------
 *  scount  --  return a semaphore count
 *------------------------------------------------------------------------
 */
SYSCALL scount(int sem)
{
extern	struct	sentry	semaph[];
	int syscall_num = 10;
    long start_time = ctr1000;
	if (trackingOn) {
		all_syscalls_info[currpid][syscall_num].occurance_cnt++;
	}
	if (isbadsem(sem) || semaph[sem].sstate==SFREE)
		return(SYSERR);
	if (trackingOn) {
		all_syscalls_info[currpid][syscall_num].run_times += (ctr1000 - start_time);
	}	
	return(semaph[sem].semcnt);
}
