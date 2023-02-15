#include "smallssh_ssh_auth.h"

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
    char pubkey_decoded[1000] = "AAAAB3NzaC1yc2EAAAADAQABAAABgQDV6pvDAafe6Emu305YWzxuEWgWq6ypPpMftmHVtu5al9+VzLSFFph2J5hqUL06M8W7+5b1a+UXxdns7hUIHYEh2WPxJkPf4xPXyEG3bXeoTXyt4YZ3i+PagmvcYLg4pwUJl2y5A1/ipamdZTqoPNtycIDt62+pPEjBUL7QnE3YPIP6Fzh76SQcPHS46t7MDzSahBkAvaTMErCfYfyFgIrWgcWbVY+pM+JPyfNpAQs/XkYxXtctzieasPqkOlLc/Y2XKeB6SiXZiiOuu8zHTNfuAd1OO1yZ0Bp0+Bph/ZlsLmrPVsEzgw0yzOn+Mz9zMng1flQHQqxA2kLzI8lk8/HbIf9byKzIJebRdsOBJEnY+/xyEO8wxx5bgs3MshtDe9lNyKraaEgS/+c87Q4p1v6tUZdXSRPTSjyeczYxRVAMFU0NVo+WZvnG0KIHx5wMUX46tBiQFlW+gdhs1EC1wdkcC8K9zxZuK9685duhRbZp0DMgWsSC6wJi8mAUhYAT8Es=";
    char query[1000];
    char buf[BUFSIZE];
    char username[INPUTLEN], password[INPUTLEN];
    memset(username,0,INPUTLEN);

    if(read_credentials(username, password) == 1)
        return 1;
    
    //append password format
    char* passarg = append_p(password);

    memset(query,0,1000);

    strcat(query,"Use Juno; SELECT count(*) as num_users FROM (SELECT userid from devices where ssh_pubkey = '");
    strcat(query, pubkey_decoded);
    strcat(query, "') as useridlist;\0");

    //printf("\nInput: %s\n", query);
    //fflush(stdout);

    freopen("/dev/null", "w", stdout);

    //strcpy(username, "root");

    execdb(username, passarg, query, buf);

    freopen("/dev/tty", "w", stdout);

    snprintf(expecteds, sizeof(expecteds), "Expected: hybrid-swansea\n");
    snprintf(actuals, sizeof(actuals), "Actual: %s\n", buf);


    return strlen(buf) >= 2 ? 0 : 1;
}

int main(void) 
{
  printf("=============================================================\n");
  run_test("test_example_1", test_example_1);
  run_test("test_read_credentials",test_read_credentials);
  run_test("test_append_p",test_append_p);
  run_test("test_execdb",test_execdb);
  
  return 0;
}