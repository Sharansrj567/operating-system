/* resched.c  -  resched */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <math.h>
#include <sched.h>


int getexponentialprocess(double val){
    //for loop to inerate through all the processes
    if (q[rdyhead].qnext == rdytail) {
        return NULLPROC;
    }
    int highestprocess = NULLPROC;
    int i;
    for (i = q[rdytail].qprev; i != rdyhead; i = q[i].qprev) {
        //got error to fix empty queues i have to check if highestprocess is more than 0
        if (i < 0 || i >= NPROC) {
            return NULLPROC;
        }
        if (proctab[i].pprio>val){
            if (highestprocess == NULLPROC || proctab[i].pprio < proctab[highestprocess].pprio) {
                highestprocess = i;
            }
        }
    }
    if (highestprocess == NULLPROC || highestprocess >= NPROC) {
        return NULLPROC;
    }
    return (highestprocess);
}

int* myhighestvalsfunction(){
    static int myhighestvals[2];
    myhighestvals[0]=NULLPROC;
    myhighestvals[1]=-1;
    int c=q[rdytail].qprev;
    struct pentry *proc;
    while(c!=rdyhead){
        proc=&proctab[c];
        if(proc->pprio>myhighestvals[1]){
            myhighestvals[1]=proc->pprio;
            myhighestvals[0]=c;
        }
        c=q[c].qprev;
    }
    return &myhighestvals[0];
}


unsigned long currSP;	/* REAL sp of current process */
extern int ctxsw(int, int, int, int);
/*-----------------------------------------------------------------------
 * resched  --  reschedule processor to highest priority ready process
 *
 * Notes:	Upon entry, currpid gives current process id.
 *		Proctab[currpid].pstate gives correct NEXT state for
 *			current process if other than PRREADY.
 *------------------------------------------------------------------------
 */
