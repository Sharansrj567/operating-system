/* signal.c - signal */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 * signal  --  signal a semaphore, releasing one waiting process
 *------------------------------------------------------------------------
 */
SYSCALL signal(int sem)
{
	STATWORD ps;    
	register struct	sentry	*sptr;
	int syscall_num = 16;
    long start_time = ctr1000;
	if (trackingOn) {
		all_syscalls_info[currpid][syscall_num].occurance_cnt++;
	}

	disable(ps);
	if (isbadsem(sem) || (sptr= &semaph[sem])->sstate==SFREE) {
		restore(ps);
		if (trackingOn) {
			all_syscalls_info[currpid][syscall_num].run_times += (ctr1000 - start_time);
		}			
		return(SYSERR);
	}
	if ((sptr->semcnt++) < 0)
		ready(getfirst(sptr->sqhead), RESCHYES);
	restore(ps);
	if (trackingOn) {
		all_syscalls_info[currpid][syscall_num].run_times += (ctr1000 - start_time);
	}
	return(OK);
}
