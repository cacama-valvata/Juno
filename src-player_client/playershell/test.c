#include "shellserver.h"

#define BUFSIZE 256
#define INPUTLEN 32

char expecteds[1000];
char actuals[1000];

void run_test(char* name, int (*test_func)(void)) 
{
  printf("Running test: %s", name);
  if (test_func() == 0) 
  {
    printf("  PASS\n");
  } 
  else 
  {
    printf("  FAIL\n");
    printf("%s", expecteds);
    printf("%s", actuals);
  }
  printf("=============================================================\n");
}

int test_example_1(void)
 {
  int expected = 42;
  int actual = 42;

  snprintf(expecteds, sizeof(expecteds), "Expected: %d\n", expected);
  snprintf(actuals, sizeof(actuals), "Actual: %d\n", actual);

  return expected == actual ? 0 : 1;
}

int test_read_credentials(void)
{
    int expected = 0;
    char username[INPUTLEN], password[INPUTLEN];
    int actual = read_credentials(username,password);

  if(actual == 0)
  {
    snprintf(expecteds, sizeof(expecteds), "Expected: root root\n");
    snprintf(actuals, sizeof(actuals), "Actual: %s, %s\n", username, password);
  }
  else
  {
    snprintf(expecteds, sizeof(expecteds), "Expected: 0 (Program Succesfully Opened File)\n");
    snprintf(actuals, sizeof(actuals), "Actual: %d\n", actual);
  }

    return expected == actual && strlen(username) > 0 && strlen(password) > 0 ? 0 : 1;
}

int test_append_p(void)
{
    char targ[10] = "HelloWorld";

    char* eval = append_p(targ);
    
    snprintf(expecteds, sizeof(expecteds), "Expected: -pHelloWorld\n");
    snprintf(actuals, sizeof(actuals), "Actual: %s\n", eval);

    return strcmp(eval,"-pHelloWorld") == 0 ? 0 : 1;
}

int test_execdb(void)
{
    char pubkey_decoded[451] = "1\0";
    char query[1000];
    char buf[BUFSIZE];
    char username[INPUTLEN], password[INPUTLEN];
    memset(username,0,INPUTLEN);

    if(read_credentials(username, password) == 1)
        return 1;
    
    //append password format
    char* passarg = append_p(password);

    memset(query,0,1000);

    strcat(query,"Use Juno; SELECT username FROM users WHERE userid = '");
    strcat(query, pubkey_decoded);
    strcat(query, "';\0");

    //printf("\nInput: %s\n", query);
    //fflush(stdout);

    freopen("/dev/null", "w", stdout);

    //strcpy(username, "root");

    execdb(username, passarg, query, buf);

    freopen("/dev/tty", "w", stdout);

    snprintf(expecteds, sizeof(expecteds), "Expected: hybrid-swansea\n");
    snprintf(actuals, sizeof(actuals), "Actual: %s\n", buf);


    return strlen(buf) >= 14 ? 0 : 1;
}

int test_heartbeat(void)
{

  char key[30] = "1";

    char username[INPUTLEN], password[INPUTLEN];


  if(read_credentials(username, password) == 1)
      return 1;
    
  //append password format
  char* passarg = append_p(password);

  freopen("/dev/null", "w", stdout);

  heartbeat(key,username,passarg);

  freopen("/dev/tty", "w", stdout);

  snprintf(expecteds, sizeof(expecteds), "Expected: tbd\n");
  snprintf(actuals, sizeof(actuals), "Actual: tbd\n");


  return strlen(key) > 31 ? 0 : 1;
}

int test_retrieve_conf(void)
{
    char pubkey_decoded[451] = "1\0";
    char username[INPUTLEN], password[INPUTLEN];
    memset(username,0,INPUTLEN);

    if(read_credentials(username, password) == 1)
        return 1;

    char* passarg = append_p(password);

    freopen("/dev/null", "w", stdout);

    retrieve_conf(pubkey_decoded, username, passarg, "1");

    
    freopen("/dev/tty", "w", stdout);


    //wgcfg
    snprintf(expecteds, sizeof(expecteds), "Expected: %s + rest of cfg\n",pubkey_decoded);
    snprintf(actuals, sizeof(actuals), "Actual: %s\n", pubkey_decoded);


    return strlen(pubkey_decoded) > 1 ? 0 : 1;
}



int main(void) 
{
  printf("=============================================================\n");
  run_test("test_example_1", test_example_1);
  run_test("test_example_1", test_example_1);
  run_test("test_read_credentials",test_read_credentials);
  run_test("test_append_p",test_append_p);
  run_test("test_execdb",test_execdb);
  run_test("test_heartbeat",test_heartbeat);
  run_test("test_retrieve_conf",test_retrieve_conf);
  return 0;
}