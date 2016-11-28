#include "ers.h"

void display_title (void)
{
   printf("================================================================\n");
   printf("               M AND M COMPANY\n");
  // printf("Balkumari, Lalitpur \n");
   printf("\n");
   printf("             EMPLOYEE RECORD SYSTEM\n");
   printf("================================================================\n\n");
}

void welcome (void)
{
   printf("\n");
   printf("WELCOME TO THE EMPLOYEE RECORD SYSTEM \n");
   printf("\n");
   printf("Developed by: \n");
   printf("   Reema Prajapati \n");
   printf("   Bina Balami \n");
   printf("   Sandhya Gauro \n");
   printf("   Priyanka Gyawali \n");
   printf("\n");
}

void main_menu (void) {
   char temp[100];
   int id, choice;
   
   system("cls");
   display_title();
   
   printf("%s", 
      "\n"
      "        MAIN MENU \n"
      "----------------------------- \n"
      "   1.  View all employees \n"
      "   2.  Add employee \n"
      "   3.  Search employee \n"
      "   4.  Modify employee \n"
      "   5.  Delete employee \n"
      "   6.  Exit \n"
      "\n"
      "Enter your choice: ");
   
   getstr(temp, 100, stdin);
   choice = strtol(temp, NULL, 10);
   printf("\n");
   
   switch (choice) {
      case 1: view_employees(); break;
      case 2: add_employee(); break;
      case 3: search_employee(); break;
      case 4: 
         printf("Enter ID to modify: "); 
         id = strtol(getstr(temp, 100, stdin), NULL, 10);
         modify_employee(id); 
         break;
      case 5: 
         printf("Enter ID to delete: "); 
         id = strtol(getstr(temp, 100, stdin), NULL, 10);
         delete_employee(id);
         break;
      case 6: exit(0); break;
      default:  main_menu();
   }
}

void error(const char* error_msg) {
   system("cls");
   display_title();
   
   printf("ERROR: %s \n", error_msg);
   printf("\n");
   printf("Press [Enter] to goto Main Menu\n");
   getchar();
   main_menu();
}
