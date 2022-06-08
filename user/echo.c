#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

char sharedMem[] = "ABCD";
char *name = "Shared1";
int size = 5;

char sharedMem2[] = "ABCD";
char *name2 = "Shared2";
int size2 = 5;

char sharedMem3[] = "ABCD";
char *name3 = "Shared3";
int size3 = 5;

char sharedMem4[] = "ABCD";
char *name4 = "Shared4";
int size4 = 5;

char sharedMem5[] = "ABCD";
char *name5 = "Shared5";
int size5 = 5;

char sharedMem6[] = "ABCD";
char *name6 = "Shared6";
int size6 = 5;

char sharedMem7[] = "ABCD";
char *name7 = "Shared7";
int size7 = 5;

char sharedMem8[] = "ABCD";
char *name8 = "Shared8";
int size8 = 5;

char sharedMem9[] = "ABCD";
char *name9 = "Shared9";
int size9 = 5;

char sharedMem10[] = "ABCD";
char *name10 = "Shared10";
int size10 = 5;

char sharedMem11[] = "ABCD";
char *name11 = "Shared11";
int size11 = 5;

int
main(int argc, char *argv[])
{
	printf("share_mem return: %d\n", share_mem(name, sharedMem, size));
	printf("share_mem return: %d\n", share_mem(name2, sharedMem2, size2));
	printf("share_mem return: %d\n", share_mem(name3, sharedMem3, size3));
	printf("share_mem return: %d\n", share_mem(name4, sharedMem4, size4));
	printf("share_mem return: %d\n", share_mem(name5, sharedMem5, size5));
	printf("share_mem return: %d\n", share_mem(name6, sharedMem6, size6));
	printf("share_mem return: %d\n", share_mem(name7, sharedMem7, size7));
	printf("share_mem return: %d\n", share_mem(name8, sharedMem8, size8));
	printf("share_mem return: %d\n", share_mem(name9, sharedMem9, size9));
	printf("share_mem return: %d\n", share_mem(name10, sharedMem10, size10));

	int pid = fork();

	if (pid < 0) {
		printf("error\n");
	}

	if (pid > 0) {
		printf("child\n");
	}

	if (pid == 0) {
		printf("parent\n");
	}

	wait();
	exit();

	//for(int i = 1; i < argc; i++)
	//	printf("%s%s", argv[i], i+1 < argc ? " " : "\n");
	//exit();
}
