#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "json.h"
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>
#include <unistd.h>

    int main(int argc, char* argv[]){
        JSON json;
        std::string name=argv[1];
        std::string csvpoint=argv[2];
        std::string json2=argv[3];
        std::vector<std::string> x_json;
        std::vector<double> x_point;
        std::vector<double> y_point;
        std::vector<double> y_poly;
        std::vector<double> x_poly;
        std::vector<std::string> x_texte;
        std::vector<std::vector<std::string>> x_js;
        std::stringstream ss;
        std::vector<std::string> temp;
        std::string s="[";
        ss<<'"';
        s=s+ss.str();
        json.json_txt(name, x_js, temp);
       // json.read_json(name, x_json);

        json.read_point(csvpoint,x_point,y_point);
        json.line(x_texte, x_point, y_point, x_poly, y_poly, x_json, x_js, name, temp);
        return 0;
    }

