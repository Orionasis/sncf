#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

    std::ofstream flux_sortie(argv[1],std::ios::out|std::ios::trunc);
    //test si le flux de sortie échoue"
    if(flux_sortie.fail()){
        std::cerr<<"le fichier n'existe pas "<<argv[1]<<std::endl;
        return 1;
        }

    flux_sortie.precision(12);
    std::string bodysources="JSONCSV=../io\n"
            "JSONCSVSOURCES=/home/devops/line/line/io/polyligneTest.csv\n"
            "JSONPATA=/home/devops/line/line/pata\n"
            "JSONPATASOURCES=$(foreach dir,$(JSONPATA),$(dir)/*.csv)\n"
            "JSONTXT=/home/devops/line/line/cata\n"
            "JSONTXTSOURCES=$(foreach dir,$(JSONTXT),$(dir)/*.txt)\n"
            "EXEJSON=/home/devops/line/line/creation_json\n"
            "EXEJSONSOURCES=$(foreach dir,$(EXEJSON),$(dir)/*.cpp)\n"
            "JSON=/home/devops/line/line/js\n"
            "GPP=g++\n"
            "EXE=creation_json\n"
            "ARGS=$(JSONCSVSOURCES) $(JSONPATA) $(JSONTXT) $(JSON)\n";
           std::string bodymake= "all: run\n"

            "run: $(EXE)\n"
                "\t./$(EXE) $(ARGS)\n"
            "creation_json: creation_json.o\n"
                "\t$(GPP) $< -o $@\n"

            "creation_json.o: $(EXEJSONSOURCES)\n"
                "\t$(GPP) -c $< -o $@ ";
    flux_sortie<<bodysources;
    flux_sortie<<bodymake;
return 0;
}


