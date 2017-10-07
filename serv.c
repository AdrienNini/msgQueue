#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct data{
	int pid;
	char filename[50];
};

int main(){

	int msgqid;
	struct data d;

	msgqid = msgget(77, 0666|IPC_CREAT);
	
	if ((msgrcv(msgqid, &d, sizeof d, 1, 0)) == -1){
		char errorMsg[] = "Error";
		write(1, errorMsg, sizeof errorMsg);
		return(-1);	
	}
	
	write(1, d.filename, sizeof d.filename);
	printf("\n");
	

	return 0;
}
