#include "types.h"
#include "stat.h"
#include "user.h"
#define passwdFile "/passwd"
#define maxLenght 100

int contains (char *str, char *pattern){
	int i = 0, j = 0;
	int sizeStr = strlen(str);
	int sizePattern = strlen(pattern);

	while( i < sizePattern && j < sizeStr && pattern[i] != str[j]){
		j++;
	}
	if (j == sizeStr)
	{
		return 0;
	}
	while(i < sizePattern && j < sizeStr && pattern[i] == str[j]){
		i++;
		j++;
	}
	if (i == sizePattern)
	{
		return 1;
	} else {
		return 0;
	}
}

int readLine(int fd, char *buf, int size){
	int i = 0, n = 0;
	char c;
	while(read(fd, &c, 1) > 0){
		n++;
		if(c != '\n'){
			buf[i] = c;
			i++;
			if (i == size - 1){
				break;
			}
		}else{
			break;
		}
	}
	buf[i] = '\0';
	return n;
}

int
main(int argc, char *argv[])
{
	int fd;
	char record[maxLenght];
	char userName[maxLenght];
	char userPassword[maxLenght];
	int n, pid, wpid;
	char *shArgv[] = { "sh", 0};

	//printf("userName = %s, userPassword = %s",userName, userPassword );
	while(1){

		printf(1, "login: ");
		memset(userName, 0,sizeof(userName));
		read(0, userName, sizeof(userName));
		userName[strlen(userName) -1] = ':';
		printf(1, "password: ");
		memset(userPassword, 0,sizeof(userPassword));
		read(0, userPassword, sizeof(userPassword));
		userPassword[strlen(userPassword) -1] = ':';

		fd = open(passwdFile, 0);

		while((n = readLine(fd, record, sizeof(record))) > 0) {
			printf(1,"%s\n", record );
	 		if (contains(record, userName) && contains(record, userPassword))
	 		{
	 			pid = fork();
	 			if (pid < 0)
	 			{
	 				printf(1, "login: fork failed\n");
	 				exit();
	 			}
	 			if (pid == 0)
	 			{
	 				exec("sh", shArgv);
	 				printf(1,"init: exec sh failed\n");
	 				exit();
	 			}
	 			while((wpid = wait()) >= 0 && wpid != pid){
	 				printf(1, "zombie!\n");
	 			}
	 			break;
	 		}
	 	}
	 	close(fd);
	}
	exit();
}