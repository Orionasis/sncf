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

std::string getFileExtension(std::string filePath)
{
    // Find the last position of '.' in given string
    std::size_t pos = filePath.rfind('.');

    // If last '.' is found
    if (pos != std::string::npos) {
        // return the substring
        return filePath.substr(pos);
    }
    // In case of no extension return empty string
    return "";
}

int read_poly(const std::string & fichier_i,
              std::vector<double> &x,
              std::vector<double> &y,
              std::string extension){

extension=getFileExtension(fichier_i);
std::cerr<<extension<<std::endl;
    std::ifstream flux(fichier_i.c_str(),std::ios::in);
//test si le flux d'entrée échoue"
    if(flux.fail()){std::cerr<<"erreur dans la lecture de"<<fichier_i<<std::endl; return 1;}

    x.clear();
    y.clear();
    double x_temp=-666;
    double y_temp=-666;
    std::string ligne;
    while(std::getline(flux, ligne)){
        if(""==ligne){continue;}

        if("Polyligne"!=ligne.substr(0,9)){
           std::cerr<<"le fichier n'est pas un fichier polyligne \t"<<fichier_i<<std::endl;
           return 1;}
//écriture dans le vecteur

            ligne=ligne.substr(10, ligne.size());
            std::istringstream iss(ligne.c_str());
            while(iss>>x_temp>>y_temp){
                x.push_back(x_temp);
                y.push_back(y_temp);
            }//end while iss>>

    }//end while getline
    flux.close();
    return 0;

}

std::string GetFileListing(std::vector<std::string>& vectlisting, std::string directory, std::string fileFilter, bool recursively)
{


 // if(recursively==true){std::cerr<<"recursivite du getfilelisitng non implemente sous posix-> mais vasy fait le !"<<std::endl; exit(1);}
if(fileFilter.substr(0,1)=="*"){fileFilter=fileFilter.substr(1,fileFilter.size());}
    DIR* dirp = opendir(directory.c_str());
     struct dirent * dp;
     while ((dp = readdir(dirp)) != NULL) {

         if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0){continue;}

         std::cerr<<directory+"/"+dp->d_name<<std::endl;
         if(fileFilter==".*")
         {
 vectlisting.push_back(directory+"/"+dp->d_name);
 if(true==recursively){
             GetFileListing(vectlisting, directory+"/"+dp->d_name, fileFilter, recursively);
 }




 continue;

         }
         std::string fichier=dp->d_name;
         std::cerr<<fichier<<std::endl;
         if(fichier.size()>fileFilter.size())
         {
            if(fichier.substr(fichier.size()-fileFilter.size(),fichier.size())==fileFilter)
            {

 vectlisting.push_back(directory+"/"+dp->d_name);
            }

         }


 if(true==recursively){
             GetFileListing(vectlisting, directory+"/"+dp->d_name, fileFilter, recursively);
     }


     }
     return "";
     closedir(dirp);



}
int fichier(std::string & fichier_i, std::vector<std::string> &x){
    std::vector<std::string> vectlisting;
    bool recursively=false;
    GetFileListing(vectlisting, fichier_i, ".txt", recursively);
    for(unsigned long long int i=0; i<vectlisting.size();i++){
        fichier_i=vectlisting[i];
    }
              std::ifstream flux_lecture(fichier_i.c_str(),std::ios::in);
              //test si le flux d'entrée échoue"
        if(flux_lecture.fail()){
            std::cerr<<"erreur a la lecture de "<<fichier_i<<std::endl;
            return 1;}
    x.clear();
//écriture dans le vecteur
    std::string x_temp="";
    std::string ligne;
    while(std::getline(flux_lecture, ligne)){
        /*if("text "!=ligne.substr(0,5)){

std::cerr<<"fuck"<<std::endl;
           std::cerr<<"le fichier n'est pas un fichier texte \t"<<fichier_i<<std::endl;
        return 1;}*/

            ligne=ligne.substr(6, ligne.size());

            std::istringstream iss(ligne.c_str());

            while(iss>>x_temp){
                x.push_back(x_temp);
            }
        }
flux_lecture.close();

    return 0;

   }
