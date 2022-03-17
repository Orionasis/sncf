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
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>
#include <unistd.h>

int create_makefile(std::string make){
    std::ofstream flux_sortie(make,std::ios::out|std::ios::trunc);
    // test si le flux de sortie peut-être lu ou non
    if(flux_sortie.fail()){
        std::cerr<<"le fichier n'existe pas "<<make<<std::endl;
        return 1;
        }

    flux_sortie.precision(12);
    std::string bodysources="JSONFIC=../jsdosex\n"
            "JSONFICSOURCES=$(foreach dir,$(JSONFIC),$(dir)/*.json)\n"
            "EXE=../build-jsonheadliner/jsonheadiner\n"
            "HEADLINE=../headlineproject/healine4.json\n";
           std::string bodymake= "all:$(JSONFICSOURCSES)\n"
                   "\t for i in $(JSONFICSOURCES); do \n \
                               \t\t$(EXE) $(JSONFIC) $(HEADLINE) $$i ; \
                       \t done;";

//écrit dans le flux de sortie les chaînes de caractères défini plus tôt
    flux_sortie<<bodysources;
    flux_sortie<<bodymake;
return 0;
}

int main(int argc, char *argv[]){
    std::string make=argv[1];
create_makefile(make);
}

