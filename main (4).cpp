#include <iostream>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "outils.h"
#include <iterator>
#include "wait.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <algorithm>

unsigned long long int taille(const std::string & fichier){
     unsigned long long int size;
    std::ifstream flux_lecture(fichier);
    if(flux_lecture.fail()){
                std::cerr<<"erreur a la lecture de "<<fichier<<std::endl;
                return 1;

    }
    flux_lecture.seekg(0, std::ios::end);
    size=flux_lecture.tellg();
    flux_lecture.close();
 //   std::cout << "Taille du fichier : " <<size << "octets." <<std::endl;
    return size;

}

int getfiledir(const std::string directory, std::vector<std::string> vecldir){
    vecldir.clear();
    outils::GetDirectoryListing(vecldir, directory);
    std::ifstream flux(directory);
    if(flux.fail()){
        std::cerr<<"le string"<<directory<<"n'est pas un dossier"<<std::endl;
        return 1;
    }
    flux.close();
    return 0;
}

int getfileListing(std::vector<std::string>& vectlisting, std::string directory, std::string filter, bool recursively){
    vectlisting.clear();
    unsigned long long int i;
    outils::GetFileListing(vectlisting, directory, filter, true);
    for(i=0; i<vectlisting.size();i++){
        if(outils::IsDirectoryExist(vectlisting[i])){

            recursively=true;
            outils::GetFileListing(vectlisting, vectlisting[i], filter, recursively);
            return 1;
        }

    }
    recursively=false;

    return 0;
    }



int main(int argc, char *argv[])
{
    std::vector<unsigned long long int> vectsize;
    std::vector<unsigned long long int> vectsize2;

    if(argc!=2){std::cerr<<"attendu nom_exe dossier_in"<<std::endl;return 1;}
    std::vector<std::string> vecldir;
    std::vector<std::string> vecldir2;
    std::vector<std::string> vectlisting;
    std::vector<std::string> vectlisting2;
    std::string filter="*.*";
    int k=0;
    bool recursively=true;
    int size;
    int size2;

    std::vector<std::string> vectlisting_jc;

   /*outils::GetFileListing(vectlisting_jc,"/home/devops/line/line","*.*",true);
for(unsigned long int i=0;i<vectlisting_jc.size();i++)
   {
    std::cerr<<vectlisting_jc[i]<<std::endl;
   }*/
   //écriture des vecteurs dans le vecteur comparatif
    getfileListing(vectlisting, argv[1],"*.*", true);
    for(unsigned long long int i=0;i<vectlisting.size();i++){
        vectsize.push_back(taille(vectlisting[i]));
    }
    sleep(15);
   //écriture des vecteurs dans le vecteur comparatif
    getfileListing(vectlisting2, argv[1], "*.*", true);
    for(unsigned long long int j=0; j<vectlisting2.size();j++){
        vectsize2.push_back(taille(vectlisting2[j]));

        }
        //compare la taille des vecteurs
    if(vectsize.size()!=vectsize2.size()){

        return 1;}

    for(unsigned long long int val=0;val<vectsize.size();val++)
    {//compare les différentes valeurs des vecteurs
        if(vectsize[val]!=vectsize2[val]){
            return 1;}
    }
   std::cerr<<"ok"<<std::endl;

    return 0;
}