int fichier_point(std::string & fichier_i, std::vector<double> &x_point, std::vector<double> &y_point, std::string extension){
    std::string virgule=",";
    std::string espace=" ";
    std::vector<std::string> vectlisting;
    bool recursively=false;
    GetFileListing(vectlisting, fichier_i, extension, recursively);
    for(unsigned long long int i=0; i<vectlisting.size();i++){
        fichier_i=vectlisting[i];
    }
    std::ifstream flux_lecture(fichier_i.c_str(),std::ios::in);
    //test si le flux de sortie échoue"
    if(flux_lecture.fail()){std::cerr<<"erreur dans la lecture de "<< fichier_i <<std::endl; return 1;}
flux_lecture.precision(12);
//écriture dans les vecteurs
    x_point.clear();
    y_point.clear();
    double x_tempoint=-666;
    double y_tempoint=-666;
    std::string ligne_point;
    while(std::getline(flux_lecture, ligne_point)){

            ligne_point=ligne_point.substr(6, ligne_point.size());
            std::istringstream iss2(ligne_point.c_str());
while(iss2>>x_tempoint>>y_tempoint){
    x_point.push_back(x_tempoint);
    y_point.push_back(y_tempoint);
}
    }
    flux_lecture.close();
 return 0;

}
int create_json(std::string & directory){
    std::vector<std::string> vectlisting;
    bool recursively=false;
    if(0!=atoi(GetFileListing(vectlisting, directory, "*.json", recursively).c_str())){
        for(unsigned long long int i=0;i<vectlisting.size();i++){
            std::string fichier_i;
            fichier_i=vectlisting[i];
        std::ofstream flux_sortie(fichier_i.c_str(),std::ios::out|std::ios::trunc);
        //test si le flux de sortie échoue"
        if(flux_sortie.fail())
            {
            std::cerr<<"le fichier n'existe pas "<<fichier_i<<std::endl;
            return 1;
}
        }

    }
    return 0;
}
/*int read_point(const std::string & fichier_i,
        std::vector<double> &x_point,
           std::vector<double> &y_point){*/



/* int read_texte(const std::string & fichier_i, std::vector<std::string> &x){
              std::ifstream flux_lecture(fichier_i.c_str(),std::ios::in);
        if(flux_lecture.fail()){
            std::cerr<<"erreur a la lecture de "<<fichier_i<<std::endl;
            return 1;}
    x.clear();
    std::cerr<<fichier_i<<std::endl;
    std::string x_temp="";
    std::string ligne;
    while(std::getline(flux_lecture, ligne)){
        if("text"!=ligne.substr(0,4)){;
           std::cerr<<"le fichier n'est pas un fichier texte \t"<<fichier_i<<std::endl;
        return 1;}
            std::cerr<<ligne<<std::endl;
            ligne=ligne.substr(5, ligne.size());
            std::cerr<<ligne<<std::endl;
            std::istringstream iss(ligne.c_str());
            while(iss>>x_temp){
                x.push_back(x_temp);
            }
        }

    return 0;
   }*/

