#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>

bool isBackground = false;

void func(){
 
 FILE *f;
 f  = fopen ("lab1.log", "a");
 if(f != NULL){
 fprintf(f, "Child process was terminated\n"); 
 }

}

 
void getArguments(char **arguments){

 int n=0;     //number of arguments
 char *commandLine;
 size_t size = 10;                                     /*initial size of char array*/
 commandLine = (char *) malloc (size);
 getline(&commandLine,&size,stdin);
 char *token = strtok(commandLine, " \n\t");
 
   while(token!=NULL){    //remove all spaces and put the tokens to array of strings
        arguments[n]=token;      
        token = strtok(NULL," \n\t");
        n++;
   }
   arguments[n] = NULL;
   if(strcmp(arguments[n-1],"&")==0){  //check if there is an & , if so then delete it and make isBackground = true
   arguments[n-1] = NULL;
   isBackground = true;
   }
   else{
    isBackground = false;   
   }
}

int main() {
 
 signal(SIGCHLD,func);

 while(1){
 
 char *arguments[100];    //array of arguments

 printf("Shell > ");
 getArguments(arguments);
 
 if(strcmp(arguments[0],"exit")==0){
   exit(EXIT_SUCCESS);
 }
 
 int status;
 pid_t pid = fork();
 
 if(pid<0){
 printf("fork failed unable to create a child process.\n");
 exit(EXIT_SUCCESS);
 }
 
 else if(pid ==0){    //child process
 if (execvp(arguments[0],arguments) < 0) {     /* execute the command  */
     printf("No such command\n");
 }
 exit(EXIT_SUCCESS);
 }
 
 else{    //parent process
 
 
 if(!isBackground){
 waitpid(pid,&status,0);
 
 }
 }
 }
}
