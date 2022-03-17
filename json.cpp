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

JSON::JSON()
{}
unsigned long long int JSON::read_json(const std::string &name, std::vector<std::vector<std::string>> &x_json){
    std::ifstream flux_lecture(name.c_str(),std::ios::in);
            if(flux_lecture.fail()){
				//test si le flux d'entrée échoue"
                std::cerr<<"erreur a la lecture de "<<name<<std::endl;
                return 1;}
            flux_lecture.precision(12);
        x_json.clear();
        std::string x_jstemp="";
        std::vector<std::string> temp;
        std::string ligne="";
        /*if(getFileExtension(name)!="*.json"){
            std::cerr<<"le fichier n'est pas un fichier json " <<name<<std::endl;
            return 1;
            }*/
        //else{
                ligne=ligne.substr(0, ligne.size());
                while(std::getline(flux_lecture, ligne)){
            if(""==ligne){continue;}

                std::istringstream iss(ligne.c_str());
                std::cerr<<ligne<<std::endl;
                while(iss>>x_jstemp){
temp.push_back(x_jstemp);}
                    x_json.push_back(temp);

                }



//}

    flux_lecture.close();
        return 0;
       }
unsigned long long int JSON::creationsjson(std::string dir, std::string fichier_j, std::vector<std::vector<std::string>> &x_js){
    bool pointer=false;
    std::string mot;
    std::ifstream flux(fichier_j.c_str());
    //test si le flux de sortie échoue"
if(flux.fail()){
    std::cerr<<"erreur dans le fichier"<<std::endl;
    return 1;}
    int co = 269;
while(flux>>mot){
    for (int i = 0; i < co; i++){
        std::ofstream file(std::to_string(i) + ".json",std::ios::out|std::ios::trunc);
        //ouvre le fichier json"
        file.open (std::to_string(i) + ".json");


    if(0!=JSON::read_json(fichier_j, x_js)){
        std::cerr<<"le fichier n'est pas lue"<<std::endl;return 1;
    }
    //écriture des vecteurs dans le flux de sortie
    for(unsigned long long int i=0;i<x_js.size();i++){
        for(unsigned long long int j=0;j<x_js[i].size();j++){
            while(std::getline(flux, x_js[i][j])){
            if("\"Points""\""==x_js[i][j]){
                pointer=true;
for(unsigned long long int k=0;k<x_js[i][j].size();k++){
    if(pointer){
    if(x_js[i][j][k]!='"'){
file<<x_js[i][j][k];
}
    continue;
    }
            if("]]},"==mot){
                pointer=false;

            }


                }
            }
        }
    }

}
    file.close();
    }
}
    return 0;}
