#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "embedded-sql.h"

int main(int argc, char **argv) 
{
  int status = db_connect("intheshadow33893");
  if (status) 
  {
    fprintf(stderr, "Error connecting to database\r\n");
    return 1;
  }

  printf("Task A:\r\n");
  int digit;
  char str[128];
  printf("Input insurance fee: ");
  scanf("%d", &digit);
  printf("Input day: ");
  scanf("%s", str);

  status = task_a(digit, str);
  if (status) 
  {
		fprintf(stderr, "Error task_a\r\n");
		return 1;
  }

  printf("\r\n");
  
  printf("Task B:\r\n");
  status = task_b();
  if (status) 
  {
		fprintf(stderr, "Error task_b\r\n");
		return 1;
  }

  printf("\r\n");

  printf("Task C:\r\n");
  printf("Input value: ");
  scanf("%d", &digit);
  status = task_c(digit);
  if (status) 
  {
		fprintf(stderr, "Error task_c\r\n");
		return 1;
  }

  printf("\r\n");

  printf("Task D:\r\n");
  printf("Input value: ");
  scanf("%d", &digit);
  status = task_d(digit);
  if (status)
  {
		fprintf(stderr, "Error task_d\r\n");
		return 1;
  }
}