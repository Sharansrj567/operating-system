#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern long zfunction(long param);
/*------------------------------------------------------------------------
 *  main  --  user main program
 *------------------------------------------------------------------------
 */

int main()
{
	kprintf("input: 0xaabbccdd , output: 0x%lx\n", zfunction(0xaabbccdd));	
	create(printprocstks, 2000, 20, "printprocstks", 1, 1);
	printprocstks(1);
	syscallsummary_start();
	int i;
	kprintf("Pid of main is ", currpid);
	for (i = 0; i < 5; i++) {
		freemem(0, 100);
		freemem(0, 100);
		freemem(0, 100);
		chprio(1, 20);
		getpid();
		getprio(1);
		gettime(5);
		kill(1);
		recvclr();
		recvtim(10);
		resume(1);
		scount(1);
		sdelete(1);
		send(1, 2);
		setdev(1, 2, 2);
		setnok(1, 2);
		screate(1);
		signal(1);
		signaln(1, 2);
		sleep(1);
		sleep10(1);
		sleep100(1);
		sleep1000(1);
		sreset(1,4);
		stacktrace(1);
		suspend(1);
		unsleep(1);
		wait(1);
	}
	syscallsummary_stop();
	printsyscallsummary();
	// kprintf("\n\nHello CSC 501\n\n");
	return 0;
}
