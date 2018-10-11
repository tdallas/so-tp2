#include <constantPrints.h>
#include <exitProcess.h>

static const char weekDays[7][10] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
static const char months[12][11] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

void printTime()
{
    int times[7];
    getAllTimes(times);
    printf("Hora: %d:%d:%d.\n", times[2], times[1], times[0]);
}

void printDate(){
    int times[7];
    getAllTimes(times);
    printf("Fecha: %s %d de %s de %d.\n", weekDays[times[3] - 1], times[4], months[times[5]-1], times[6]);
}

void printTimeUTC(){
    printf("Zona horaria: UTC %d.\n", getTimeUTC());
}

void help()
{
    printf("                            \n");
    printf("                           Welcome to Titanium OS!\n");
    printf("                            \n");
    printf("                                For more information, write info\n");
    printf("                                To clean the console, write clear\n");
    printf("             If you want to display time on console, write displayTimeConsole\n");
    printf("             messageTest :: sends a message to multiple processes\n");
    printf("             prodcons if you like to see our resolution to prodcons problem\n");
    printf("             printPids (with cammelCase) if you like to print pids of processes\n");
    printf("              Write exceptionZero for trying our divZero exception catch\n");
    printf("              Write exceptionOpCode for trying our opCode exception catch\n");
    printf("                           If you want to exit, write exit\n");
    printf("                            \n");
    exitProcess();
}

void info()
{
    printf("        This is a rudimentary OS, created by 2 ITBA students, passionate for what they do\n");
    printf("                                            and what they study. \n");
    printf("        In this OS, you will be able to do: \n ");
    printf("                - See what time is it. \n");
    printf("                - See what time is it on a digital watch. \n");
    printf("                - Play a game call BlobWars -> It is a strategy game where you can play \n");
    printf("                     against a IA or against a friend, where you got a squared matrix\n");
    printf("                     and the mission is to \"convert\" as much pieces of the enemy you can.\n");
    printf("                - You can test the exceptions\n");
    printf("                - Eventually, you can inform us of any bug you'll find and we'll be \n");
    printf("                      happy to solve them (hope they're few). You can send an email to : \n");
    printf("                              tdorado@itba.edu.ar or tdallas@itba.edu.ar\n");
    printf("\n                                   THANKS FOR USING OUR OS! :) \n\n");
    exitProcess();
}

void displayTime()
{
    printf("Epoch Time: %d.\n", time(NULL));
    printTime();
    printDate();
   printTimeUTC();
    exitProcess();
}
