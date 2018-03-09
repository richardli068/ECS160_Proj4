//
//  maxTweeter.c
//  maxTweeter
//
//  Created by Richard Li on 3/8/18.
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isValid(const char* filePath);

int main(int argc, const char * argv[]) {
  // no command line input
  if (argc != 3)
  {
    printf("No Input\n");
    return 0;
  }
  
  const char* filePath = argv[2];
  
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
  return false;
}
