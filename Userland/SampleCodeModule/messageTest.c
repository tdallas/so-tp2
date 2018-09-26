#include <exitProcess.h>
#include <stdio.h>
#include <messages.h>
#include <processExec.h>
#include <shell.h>

void newProcess(int argc, char**argv);

void messageTest(int argc, char**argv){
  int processes = 4;

  int p1 = getPid();
  int * parameter = malloc(sizeof(int));
  *parameter = p1;

  int processesPids[processes];
  for(int i=0; i< processes; i++){
    processesPids[i] = execProcess(newProcess, 1, &parameter, (char)i, 0);
  }


  char *msg = "holaaa\n";

  printf("Sending: %s\n", msg);
  for(int i=0; i< processes; i++){

    send(processesPids[i], msg, strlenUserland(msg));
  }

  exitProcess();
}

void newProcess(int argc, char**argv){
  int **p1_pointer = ((void**)argv);
  int p1 = **p1_pointer;
  char msg[BUFFERSIZE+1];
  int index=0;
  do {
    receive(p1, &msg[index], 1);
  } while(msg[index] != '\n' && index++ < BUFFERSIZE);


  msg[index]=0;

  printf("Proceso %d: %s\n", getPid(), msg);
  exitProcess();
}
