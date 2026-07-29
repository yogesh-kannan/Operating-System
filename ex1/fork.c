#include<stdio.h>
#include<unistd.h>
void main(){//p1
   int p2,p3,p4,p5;
   p2=fork();
   if(p2==0){
      printf("p2:pid %d ppid %d\n",getpid(),getppid());
   }
   else{
      printf("p1:pid %d ppid %d\n",getpid(),getppid());
      p3=fork();
      if(p3==0){
	 p4=fork();
	 if(p4==0){
	    printf("p4 pid %d ppid %d\n",getpid(),getppid());
	 }
	 else{
	    printf("p3 pid %d ppid %d\n",getpid(),getppid());
	    p5=fork();
	    if(p5==0){
	       printf("p5 pid %d ppid %d\n",getpid(),getppid());
	    }
	 }
      }
      else{
	 wait(0);
      }
   }
}
