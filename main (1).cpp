#include <fstream>
#include <sstream>
#include <string.h>
#include <iostream>
#include <vector>
#include "json.h"
#include <iterator>
#include "wait.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <algorithm>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char*argv[])
{
    JSON json;
    std::string name=argv[2];
    std::vector<std::vector<std::string>> x_js;
    json.read_json(name, x_js);
    json.creationsjson(argv[1],argv[2],x_js);
    return 0;
}
