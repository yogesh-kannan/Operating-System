#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h> // Required for wait()

int main(){
   int p1, p3, i;
   char str[100];
   
   // 1. Get input FIRST so both children safely inherit the exact same string
   printf("Enter the string: ");
   fgets(str, sizeof(str), stdin);
   
   p1 = fork();
   if(p1 == 0){
      // FIRST CHILD: Counts Vowels
      int vow = 0;
      for(i = 0; str[i] != '\0'; i++){ // Fixed: '\0' instead of "\0"
         char ch = tolower((unsigned char)str[i]);
         if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u'){
            vow++;
         }
      }
      printf("P1 (Vowels count): %d\n", vow);
   }
   else{
      p3 = fork();
      if(p3 == 0){
         // SECOND CHILD: Counts Special Characters
         int sp = 0;
         for(i = 0; str[i] != '\0'; i++){ // Fixed: '!=' instead of '='
            if(!isalnum((unsigned char)str[i]) && !isspace((unsigned char)str[i])){
               sp++;
            }
         }
         printf("P3 (Special chars count): %d\n", sp);
      }
      else{
         // PARENT PROCESS: Waits for both child processes to completely finish
         wait(NULL); 
         wait(NULL); 
      }
   }
   return 0;
}
