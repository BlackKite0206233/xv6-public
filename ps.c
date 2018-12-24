#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"

enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };
struct proc {
  enum procstate state; // Process state
  int pid;              // Process ID
  int ppid ;            // Parent process ID
  char name[16];        // Process name 
};
int
main(void)
{  
  struct proc ptable[NPROC];
  struct proc *p;
  int err;
  
  err = getptable(10 * sizeof(struct proc), &ptable);
  if (err != 0)
    printf(1, "Error getting ptable");
  
  p = &ptable[0];
  printf(1, "PID\tPPID\tSTATE\tCMD\n");
  while (p != &ptable[NPROC - 1] && p->state != UNUSED) {
  	printf(1, "%d\t%d", p->pid, p->ppid);
  	switch (p->state) {
  	case UNUSED:
  		printf(1, "\t%s", "UNUSED");
  		break;
  	case EMBRYO:
  		printf(1, "\t%s", "EMBRYO");
  		break;
  	case SLEEPING:
  		printf(1, "\t%s", "SLEEPING");
  		break;
  	case RUNNABLE:
  		printf(1, "\t%s", "RUNNABLE");
  		break;
  	case RUNNING:
  		printf(1, "\t%s", "RUNNABLE");
  		break;
  	case ZOMBIE:
  		printf(1, "\t%s", "RUNNABLE");
  		break;
  	} 
  	printf(1, "\t%s\n", p->name);
  	p++;
  }
  	  
  exit();
}