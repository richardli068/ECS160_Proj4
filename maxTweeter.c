//
//  maxTweeter.c
//  maxTweeter
//
//  Created by Richard Li on 3/8/18.
//

#include <stdio.h>
#include <stdlib.h> // for EXIT_SUCCESS
#include <stdbool.h>
#include <string.h>

// include \n, exclude \0
#define MAX_LINE_LENGTH 375
#define LINE_LENGTH 400
#define MAX_LINE_COUNT 20000
#define MAX_TWEETER_COUNT 6228

bool isValid(const char* filePath);

// helpers
bool readLine(FILE *fp, char* line);
int splitLine(char* line,
              char lineList[(MAX_LINE_LENGTH - 1) / 2 + 1][MAX_LINE_LENGTH]);
int processHeader(char header[(MAX_LINE_LENGTH - 1) / 2 + 1][MAX_LINE_LENGTH]
                  , int numField);

void printInvalidAndExit(void);
// validation checkers



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
    printInvalidAndExit();
  }
  
  // valid csv
  // TODO
  
  return 0;
}

bool
isValid(const char* filePath)
{
  // invalid condition:
  // no header -> no name inplies no header.            DONE
  // only have header
  // line too long                                      DONE in readLine
  // more than 20,000 lins
  // more than 6228 tweeters
  // no additional comma inside tweets                  Assumpiton
  
  FILE *fp = fopen(filePath, "r");
  char line[LINE_LENGTH];
  short lineCount = 0;
  
  // Error opening file
  if (!fp)
  {
    printf("Error opening file\n");
    return false;
  }
  
  // Process header line
  //----------------------------------------------------------------------------
  // read first line
  // check if line is too long and if file is empty
  if(!readLine(fp, line)) return false;
  lineCount++;
  
  // split line
  // line guaranteed to be <= MAX_LINE_LENGTH
  // correctly handles \0
  // [(MAX_LINE_LENGTH - 1) / 2 + 1][]: in case all fields have length 1
  // [][MAX_LINE_LENGTH]: in case only 1 field
  char lineList[(MAX_LINE_LENGTH - 1) / 2 + 1][MAX_LINE_LENGTH];
  
  // numFiled: number of fields in the header line
  int numField = splitLine(line, lineList);
  int nameIndex = processHeader(lineList, numField);
  // check if no name or multiple name's are present
  if (nameIndex == -1) return false;
  //----------------------------------------------------------------------------
  // Finish processing header line
  
  // Process body
  //----------------------------------------------------------------------------
  while(readLine(fp, line))
  {
    // do something here
    lineCount++;
  }
  
  // check if only header is present
  if (lineCount == 1) return false;
  
  
  //----------------------------------------------------------------------------
  // Finish processing body
  
  fclose(fp);
  return true;
}


/*******************************************************************************
 ********************              Helpers              ************************
 ******************************************************************************/


// return true on valid line read
// return false on invalid line read
bool
readLine(FILE *fp, char* line)
{
  if (!fgets(line, LINE_LENGTH, fp))
  {
    // EOF or empty file
    return false;
  }
  else
  {
    // successfully read. Check line length
    if (strlen(line) > MAX_LINE_LENGTH) return false;
  }
  return true;
}


// split a line by ','
// return number of tokens appended
int
splitLine(char* line,
          char lineList[(MAX_LINE_LENGTH - 1) / 2 + 1][MAX_LINE_LENGTH])
{
  char* token;
  
  token = strtok(line, ",");
  
  int count;
  for (count = 0; token; count++)
  {
    memcpy(lineList[count], token, MAX_LINE_LENGTH);
    token = strtok(NULL, ",");
  }
  return count;
}


// return index of the name field if valid name field is found
// return -1 if none or multiple found
int
processHeader(char header[(MAX_LINE_LENGTH - 1) / 2 + 1][MAX_LINE_LENGTH]
              , int numField)
{
  const char* name1 = "name";
  const char* name2 = "\"name\"";
  int nameField = -1;
  
  for (int i = 0; i < numField; i++)
  {
    // delete
    // printf("%s\n", header[i]);
    if (strcmp(header[i], name1) == 0 || strcmp(header[i], name2) == 0)
    {
      if (nameField != -1)
      {
        // multiple name field detected
        nameField = -1;
        break;
      }
      nameField = i;
    }
  }
  return nameField;
}


void
printInvalidAndExit(void)
{
  printf("Invalid Input Format\n");
  exit(EXIT_SUCCESS);
}

/*******************************************************************************
 ***************              Validation Checkers              ******************
 *******************************************************************************/


