#include "ers.h"

/********************************************************************************/
/* ADD EMPLOYEE PAGE */

void add_employee (void)
{
   char temp[100];
   FILE* file = NULL;
   
   system("cls");
   display_title();
   
   EMPLOYEE e;
   
   printf("ID (in number)              : "); getstr(temp, 100, stdin);
      e.id = strtol(temp, NULL, 10); 
      /* converts string into long integer (str-to-l)
       * temp = string to be converted
       * NULL = variable to put the rest of the string (after conversion)
       * 10 = base (10 for decimal, 16 for hexa, etc...
       * 
       * We used this way to prevent problems caused by scanf() and gets()
       */
   printf("Name            : "); getstr(e.name, 100, stdin);
   printf("Address         : "); getstr(e.addr, 100, stdin);
   printf("Phone No.       : "); getstr(e.phone, 100, stdin);
   printf("Department      : "); getstr(e.dept, 100, stdin);
   printf("Monthly Salary  : "); getstr(temp, 100, stdin);
      e.salary = strtof(temp, NULL); /* converts string into floating number (str-to-f) */
   printf("\n");
   
   file = fopen("records.data", "ab+");
   if (!file) {
      error("Couldn't open the data file!");
   }
   
   /* check to see if there's already an employee with that ID */
   
   EMPLOYEE e2;
   int same_id_found = 0;
   rewind(file);
   while (!feof(file)) {
      fread(&e2, sizeof(e2), 1, file);
      if (e.id == e2.id) {
         same_id_found = 1;
         break;
      }
   }
   
   if (same_id_found) {
      fclose(file);
      error("There's already a record with that ID!");
   }
   
   fseek(file, 0, SEEK_END);
   fwrite(&e, sizeof(e), 1, file);
   
   printf("Record added succesfully! \n");
   printf("\n");
   printf("Press [Enter] key to goto Main Menu \n");
   getchar();
   fclose(file);
   main_menu();
}

/********************************************************************************/
/* SEARCH EMPLOYEE PAGE */

void search_employee (void)
{
   char temp[100], choice, name[50];
   int id;
   system("cls");
   display_title();
   
   printf("  1.  Search by ID \n");
   printf("  2.  Search by Name \n");
   printf("\n");
   printf("Enter your choice (1 or 2): "); getstr(temp, 100, stdin);
   choice = temp[0];
   printf("\n");
   
   switch (choice) {
      case '1':
         printf("Enter ID: "); getstr(temp, 100, stdin);
         id = strtol(temp, NULL, 10);
         search_by_id(id); 
         break;
      case '2': 
         printf("Enter Name: "); getstr(name, 100, stdin);
         search_by_name(name); break;
      default:  search_employee(); break;
   }
   
   getchar();
   main_menu();
}

void search_by_id (int id)
{
   system("cls");
   display_title();

   FILE* file = fopen("records.data", "rb");
   if (!file) {
      error("Couldn't open the data file!");
   }
   
   EMPLOYEE e;
   int n = no_of_records(file, sizeof(e));
   
   int i, found = 0;
   for (i=0; i<n; i++) {
      fread(&e, sizeof(e), 1, file);
      if (e.id == id) {
         found = 1;
         break;
      }  
   }
   
   /* IF the ID doesn't match anyone */
   if (!found) {
      fclose(file);
      error("The given ID doesn't match any records!");
   }
   
   printf("   ID         : %d \n", e.id);
   printf("   Name       : %s \n", e.name);
   printf("   Address    : %s \n", e.addr);
   printf("   Phone no.  : %s \n", e.phone);
   printf("   Department : %s \n", e.dept);
   printf("   Salary     : %.2f per month \n", e.salary);
   printf("\n");
   printf("Press [Enter] to goto Main Menu\n");
   getchar();
   fclose(file);
   main_menu();
}


void search_by_name (char* name)
{
   system("cls");
   display_title();
  
   FILE* file = fopen("records.data", "rb");
   if (!file) {
      error("Couldn't open the data file!");
   }
   
   EMPLOYEE e;
   int n = no_of_records(file, sizeof(e));
   EMPLOYEE *matched_e = calloc(n, sizeof(EMPLOYEE));
   
   /* how many records match that name */
   int i, count = 0;
   for (i=0; i<n; i++) {
      fread(&e, sizeof(e), 1, file);
      if (strstr(strcase(e.name, 0), strcase(name, 0)) != NULL) {
         matched_e[count] = e;
         count++;
      }  
   }
   
   /* IF the name doesn't match anyone */
   if (count==0) {
      fclose(file);
      free(matched_e);
      error("The given name doesn't match any records!");
   }
   
   qsort(matched_e, count, sizeof(EMPLOYEE), emp_cmp);
   
   printf("%5s  %-20s %15s \n", "ID", "NAME", "SALARY");
   printf("--------------------------------------------- \n");
   for (i=0; i<count; i++) {
      printf("%5d  %-20s %15.2f \n", matched_e[i].id, matched_e[i].name, matched_e[i].salary );
   }
   printf("--------------------------------------------- \n");
   
   printf("\n");
   printf("Press [Enter] to goto Main Menu\n");
   getchar();
   free(matched_e);
   fclose(file);
   main_menu();
}


