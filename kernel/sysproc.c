#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
	return fork();
}

int
sys_exit(void)
{
	exit();
	return 0;  // not reached
}

int
sys_wait(void)
{
	return wait();
}

int
sys_kill(void)
{
	int pid;

	if(argint(0, &pid) < 0)
		return -1;
	return kill(pid);
}

int
sys_getpid(void)
{
	return myproc()->pid;
}

int
sys_sbrk(void)
{
	int addr;
	int n;

	if(argint(0, &n) < 0)
		return -1;
	addr = myproc()->sz;
	if(growproc(n) < 0)
		return -1;
	return addr;
}

int
sys_sleep(void)
{
	int n;
	uint ticks0;

	if(argint(0, &n) < 0)
		return -1;
	acquire(&tickslock);
	ticks0 = ticks;
	while(ticks - ticks0 < n){
		if(myproc()->killed){
			release(&tickslock);
			return -1;
		}
		sleep(&ticks, &tickslock);
	}
	release(&tickslock);
	return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
	uint xticks;

	acquire(&tickslock);
	xticks = ticks;
	release(&tickslock);
	return xticks;
}

int
sys_share_mem(void)
{
	char *name;
	void *addr;
	int size;
	if (argstr(0, &name) < 0 || argint(2, &size) < 0 || argptr(1, &addr, size) < 0)
		return -1;

	if (!addr)
		return -1;

	struct proc *curproc = myproc();

	struct shared *shr = 0;
	for (int i = 0; i < SHRD_SIZ; ++i) {
		if (!strncmp(name, curproc->shr[i].name, SHRD_NAME_SIZ)) {
			return -2;
		}

		if (curproc->shr[i].size == 0) {
			shr = &curproc->shr[i];
			break;
		}
	}

	if (!shr)
		return -3;

	shr->mem = addr;
	strncpy(shr->name, name, SHRD_NAME_SIZ);
	shr->size = size;
	
	cprintf("%s %s %d\n", shr->name, (char *)shr->mem, shr->size);

	return 0; // @TODO: vrati redni broj strukture
}
