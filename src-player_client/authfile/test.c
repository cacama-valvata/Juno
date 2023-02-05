#include "smallssh_ssh_auth.h"

#define BUFSIZE 256
#define INPUTLEN 32

void run_test(char* name, int (*test_func)(void)) 
{
  printf("Running test: %s\n", name);
  if (test_func() == 0) 
  {
    printf("  PASS\n");
  } 
  else 
  {
    printf("  FAIL\n");
  }
}

int test_example_1(void)
 {
  int expected = 42;
  int actual = 42;
  return expected == actual ? 0 : 1;
}

int test_read_credentials(void)
{
    int expected = 0;
    char username[INPUTLEN], password[INPUTLEN];
    int actual = read_credentials(username,password);

    return expected == actual && strlen(username) > 0 && strlen(password) > 0 ? 0 : 1;
}

int test_append_p(void)
{
    char targ[10] = "HelloWorld";

    char* eval = append_p(targ);

    return strcmp(eval,"-pHelloWorld") == 0 ? 0 : 1;
}

int test_execdb(void)
{
    char pubkey_decoded[451] = "x";
    char query[1000];
    char buf[BUFSIZE];
    char username[INPUTLEN], password[INPUTLEN];

    if(read_credentials(username, password) == 1)
        return 1;
    
    //append password format
    char* passarg = append_p(password);

    strcat(query,"SELECT COUNT(*), username FROM users WHERE pubkey = '");
    strcat(query, pubkey_decoded);
    strcat(query, "';");

    execdb(username, passarg, query, buf);


    return strlen(buf) > 1 ? 0 : 1;
}

int main(void) 
{
  run_test("test_example_1", test_example_1);
  run_test("test_read_credentials",test_read_credentials);
  run_test("test_append_p",test_append_p);
  run_test("test_execdb",test_execdb);
  
  return 0;
}