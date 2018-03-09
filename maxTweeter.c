//
//  maxTweeter.c
//  maxTweeter
//
//  Created by Richard Li on 3/8/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 377
#define LINE_LENGTH 400

bool isValid(const char* filePath);
void printInvalid();


int main(int argc, const char * argv[]) {
  // no command line input
  if (argc != 2)
  {
    printf("No Input\n");
    return 0;
  }
  
  const char* filePath = argv[1];
  
  // invalid csv
  if(!isValid(filePath))
  {
    printf("Invalid Input Format\n");
    return 0;
  }
  
  // valid csv
  // TODO
  
  return 0;
}

bool isValid(const char* filePath)
{
  FILE *fp = fopen(filePath, "r");
  char line[LINE_LENGTH];
  
  // Error opening file
  if (!fp)
  {
    printInvalid();
    return false;
  }
  
  // read line
  fscanf(fp, "%s", line);
  
  // line too long
  if (strlen(line) > MAX_LINE_LENGTH)
  {
    printInvalid();
    return false;
  }
  
  // TODO
  // split by ',', if not every token starts and ends with ", invalid.
  
  fclose(fp);
  return true;
}

void printInvalid()
{
  printf("Invalid Input Format\n");
}
