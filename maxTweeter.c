//
//  maxTweeter.c
//  maxTweeter
//
//

#include <stdio.h>
#include <stdlib.h> // for EXIT_SUCCESS
#include <stdbool.h>
#include <string.h>

// include \n, exclude \0
#define MAX_LINE_LENGTH 376
#define LINE_LENGTH 400
#define MAX_LINE_COUNT 20000
#define MAX_TWEETER_COUNT 6228
#define TWEETER_COUNT 6250

// struct
typedef struct map
{
  char name[LINE_LENGTH];
  int count;
} Map;
bool isMapEmpty(const Map m);
int hasKey(const Map maps[TWEETER_COUNT]
           , const char name[LINE_LENGTH], const int size);
void printMap(const Map m);


short isValid(const char* filePath, Map maps[TWEETER_COUNT], int* size);


// helpers
short readLine(FILE *fp, char* line);
int splitLine(char* line,
              char lineList[(LINE_LENGTH - 1) / 2 + 1][LINE_LENGTH]);
int processHeader(char header[(LINE_LENGTH - 1) / 2 + 1][LINE_LENGTH]
                  , const int numField);
bool processBodyLine(char line[LINE_LENGTH], const int totalField
                     , const int nameField, char name[LINE_LENGTH]);
void printInvalidAndExit(void);
void printError(short error);
int compare(const void *s1, const void *s2);


int main(int argc, const char * argv[]) {
  const char option[10] = "-r";
  
  // no command line input
  // or only option
  if (argc < 2 || (argc == 2 && strcmp(argv[1], option) == 0))
  {
    printf("Usage: ./maxTweeter.out [-option] <file>\n");
    exit(EXIT_SUCCESS);
  }
  
  const char* filePath;
  bool printInvalidReason = false;
  
  if (argc > 2)
  {
    if (strcmp(option, argv[1]) == 0) printInvalidReason = true;
    // if more arguments are passed in, ignore all after the 2nd one
    filePath = argv[2];
  }
  else // argc must be 2
  {
    filePath = argv[1];
  }
  
  // error code:
  // -1: No error
  //  1: Error opening file
  //  2: No header
  //  3: Line too long
  //  4: No name or multiple name fields
  //  5: Body line missing field(s)
  //  6: Too many tweeters
  //  7: File too large
  //  8: No tweets
  short error = -1;
  
  Map maps[TWEETER_COUNT];
  int* size = (int*) malloc(sizeof(int));
  *size = 0;
  
  // invalid csv
  if((error = isValid(filePath, maps, size)) != -1)
  {
    if (printInvalidReason) printError(error);
    printInvalidAndExit();
  }
  
  // valid csv
  qsort(maps, *size, sizeof(Map), compare);
  if (*size < 10)
  {
    for (int i = 0; i < (*size); i++)
    {
      printMap(maps[i]);
    }
  }
  else
  {
    for (int i = 0; i < 10; i++)
    {
      printMap(maps[i]);
    }
  }
  return 0;
}



/*******************************************************************************
 *********************              Struct              ************************
 ******************************************************************************/

bool
isMapEmpty(const Map m)
{
  if (m.count == 0) return true;
  else return false;
}


// size: the size of the maps. greatly reduce computation complexity

// returns index if key found in maps
// return -1 if not found
int
hasKey(const Map maps[TWEETER_COUNT]
       , const char name[LINE_LENGTH], const int size)
{
  for (int i = 0; i < size; i++)
  {
    if (strcmp(maps[i].name, name) == 0) return i;
  }
  return -1;
}


void
printMap(const Map m)
{
  printf("%s:%d\n", m.name, m.count);
}




