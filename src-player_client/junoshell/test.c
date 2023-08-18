#include "shellserver.h"

#define BUFSIZE 256
#define INPUTLEN 32

char expecteds[1000];
char actuals[1000];

int main (int argc, char* argv[]) 
{

    char* query = (char*) calloc (1024, sizeof (char));
    strcpy (query, "SELECT ssh_prefix FROM devices where userid = \"");
    strcat (query, "3");
    strcat (query, "\";");

    MYSQL_RES* res_query = query_db (query); 

    char* res = parse_results(res_query);

    if (res)
    {
      printf ("%s\n", res);
      free (res);
    }

    query = (char*) calloc (1024, sizeof (char));
    strcpy (query, "SELECT ssh_prefix FROM devices where userid = \"");
    strcat (query, "3");
    strcat (query, "\";");

    res_query = query_db (query); 

    res = parse_results(res_query);

    if (res)
    {
      printf ("%s\n", res);
      free (res);
    }

    return 0;
}