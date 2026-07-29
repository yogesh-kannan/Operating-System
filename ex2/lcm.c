#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 

int gcd(int a, int b){
   while(b != 0){
      int t = b;
      b = a % b;
      a = t;
   }
   return a;
}

int main(){
   int fd[2], lcm, arr[2], i;
   
   if(pipe(fd) == -1) {
      perror("Pipe failed");
      return 1;
   }
   
   pid_t pid = fork();
   if(pid < 0) {
      perror("Fork failed");
      return 1;
   }
   
   if(pid == 0){
      close(fd[0]);
      
      printf("Enter two numbers: ");
      for(i = 0; i < 2; i++) {
         scanf("%d", &arr[i]);
      }
      
     
      write(fd[1], arr, 2 * sizeof(int));
      close(fd[1]);
   }
   else{
     
      close(fd[1]);
      
     
      read(fd[0], arr, 2 * sizeof(int));
      close(fd[0]);
      
      lcm = (arr[0] * arr[1]) / gcd(arr[0], arr[1]);
      printf("LCM = %d\n", lcm);
      
      wait(NULL);
   }
   return 0;
}
