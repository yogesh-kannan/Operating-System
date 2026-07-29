#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
   int fd[2];
   pid_t pid;
   char w_msg[] = "Hello from parent";
   char r_msg[100];
   
   if(pipe(fd) == -1){
      perror("Pipe connection failed");
      return 1;
   }
   
   pid = fork();
   if(pid < 0){
      perror("Fork creation failed");
      return 1;
   }
   
   if(pid == 0){
      close(fd[1]);
      int byte_r = read(fd[0], r_msg, sizeof(r_msg) - 1); 
      if(byte_r > 0){
         r_msg[byte_r] = '\0';
         printf("Child Received: %s\n", r_msg); 
      }
      close(fd[0]);
   }
   else{
     
      close(fd[0]); 
      
      printf("Parent sending: %s\n", w_msg);
      write(fd[1], w_msg, strlen(w_msg) + 1);
      close(fd[1]); 
      wait(NULL); 
   }
   return 0;
}
