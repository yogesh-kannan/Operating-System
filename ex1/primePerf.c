#include<stdio.h>
#include<unistd.h>
int isPrime(int n){
   if(n<=1)
      return 0;
   int i;
   for(i=2;i<n;i++){
      if(n%i==0)
	 return 0;
   }
   return 1;
}
int isPerfect(int n){
   if(n<=1)
      return 0;
   int i,c=0;
   for(i=1;i<n;i++){
      if(n%i==0)
	 c+=i;
   }
   if(c==n)
      return 1;
   else
      return 0;
}
int main(){
   int n,p1,p2;
   printf("Enter no of element:\n");
   scanf("%d",&n);
   int arr[n],i;
   p1=fork();
   if(p1==0){
      printf("Child 1 process\nEnter the element:\n");
      for(i=0;i<n;i++)
	 scanf("%d",&arr[i]);
      for(i=0;i<n;i++){
	 if(isPrime(arr[i]))
	    printf("%d ",arr[i]);
      }
   }
   else{
      wait(NULL);
      printf("\nChild 2 process\nEnter the element:\n");
      for(i=0;i<n;i++)
	 scanf("%d",&arr[i]);
      for(i=0;i<n;i++){
	 if(isPerfect(arr[i]))
	    printf("%d ",arr[i]);
      }
   }
   return 0;
}
