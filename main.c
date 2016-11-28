#include "ers.h"

int main (void) 
{   
   system("cls");
   display_title();
   welcome();

   printf("\nPress [Enter] key to enter the program.\n");
   getchar();

   main_menu();
   
   return 0;
}
