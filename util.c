#include "ers.h"

/* This function is a modified version of fgets()
 * It is required because scanf() and gets() don't work together well!
 * Plus, the fgets() has a slight problem
 */
char* getstr(char* string, int size, FILE* file_ptr)
{
   int len;
   
   fgets(string, size, file_ptr);
   len = strlen(string);
   
   /* fgets() puts the Enter character ('\n') as well into the string
    * which is not what we want. So we'll change that '\n' into '\0'
    */
   
   if (len>0 && string[len-1]=='\n')
      string[len-1] = '\0';
   
   /* we'll ask the user until we get some text */
   
   //if (strlen(string) < 1)
    //  getstr(string, size, file_ptr);
   
   return string;
}

/* This function returns the no of records of size 'element_size' in a file */
int no_of_records(FILE* file, int element_size) {
   rewind(file);
   int count = 0;
   char c;
   while (!feof(file)) {
      fread(&c, 1, 1, file);
      count++;
   }
   rewind(file);
   return count/element_size;
}


/* A function to convert whole string into uppercase or lowercase */
char* strcase(char* string, int flag) {
   /* if flag=1, into uppercase
    * if flag=0, into lowercase
    */
    
    int len = strlen(string);
    
    char* newstring = calloc(len+1, sizeof(*newstring));
    
    int i;
    for (i=0; i<=len; i++) {
       if (flag) 
         newstring[i] = toupper(string[i]);
       else
         newstring[i] = tolower(string[i]);
    }
    
    return newstring;
}


/* a function to compare two employees (to be used with qsort() function) */
int emp_cmp (const void *e1, const void *e2)
{
   if (((EMPLOYEE*)e1)->id < ((EMPLOYEE*)e2)->id) return -1;
   else if (((EMPLOYEE*)e1)->id == ((EMPLOYEE*)e2)->id) return 0;
   else return 1;
}