/********************************************************************************/
/* MODIFY EMPLOYEE PAGE */

void modify_employee (int id)
{
   char temp[100];
   system("cls");
   display_title();
   
   FILE* file = fopen("records.data", "r");
   
   if (!file) {
      error("Couldn't open the data file!");
   }
   
   int n = no_of_records(file, sizeof(EMPLOYEE));
   EMPLOYEE *e_all = calloc(n, sizeof(EMPLOYEE));
   
   fread(e_all, sizeof(EMPLOYEE), n, file);
   
   fclose(file);
   
   
   
   int found=0, index, i;
   for (i=0; i<n; i++) {
      if (e_all[i].id == id) {
         found = 1;
         index = i;
         break;
      }
   }
   
   if (!found) {
      free(e_all);
      error("The given ID doesn't match any records!");
   }
   
   printf("CURRENT DETAILS: \n");
   printf("   ID         : %d \n", e_all[index].id);
   printf("   Name       : %s \n", e_all[index].name);
   printf("   Address    : %s \n", e_all[index].addr);
   printf("   Phone      : %s \n", e_all[index].phone);
   printf("   Department : %s \n", e_all[index].dept);
   printf("   Salary     : %.2f \n", e_all[index].salary);
   printf("\n");
   
   printf("NEW DETAILS: \n");
   printf("   ID         : %d \n", e_all[index].id);
   printf("   Name       : "); getstr(e_all[index].name, 100, stdin);
   printf("   Address    : "); getstr(e_all[index].addr, 100, stdin);
   printf("   Phone      : "); getstr(e_all[index].phone, 100, stdin);
   printf("   Department : "); getstr(e_all[index].dept, 100, stdin);
   printf("   Salary     : "); e_all[index].salary = strtof(getstr(temp, 100, stdin), NULL);
   
   file = fopen("records.data", "wb");
   fwrite(e_all, sizeof(EMPLOYEE), n, file);
   free(e_all);
   fclose(file);
   
   printf("\n");
   printf("Record successfully updated! \n");
   printf("\n");
   printf("Press [Enter] to goto Main Menu \n");
   getchar();
   main_menu();
}

/********************************************************************************/
/* DELETE EMPLOYEE PAGE */

void delete_employee (int id)
{
   char temp[100];
   system("cls");
   display_title();
   
   printf("Are you sure you want to delete the record (y/n) ? "); getstr(temp, 100, stdin);
   printf("\n");
   
   char choice = temp[0];
   if (tolower(choice) != 'y') {
      printf("Deletion Aborted.\n\n");
      printf("Press [Enter] to goto Main Menu \n");
      getchar(); main_menu();
   }
   
   FILE* file = fopen("records.data", "rb");
   if (!file) error("Unable to open the data file!");
   int n = no_of_records(file, sizeof(EMPLOYEE));
   
   EMPLOYEE *emps = calloc(n, sizeof(EMPLOYEE));
   EMPLOYEE *emps_new = calloc(n-1, sizeof(EMPLOYEE));
   fread(emps, sizeof(EMPLOYEE), n, file);
   fclose(file);
   
   int i, found=0, count=0;
   for (i=0; i<n; i++) {
      if (emps[i].id == id) found=1;
      else emps_new[count++] = emps[i];
   }
   
   if (!found) {
      error("The given ID doesn't match any records.");
   }
   
   file = fopen("records.data", "wb");
   fwrite(emps_new, sizeof(EMPLOYEE), count, file);
   
   free(emps); free(emps_new);
   fclose(file);
   
   printf("Record successfully deleted.\n\n");
   printf("Press [Enter] to goto Main Menu\n");
   getchar(); main_menu();
}

/********************************************************************************/
/* VIEW EMPLOYEEs PAGE */

void view_employees (void)
{
   char temp[100];
   FILE* file = NULL;
   int n, i;
   
   system("cls");
   display_title();

   file = fopen("records.data", "rb");
   if (!file) {
      error("Couldn't open the data file!");
   }
   
   /* find out the no of records first */
   n = no_of_records(file, sizeof(EMPLOYEE));
   
   if (n<1) {
      fclose(file);
      error("There are no any records at the moment.");
   }
   
   EMPLOYEE* emps = calloc(n, sizeof(EMPLOYEE));
   
   fread(emps, sizeof(EMPLOYEE), n, file);
   
   qsort(emps, n, sizeof(EMPLOYEE), emp_cmp);
   
   printf("No of records: %d\n\n", n);
   
   /* display the table of records */
   printf("%5s  %-20s %15s \n", "ID", "NAME", "SALARY");
   printf("-------------------------------------------- \n");
   for (i=0; i<n; i++) {
      printf("%5d  %-20s %15.2f \n", emps[i].id, emps[i].name, emps[i].salary);
   }
   printf("-------------------------------------------- \n");
   
   free(emps);
   fclose(file);
   
   printf("\n");
   printf("Enter an ID to view detailed info (Press [Enter] to goto Main Menu): "); getstr(temp, 100, stdin);
   if (strlen(temp) < 1)
      main_menu();
   int id = strtol(temp, NULL, 10);
   search_by_id(id);
}
