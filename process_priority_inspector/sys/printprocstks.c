#include<stdio.h>
#include <kernel.h>
#include <proc.h>

void printprocstks(int priority)
{
 int i;
 unsigned long current_one;
 kprintf("void printprocstks(int priority)\n");
 asm("movl %%esp, %0" : "=r" (current_one));
 for(i=0; i<NPROC; i++)
 {
  struct pentry *proc = &proctab[i];
  int procPriority = proc->pprio;
  if(proc->pprio > priority && proc->pstate != PRFREE)
  {
    printf("Process [%s]\n", proc->pname);
    printf("    pid: %d\n", i);
    printf("    priority: %d\n", procPriority);
    printf("    base: 0x%08x\n", proc->pbase);
    printf("    limit: 0x%08x\n", proc->plimit);
    printf("    len: %d\n", proc->pstklen);
    int isCurrentProcess =0;
    if(i==currpid){
      isCurrentProcess = 1;
    }

    isCurrentProcess==1?printf("    pointer: 0x %08x\n", current_one) : printf("    pointer: 0x %08x\n", proc->pesp);
  }
 }
}