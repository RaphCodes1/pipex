#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h> 
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main()
{
    // int pid1 = fork();
    // int pid2 = fork();
    // if(pid1 < 0 || pid2 < 0)
    // {
    //     printf("fork failed");
    //     exit(1);
    // }    
    // if(pid1 == 0)
    // {
    //     if(pid2 == 0)
    //         printf("in Y child process\n");
    //     else
    //         printf("in X child process\n");
    // }
    // else
    // {
    //     if(pid2 == 0)
    //         printf("in Z child process\n");
    //     else
    //         printf("in the parent process\n");
    // }
    // while(wait(NULL) != -1 || errno != ECHILD)
    // {
    //     printf("waited till child to finish\n");
    // }
    // return 0;


    // int fd[2]; // pipe // 0 -> read, 1 ->write
    // if(pipe(fd) == -1)
    //     printf("error");
    // int arr[] = {1,2,3,4,5,6,7,8};
    // int argLen = sizeof(arr) / sizeof(int);
    // int start,end;
    // int pid = fork();
    // int pid2 = fork();
    // if(pid == -1)
    //     printf("error");
    // if(pid == 0)
    // {   
    //     if(pid2 == 0)
    //     {
    //         start = 0;
    //         end = argLen / 2;
    //     }
        
    // }
    // else
    // {   
    //     if(pid2 != 0)
    //     {
            
    //         start = argLen / 2;
    //         end = argLen;
    //     }
    //     else 
    //     {
    //         start = argLen;
    //         end = argLen;
    //         wait(NULL);
            
    //     }
    // }
    // int i = start;
    // int sum1 = 0;
    // int sum2 = 0;
    // while(i < end)
    // {   
    //     if(pid2 == 0)
    //         sum1 += arr[i++];
    //     else if(pid2 != 0)
    //         sum2 += arr[i++];
    // }
    // if(pid == 0)
    // {   
    //     if(pid2 == 0)
    //     {
    //         close(fd[0]);
    //         write(fd[1],&sum1,sizeof(sum1));
    //         close(fd[1]);
    //         printf("1 sum: %d\n",sum1);
    //     }
    // }
    // else
    // {   

    //     if(pid2 != 0)
    //     {
    //         close(fd[0]);
    //         write(fd[1],&sum2,sizeof(sum2));
    //         close(fd[1]);
    //         printf("2 sum: %d\n",sum2);
    //     }
    //     else 
    //     {
    //         int totalSum;
    //         close(fd[1]);
    //         read(fd[0],&totalSum,sizeof(int));
    //         close(fd[0]);

    //         int test = totalSum + sum1;
    //         printf("total sum: %d\n",test);
    //         wait(NULL);
    //     }
    // }

    // PIPE Simulator

    // int fd[2];
    // int txtfile = open("hello.txt", O_WRONLY | O_CREAT);
    // if(pipe(fd) == -1)
    //     return 1;
    
    // int pid1 = fork();
    // int pid2 = fork();

    // if(pid1 < 0)
    //     return 2;
    // if(pid2 < 0)
    //     return 3;
    
    // if(pid1 == 0)
    // {
    //     //first command
    //     dup2(fd[1],STDOUT_FILENO);
    //     close(fd[0]);
    //     close(fd[1]);
    //     execlp("cat", "cat", "txtfile", NULL);
    // }
    // if(pid2 == 0)
    // {   
    //     //second command
    //     dup2(fd[0],STDIN_FILENO);
    //     close(fd[1]);
    //     close(fd[0]);
    //     execlp("wc","wc","-l",NULL);
    // }

    // close(fd[1]);
    // close(fd[0]);
    // close(txtfile);
    // waitpid(pid1,NULL,0);
    // waitpid(pid2,NULL,0);

    // dup2 and dup and access
    int txtfile = open("hello.txt",O_WRONLY | O_CREAT, 0644);
    int main_out = dup(1);
    dup2(txtfile,STDOUT_FILENO);
    close(txtfile);
    printf("example of hello file!"); 
    unlink("hello.txt");
    if(access("hello.txt",R_OK) != -1)
        printf("ok permission");
    else
        printf("NO permission");

    //execve()

    char *args[3];

	args[0] = "ls";
	args[1] = "-l";
	args[2] = NULL;
	execve("/bin/ls", args, NULL);
	printf("This line will not be executed.\n");

	return (0);
}