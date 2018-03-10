//
//  main.cpp
//  mapCmp
//
//  Created by Richard Li on 3/10/18.
//  Copyright © 2018 Richard Li. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstring>

void generateMap(std::fstream* fs, std::map<std::string, std::string> map);

int main(int argc, const char * argv[]) {
  if (argc != 3)
  {
    std::cout << "Usage: ./generateMap <my_output> <answer_output>"
    << std::endl;
  }
  
  const std::string MYOUT = argv[1];
  const std::string ANSWEROUT = argv[2];
  
  
  std::map<std::string, std::string> myMap;
  std::map<std::string, std::string> answerMap;
  
  std::fstream myFs(MYOUT);
  std::fstream answerFs(ANSWEROUT);
  
  generateMap(&myFs, myMap);
  generateMap(&answerFs, answerMap);
  if (myMap == answerMap)
  {
    std::cout << "True" << std::endl;
  }
  else
  {
    std::cout << "False" << std::endl;
  }
  return 0;
}

void generateMap(std::fstream* fs, std::map<std::string, std::string> map)
{
  std::string line;
  std::string key, value;
  
  while (std::getline(*fs, line))
  {
    int index = (int) line.find(":");
    key = line.substr(0, index);
    if (key[0] == '\"' && key[key.length() - 1] == '\"')
    {
      key = key.substr(1, key.length() - 2);
    }
    value = line.substr(index + 1);
    map.insert(std::pair<std::string, std::string>(key, value));
  }
  
//  print map
//  for (auto it = map.begin(); it != map.end(); ++it)
//  {
//    std::cout << it->first << " " << it->second << std::endl;
//  }
}