// 0 ok 1 erreur
int line(std::vector<double> x_poly,
         std::vector<double> y_poly,
         std::vector<double> x_point,
         std::vector<double> y_point,
         std::vector<std::string> x_text,
       std::string & fichier_json, std::string &fichier_i)
{


create_json(fichier_json);
std::ofstream flux_sortie(fichier_i.c_str(),std::ios::out|std::ios::trunc);
//test si le flux de sortie échoue"
if(flux_sortie.fail())
    {
    std::cerr<<"le fichier n'existe pas "<<fichier_json<<std::endl;
    return 1;
    }
flux_sortie.precision(12);
            std::string begin="{\n"

                              "\"type""\" "":" "\"Featurecollection""\" "",\n"
                    "\"features""\" "":" "[";


            flux_sortie<<begin;
            std::string bodypoint="{\n" "\"type""\" "":" "\"Feature""\" ,\n" "\"geometry""\" "":" "{\n"
                                  "\"type""\" "":" "\"Point""\" ""," "\"coordinates""\" "":" "[";
            std::string end="\n]},\n},\n";
            std::string bodypoly="{\n"
                                   "\"type""\" "":" "\"Feature""\" ,\n" "\"geometry""\" "":" "{"
"\"type""\" "":" "\"LineString""\"""," "\"coordinates""\" "":" "[";
            std::string text="\"";
            std::string bodytext="{\n"
                                 "\"type""\"  "":" "\"Feature""\" ,\n"
                    "\"name""\" "":" "{"
                        "\"type""\" "":"  "\"name""\", "
                         "\"name""\" "":"  "[";

flux_sortie<<bodypoly;
//écriture dans le flux de sortie
            for(unsigned long long int i=0;i<x_poly.size();i++){
                flux_sortie<<"[";
                flux_sortie<<x_poly[i];
                flux_sortie<<",";
                flux_sortie<<y_poly[i];
                flux_sortie<<"]";
                flux_sortie<<",";

            }
            flux_sortie<<end;
            for(unsigned long long int k=0;k<x_point.size();k++)
            {
                flux_sortie<<bodypoint;
                flux_sortie<<x_point[k];
                flux_sortie<<",";
                flux_sortie<<y_point[k];
                flux_sortie<<end;
            }
            flux_sortie<<end;

            for(unsigned long long int j=0;j<x_text.size();j++){

                flux_sortie<<bodytext;
                flux_sortie<<text;
               flux_sortie<<x_text[j];
               flux_sortie<<text;
               flux_sortie<<end;
}
            flux_sortie<<"]}";
flux_sortie.close();




// getlin c'est bien mais si tu as que des espace et un ordre connu tu peux faire le bourrin








return 0;
}
int main(int argc, char* argv[])
{


std::cerr.precision(12);

std::vector<double> x_poligne;
std::vector<double> y_poligne;
std::vector<double> x_point1;
std::vector<double> y_point1;
std::string point=argv[2];
std::string texte=argv[3];
std::string json=argv[4];
std::vector<std::string> x_texte;
std::string ext;
std::string fichier_json="js3.json";

if(0!=read_poly(argv[1],
          x_poligne,
          y_poligne, ext))
{
    std::cerr<<"erreur a la lecture du fichier "<<argv[1]<<std::endl;
return 1;
}

for(unsigned long long int i=0;i<x_poligne.size();i++)
{
   std::cerr<<x_poligne[i]<<std::endl;
   std::cerr<<y_poligne[i]<<std::endl;

}
std::cerr<<"-------------"<<std::endl;

if(0!=fichier_point(point,
          x_point1,
          y_point1, ext))
{

    std::cerr<<"erreur a la lecture du fichier"<<std::endl;
return 1;
}

std::cerr<<"point"<<std::endl;
for(unsigned long long int j=0;j<x_point1.size();j++)
{
   std::cerr<<x_point1[j]<<std::endl;
   std::cerr<<y_point1[j]<<std::endl;
}
std::cerr<<"-------------"<<std::endl;
if(0!=fichier(texte,
              x_texte)){

        std::cerr<<"erreur a la lecture du fichier texte"<<std::endl;
    return 1;
    }
std::cerr<<"texte"<<std::endl;
        for(unsigned long long int k=0;k<x_texte.size();k++)
        {
           std::cerr<<x_texte[k]<<std::endl;
        std::cerr<<std::endl;

        }

std::cerr<<"-------------"<<std::endl;

std::cerr<<"tentative ecriture"<<std::endl;
if(0!=line(x_poligne, y_poligne,x_point1,y_point1,x_texte,
           json, fichier_json))
{
std::cerr<<"erreur a l execution de la fonction line"<<std::endl;
return 1;
}






    return 0;
}

