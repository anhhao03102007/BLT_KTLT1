#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <MODE_3.h>
#include <FUNCTION.h>

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define MAGENTA "\033[35m"
#define BG_BLUE "\033[44m"

void loadingAnimation() {
    system("cls");

    printf(CYAN "=============================================================\n" RESET);
    printf(CYAN "|" BOLD YELLOW "      " RESET CYAN "|\n" RESET);
    printf(CYAN "=============================================================\n" RESET);
    Sleep(600);

    printf(WHITE "\n  Dang khoi dong he thong");
    for (int i = 0; i < 3; i++) {
        Sleep(300);
        printf(YELLOW "." RESET);
    }
    printf("\n\n" RESET);

    int totalSteps = 20;
    printf("  " CYAN "Loading: [" RESET);

    for (int i = 0; i < totalSteps; i++) {
       
        if (i < 7)
            printf(RED "#" RESET);        
        else if (i < 14)
            printf(YELLOW "#" RESET);     
        else
            printf(GREEN "#" RESET);      

        printf(WHITE "] %3d%%" RESET, (i + 1) * 5);

        printf("\b\b\b\b\b\b"); 

     
        fflush(stdout); 
        Sleep(100);
    }

    printf(GREEN "#" CYAN "] " GREEN BOLD "100%%" RESET "\n\n");
    Sleep(300);

    printf(CYAN "  =============================================================\n" RESET);
    printf(GREEN BOLD "                     >> Completed ! <<\n" RESET);
    printf(CYAN "  =============================================================\n\n" RESET);

    printf(YELLOW "  Nhan " BOLD "[Enter]" RESET YELLOW " de tiep tuc..." RESET);
    _getch();
    system("cls");
}
int main(){
   loadingAnimation();
   playGame();
   return 0;
}