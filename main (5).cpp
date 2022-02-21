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


int main(int argc, char* argv[])
{
    JSON json2;
            std::string name=argv[1];
            std::string csvpoint=argv[2];
            std::string texte=argv[3];
            std::vector<std::string> x_texte;
            std::vector<double> y_poligne;
            std::vector<double> x_poligne;

json2.read_poly(csvpoint,
          x_poligne,
          y_poligne);

    json2.read_texte(texte,
              x_texte);


json2.line(name, x_texte,x_poligne, y_poligne);







    return 0;
}
