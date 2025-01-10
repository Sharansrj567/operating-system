#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#define EXPDISTSCHED 1
#define LINUXSCHED 2

extern int sched_class;

void setschedclass(int scheduler_type);
int getschedclass();

#endif