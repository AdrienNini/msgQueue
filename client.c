#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct data{
	int pid; 
	char filename[50];
};

struct msg{
	long type;
	struct data d;
};

int main(int argc, char *argv[]){

	int msgqid;
	struct msg m;

	m.d.pid = getpid();
	if (argc == 2){
		strcpy(m.d.filename, argv[1]);
	}	

	m.type = 1;
	
	msgqid = msgget(77, 0666|IPC_CREAT);
	
	int result;
	if ((result = msgsnd(msgqid, &m, sizeof(m.d), 0) == -1)){
		char errorMsg[] = "Error\n";
		write(1, errorMsg, sizeof errorMsg);
		return(-1);
	} else {
		char successMsg[] = "Message sent\n";
		write(1, successMsg, sizeof successMsg);
		return(1);
	}

	return 1;

}