short
isValid(const char* filePath, Map maps[TWEETER_COUNT], int* size)
{
  FILE *fp = fopen(filePath, "r");
  char line[LINE_LENGTH];
  short lineCount = 0;
  
  // Error opening file
  if (!fp) return 1;
  
  // Process header line
  //----------------------------------------------------------------------------
  // read first line
  // check if line is too long and if file is empty
  int readLineCode = readLine(fp, line);
  if (readLineCode == 1) return 2;
  else if (readLineCode == 2) return 3;
  lineCount++;
  
  // split line
  // line guaranteed to be <= LINE_LENGTH
  // correctly handles \0
  // [(LINE_LENGTH - 1) / 2 + 1][]: in case all fields have length 1
  // [][LINE_LENGTH]: in case only 1 field
  char lineList[(LINE_LENGTH - 1) / 2 + 1][LINE_LENGTH];
  
  // numFiled: number of fields in the header line
  int numField = splitLine(line, lineList);
  int nameIndex = processHeader(lineList, numField);
  // check if no name or multiple name's are present
  if (nameIndex == -1) return 4;
  //----------------------------------------------------------------------------
  // Finish processing header line
  
  // Process body
  //----------------------------------------------------------------------------
  int error;
  while((error = readLine(fp, line)) == 0)
  {
    //    printf("%s\n", line);
    char name[LINE_LENGTH];
    if (!processBodyLine(line, numField, nameIndex, name)) return 5;
    
    int insertIndex;
    
    if ((insertIndex = hasKey(maps, name, *size)) == -1)
    {
      // not found key
      strcpy(maps[*size].name, name);
      maps[*size].count = 1;
      (*size)++;
      
      // check if tweeter count exceeds the max amount
      if ((*size) > MAX_TWEETER_COUNT) return 6;
    }
    else // found
    {
      maps[insertIndex].count++;
    }
    lineCount++;
    
    // check if file is too large
    if (lineCount > MAX_LINE_COUNT) return 7;
  }
  
  // check is line is too long
  if (error == 2) return 3;
  // check if only header is present
  if (lineCount == 1) return 8;
  //----------------------------------------------------------------------------
  // Finish processing body
  
  fclose(fp);
  return -1;
}


/*******************************************************************************
 ********************              Helpers              ************************
 ******************************************************************************/

// return 0 on valid line read
// return 1 on EOF
// return 2 on line too long
short
readLine(FILE *fp, char* line)
{
  if (!fgets(line, LINE_LENGTH, fp))
  {
    // EOF or empty file
    return 1;
  }
  else
  {
    // successfully read. Check line length
    if (strlen(line) > MAX_LINE_LENGTH) return 2;
  }
  return 0;
}


// split a line by ','
// return number of tokens appended
int
splitLine(char* line,
          char lineList[(LINE_LENGTH - 1) / 2 + 1][LINE_LENGTH])
{
  char* token;
  
  token = strtok(line, ",");
  
  int count;
  for (count = 0; token; count++)
  {
    memcpy(lineList[count], token, LINE_LENGTH);
    token = strtok(NULL, ",");
  }
  return count;
}


// return index of the name field if valid name field is found
// return -1 if none or multiple found
int
processHeader(char header[(LINE_LENGTH - 1) / 2 + 1][LINE_LENGTH]
              , const int numField)
{
  const char* name1 = "name";
  const char* name2 = "\"name\"";
  int nameField = -1;
  
  
  for (int i = 0; i < numField; i++)
  {
    // if last character is newline, strip it
    if (header[i][strlen(header[i]) - 1] == '\n')
    {
      header[i][strlen(header[i]) - 1] = '\0';
    }
    
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
                , const int nameField, char name[LINE_LENGTH])
{
  char lineList[(LINE_LENGTH - 1) / 2 + 1][LINE_LENGTH];
  int numFields = splitLine(line, lineList);
  
  // check if current line has all fields defined by header
  if (numFields != totalField) return false;
  
  strcpy(name, lineList[nameField]);
  
  if (name[strlen(name) - 1] == '\n')
  {
    name[strlen(name) - 1] = '\0';
  }
  return true;
}


void
printInvalidAndExit(void)
{
  printf("Invalid Input Format\n");
  exit(EXIT_SUCCESS);
}


// error code:
// -1: No error
//  1: Error opening file
//  2: No header
//  3: Line too long
//  4: No name or multiple name fields
//  5: Body line missing field(s)
//  6: Too many tweeters
//  7: File too large
//  8: No tweets
void printError(short error)
{
  switch (error) {
    case 1:
      printf("Error opening file\n");
      break;
    case 2:
      // empty file implies no header
      printf("No header\n");
      break;
    case 3:
      printf("Line too long\n");
      break;
    case 4:
      printf("No name field or multiple name fields\n");
      break;
    case 5:
      printf("Body line missing field(s)\n");
      break;
    case 6:
      printf("Too many tweeters\n");
      break;
    case 7:
      printf("File too large\n");
      break;
    case 8:
      printf("No tweets\n");
      break;
      
    default:
      break;
  }
}

int compare(const void *s1, const void *s2)
{
  Map *m1 = (Map*) s1;
  Map *m2 = (Map*) s2;
  return m2->count - m1->count;
}
