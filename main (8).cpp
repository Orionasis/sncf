#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    std::ofstream flux_sortie(argv[1],std::ios::out|std::ios::trunc);
    //test si le fichier de sortie 
        if(flux_sortie.fail()){
            std::cerr<<"le fichier n'existe pas "<<argv[1]<<std::endl;
            return 1;
        }
        flux_sortie.precision(12);
        std::string bodysources="ARGS=/home/devops/line\n"
                "EXEC=../build-line3-Desktop-Du00e9faut/line3\n"

                "all: exec\n"

                "exec: $(EXEC)\n"
                    "\t./$< $(ARGS)\n";
                    //écrit dans le flux de sortie la chaîne de caractère
        flux_sortie<<bodysources;
        std::string sortie=argv[1];
        int nbthreads = 5;
            std::string s;
            std::stringstream out;
            out << nbthreads;
            s = out.str();
            //fait une parallélisation mixte
std::string make= "make -f"+sortie+" -j "+s;
if(0!=system(make.c_str())){
        std::cerr<<"le fichier n'existe pas "<<sortie<<std::endl;
        return 1;
    }
    return 0;


}