int resched()
{
    static int print_handler = 0;
	register struct	pentry	*optr;	/* pointer to old process entry */
	register struct	pentry	*nptr;	/* pointer to new process entry */
    int highestprocess;
    int epochcnt=0;
	optr = &proctab[currpid];
    char currscheduler=getschedclass();
	if (currscheduler== EXPDISTSCHED) {
            double random = expdev(0.1);
            highestprocess = getexponentialprocess(random);
        //checking if curr running process is between the highest priority process and the random value
        if ((highestprocess != NULLPROC && (optr= &proctab[currpid])->pstate == PRCURR) &&
            (((q[highestprocess].qkey > optr->pprio) && (optr->pprio > random)) || (highestprocess == NULLPROC))) {
            #ifdef	RTCLOCK
                preempt = QUANTUM;		/* reset preemption counter	*/
            #endif
            return (OK);
        }

//making process ready
        if (optr->pstate == PRCURR) {
            optr->pstate = PRREADY;
            insert(currpid, rdyhead, optr->pprio);
        }
//fallback logic
        if (highestprocess == NULLPROC) {
            highestprocess = getlast(rdytail);
        }
//removing from rdy queue
        int nextprocid = highestprocess;
        dequeue(nextprocid);
        nptr = &proctab[(currpid = nextprocid)];
        nptr->pstate = PRCURR;
//reset
        #ifdef RTCLOCK
            preempt = QUANTUM;
        #endif

        // Perform the context switch
        ctxsw((int)&optr->pesp, (int)optr->pirmask, (int)&nptr->pesp, (int)nptr->pirmask);
        return OK;

    }else if (currscheduler==LINUXSCHED){
        //making a counter for epochs
        static int epochcnt = 0;
        //customfunctioon which gets latest high good process
        int* myhighestvals = myhighestvalsfunction();
        int highestgoodproc = myhighestvals[0];
        int highestgoodnessval = myhighestvals[1];
        struct pentry *proc; 

        // Checking if we need new epoch
        if (epochcnt <= 0 || isempty(rdyhead)) {
            // Start a new epoch
            epochcnt = 0;
            int iter;
            for (iter = 1; iter < NPROC; iter++) {
                proc = &proctab[iter];
                if (proc->pstate != PRFREE) {
                    // if(proc->counter>0){
                        proc->quantum = proc->pprio+ (proc->counter / 2);
                    // }else{
                    //     proc->quantum = proc->pprio;
                    // }
                    proc->counter = proc->quantum;
                    //edgecases handling to prevent errors
                    proc->goodness = (proc->counter > 0) ? proc->counter + proc->pprio : proc->pprio;
                    epochcnt += proc->quantum;
                }
            }
        }

        // Updating current process
        if (currpid != 0) {
            int tempdiff = optr->counter - preempt;
            epochcnt = (epochcnt > tempdiff) ? epochcnt - tempdiff : 0;
            optr->counter = preempt;
            optr->goodness = (optr->counter > 0) ? optr->counter + optr->pprio : 0;
            if (optr->counter <= 0) {
                optr->counter = 0;
                optr->goodness = 0;
            } else {
                optr->goodness = optr->counter + optr->pprio;
            }
        }

        //again calling magic function to get new high vals
        myhighestvals = myhighestvalsfunction();
        highestgoodproc = myhighestvals[0];
        highestgoodnessval = myhighestvals[1];

        // Again checking if current process should run
        if (optr->pstate == PRCURR && optr->goodness > 0) {
            return OK;
        }

        // Move current process to ready queue if it's still running
        if (optr->pstate == PRCURR && optr->goodness <= 0) {
            optr->pstate = PRREADY;
            insert(currpid, rdyhead, optr->goodness);
        }

        // selecting next process to run
        if (highestgoodproc != NULLPROC && highestgoodnessval > 0) {
            currpid = highestgoodproc;
            nptr = &proctab[currpid];
            dequeue(currpid);
        } else {
            epochcnt = 0;
        int i;
        for (i = 1; i < NPROC; i++) {
            proc = &proctab[i];
        }
    // again getting enw vals
    myhighestvals = myhighestvalsfunction();
    highestgoodproc = myhighestvals[0];
    highestgoodnessval = myhighestvals[1];
    if (highestgoodproc != NULLPROC && highestgoodnessval > 0) {
        currpid = highestgoodproc;
        nptr = &proctab[currpid];
        dequeue(currpid);
    } else {
            // running null process
            currpid = 0;
            nptr = &proctab[0];
        }
    //last time getting new vals
    myhighestvals = myhighestvalsfunction();
    highestgoodproc = myhighestvals[0];
    highestgoodnessval = myhighestvals[1];
    }
if (currpid != 0) {
    #ifdef RTCLOCK
        preempt = nptr->counter;
    #endif

    nptr->pstate = PRCURR;
    ctxsw((int)&optr->pesp, (int)optr->pirmask, (int)&nptr->pesp, (int)nptr->pirmask);
}

return OK;
}else{
	/* no switch needed if current process priority higher than next*/
	if ( ( (optr= &proctab[currpid])->pstate == PRCURR) &&
	   (lastkey(rdytail)<optr->pprio)) {
		return(OK);
    }
	}
	
	/* force context switch */

	if (optr->pstate == PRCURR) {
		optr->pstate = PRREADY;
		insert(currpid,rdyhead,optr->pprio);
	}

    if (currscheduler == EXPDISTSCHED) {
		/* remove the next highest priority process from remaining of ready list */
        //now get one more highestprocess
		int newhighestprocess = getexponentialprocess(q[highestprocess].qkey);
        currpid = newhighestprocess;
        nptr = &proctab[(currpid) ];
	} else {
	/* remove highest priority process at end of ready list */

	nptr = &proctab[ (currpid = getlast(rdytail)) ];
    }
	nptr->pstate = PRCURR;		/* mark it currently running	*/
#ifdef	RTCLOCK
	preempt = QUANTUM;		/* reset preemption counter	*/
#endif
	
	ctxsw((int)&optr->pesp, (int)optr->pirmask, (int)&nptr->pesp, (int)nptr->pirmask);

	/* The OLD process returns here when resumed. */
	return OK;
}
