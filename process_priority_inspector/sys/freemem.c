/* freemem.c - freemem */

#include <conf.h>
#include <kernel.h>
#include <mem.h>
#include <stdio.h>
#include <proc.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 *  freemem  --  free a memory block, returning it to memlist
 *------------------------------------------------------------------------
 */
SYSCALL	freemem(struct mblock *block, unsigned size)
{
    int syscall_num = 0;
    long start_time = ctr1000;
	int pid = currpid;
	if (trackingOn) {
		all_syscalls_info[pid][syscall_num].occurance_cnt++;
	}
	STATWORD ps;
    disable(ps);

	struct	mblock	*p, *q;
	unsigned top;

    if (size == 0 || (unsigned)block > (unsigned)maxaddr || ((unsigned)block) < ((unsigned)&end)) {
        restore(ps);
		if (trackingOn) {
			all_syscalls_info[pid][syscall_num].run_times += (ctr1000 - start_time);
		}
        return (SYSERR);
    }
	size = (unsigned)roundmb(size);
	disable(ps);
	for( p=memlist.mnext,q= &memlist;
	     p != (struct mblock *) NULL && p < block ;
	     q=p,p=p->mnext )
		;
	if (((top=q->mlen+(unsigned)q)>(unsigned)block && q!= &memlist) ||
	    (p!=NULL && (size+(unsigned)block) > (unsigned)p )) {
		restore(ps);
		if (trackingOn) {
			all_syscalls_info[pid][syscall_num].run_times += (ctr1000 - start_time);
		}			
		return(SYSERR);
	}
	if ( q!= &memlist && top == (unsigned)block )
			q->mlen += size;
	else {
		block->mlen = size;
		block->mnext = p;
		q->mnext = block;
		q = block;
	}
	if ( (unsigned)( q->mlen + (unsigned)q ) == (unsigned)p) {
		q->mlen += p->mlen;
		q->mnext = p->mnext;
	}
	restore(ps);
	if (trackingOn) {
		all_syscalls_info[pid][syscall_num].run_times += (ctr1000 - start_time);
	}
	return(OK);
}
