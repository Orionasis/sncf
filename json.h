#ifndef JSON_H
#define JSON_H
#include <fstream>
#include <sstream>
#include <string.h>
#include <iostream>
#include <vector>
#include <iterator>
#include "wait.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <algorithm>
#include <unistd.h>
#include <stdlib.h>

class JSON
{
public:
    JSON();
    unsigned long long int creationsjson(std::string dir, std::string fichier_j, std::vector<std::vector<std::string>> &x_js);
   unsigned long long int read_json(const std::string &name, std::vector<std::vector<std::string>> &x_json);
};

#endif // JSON_H
