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

// struct
typedef struct map
{
  char name[MAX_LINE_LENGTH];
  int count;
} Map;
bool isMapEmpty(const Map m);
int hasKey(const Map maps[MAX_TWEETER_COUNT]
           , const char name[MAX_LINE_LENGTH], const int size);
void printMap(const Map m);


bool isValid(const char* filePath, Map maps[MAX_TWEETER_COUNT], int* size);


// helpers
bool readLine(FILE *fp, char* line);
int splitLine(char* line,
              char lineList[(MAX_LINE_LENGTH - 1) / 2 + 1][MAX_LINE_LENGTH]);
int processHeader(const char header[(MAX_LINE_LENGTH - 1) / 2 + 1][MAX_LINE_LENGTH]
                  , const int numField);
bool processBodyLine(char line[LINE_LENGTH], const int totalField
                     , const int nameField, char name[MAX_LINE_LENGTH]);
void printInvalidAndExit(void);


int main(int argc, const char * argv[]) {
  // no command line input
  if (argc != 2)
  {
    printf("No Input\n");
    return 0;
  }
  
  const char* filePath = argv[1];
  
  Map maps[MAX_TWEETER_COUNT];
  int* size = (int*) malloc(sizeof(int));
  *size = 0;
  
  // invalid csv
  if(!isValid(filePath, maps, size))
  {
    printInvalidAndExit();
  }
  
  // valid csv
  // TODO
  for (int i = 0; i < *size; i++)
  {
    printMap(maps[i]);
  }
  return 0;
}



/*******************************************************************************
 *********************              Struct              ************************
 ******************************************************************************/

bool isMapEmpty(const Map m)
{
  if (m.count == 0) return true;
  else return false;
}


// size: the size of the maps. greatly reduce computation complexity

// returns index if key found in maps
// return -1 if not found
int hasKey(const Map maps[MAX_TWEETER_COUNT]
           , const char name[MAX_LINE_LENGTH], const int size)
{
  for (int i = 0; i < size; i++)
  {
    if (strcmp(maps[i].name, name) == 0) return i;
  }
  return -1;
}


void printMap(const Map m)
{
  printf("%s:%d\n", m.name, m.count);
}


bool
isValid(const char* filePath, Map maps[MAX_TWEETER_COUNT], int* size)
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
//    printf("%s\n", line);
    char name[MAX_LINE_LENGTH];
    if (!processBodyLine(line, numField, nameIndex, name))
      printInvalidAndExit();
    
    int insertIndex;
    if ((insertIndex = hasKey(maps, name, *size)) == -1)
    {
      // not found key
      strcpy(maps[*size].name, name);
      maps[*size].count = 1;
      (*size)++;
    }
    else // found
    {
      maps[insertIndex].count++;
    }
    lineCount++;
  }
  
  // check if only header is present
  if (lineCount == 1) return false;
  if (lineCount > MAX_LINE_COUNT) return false;
  
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
processHeader(const char header[(MAX_LINE_LENGTH - 1) / 2 + 1][MAX_LINE_LENGTH]
              , const int numField)
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


// line: a line in body
// totalField: total number of fields as seen in the header
// nameField: index of the nameField
// name: the string name is stored in
// return true if name is successfully copied
// return false if error occurs
bool
processBodyLine(char line[LINE_LENGTH], const int totalField
                , const int nameField, char name[MAX_LINE_LENGTH])
{
  char lineList[(MAX_LINE_LENGTH - 1) / 2 + 1][MAX_LINE_LENGTH];
  int numFields = splitLine(line, lineList);
  
  // check if current line has all fields defined by header
  if (numFields != totalField) return false;
  
  strcpy(name, lineList[nameField]);
  return true;
}


void
printInvalidAndExit(void)
{
  printf("Invalid Input Format\n");
  exit(EXIT_SUCCESS);
}
