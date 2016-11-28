#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct _employee {
   int id;
   char name[50];
   char addr[50];
   char phone[15];
   char dept[50];
   float salary;
};

typedef struct _employee EMPLOYEE;


/* function prototypes */

/* msg.c */
void display_title (void);
void welcome (void);
void main_menu (void);
void error (const char* error_msg);

/* util.c */
char* getstr (char* string, int size, FILE* file_ptr);
int no_of_records (FILE* file, int element_size);
char* strcase (char* string, int flag);
int emp_cmp (const void *e1, const void *e2);

/* database.c */
void add_employee (void);
void search_employee (void);
void search_by_id (int id);
void search_by_name (char* name);
void modify_employee (int id);
void delete_employee (int id);
void view_employees (void);
