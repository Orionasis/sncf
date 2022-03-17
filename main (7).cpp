#include <iostream>
#include <iostream>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include "wait.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <algorithm>

int read_texte(const std::string & fichier_i,
              std::vector<std::string> &x, std::string filter){
    std::ifstream flux(fichier_i.c_str(),std::ios::in);
    //test si le flux d'entrée échoue"
     if(flux.fail()){std::cerr<<"erreur a la lecture de "<<fichier_i<<std::endl;return 1;}
    x.clear();
    std::string x_temp="";
    std::string ligne;
    filter="*.txt";
    bool unit=false;
    if(filter=="*.txt")
        unit=true;
    if(!unit){
        std::cerr<<"le fichier n'est pas un texte \t"<<fichier_i<<std::endl;
        return 1;}
        //écriture dans le vecteur
    while(std::getline(flux, ligne)){;
            std::cerr<<ligne<<std::endl;
            ligne=ligne.substr(5, ligne.size());
            std::cerr<<ligne<<std::endl;
            std::istringstream iss(ligne.c_str());
            while(iss>>x_temp){
                x.push_back(x_temp);
            }
        }

    return 0;
   }


int read_makefile(const std::string & makefile){
    std::ifstream flux(makefile.c_str(),std::ios::in);
    //test si le flux d'entrée échoue"
    if(flux.fail()){std::cerr<<"le makefile n'existe pas encore"<<makefile<<std::endl;return 1;}
    return 0;
}

int read_exe(const std::string exe){
    std::ifstream flux(exe.c_str(),std::ios::in);
    //test si le flux d'entrée échoue"
    if(flux.fail()){std::cerr<<"ce n'est pas un fichier executable"<<std::endl;return 1;}
    return 0;
}


int line(const std::string & fichier, const std::string exe, const std::string makefile, const std::string fichier_json){
    std::string s;
    std::vector<std::string> vectstring;
    if(0!=read_makefile(makefile)){
        std::cerr<<"le fichier n'est pas un makefile"<<std::endl;
        return 1;
}
    if(0!=read_texte(fichier, vectstring, s))
    {
        std::cerr<<"ce n'est pas le bon fichier"<<std::endl;
        return 1;
    }
    if(0!=read_exe(exe)){
        std::cerr<<"ce n'est pas un exécutable"<<std::endl;
        return 1;
}
    std::ofstream flux_sortie(fichier_json.c_str(),std::ios::out|std::ios::trunc);

                if(flux_sortie.fail())
                {
                std::cerr<<"le fichier n'existe pas "<<fichier_json<<std::endl;
                return 1;

            }
    flux_sortie.precision(12);
                std::string begin="{\n"

                                  "\"type""\" "":" "\"Featurecollection""\" "",\n"
                        "\"features""\" "":" "[";
                std::string text="\"";
                            std::string bodytext="{\n"
                                                 "\"type""\"  "":" "\"Feature""\" ,\n"
                                    "\"name""\" "":" "{"
                                        "\"type""\" "":"  "\"name""\" ,\n"
                                         "\"name""\" "":"  "[";
//écriture dans le flux flux de sortie
std::string end="\n]},\n},\n";
                flux_sortie<<begin;
    for(unsigned long long int i=0;i<vectstring.size();i++){
        flux_sortie<<bodytext;
                        flux_sortie<<text;
                       flux_sortie<<vectstring[i];
                       flux_sortie<<text;
                       flux_sortie<<end;
        }
                    flux_sortie<<"]}";
        flux_sortie.close();
        return 0;
    }



int main(int argc, char* argv[])
{
    std::string filter;
    std::vector<std::string> s;
    for(int i=0;i<argc;i++){
        read_texte(argv[1], s, filter);
        read_exe(argv[2]);
        read_makefile(argv[3]);
        line(argv[1], argv[2], argv[3], argv[4]);
    }
    return 0;
}
