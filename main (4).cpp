#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

int fichier(const std::string & fichier_i, std::vector<std::string> &x){
              std::ifstream flux_lecture(fichier_i.c_str(),std::ios::in);
              //test si le flux d'entrée échoue"
        if(flux_lecture.fail()){
            std::cerr<<"erreur a la lecture de "<<fichier_i<<std::endl;
            return 1;}
    x.clear();
    std::string x_temp="";
    std::string ligne;
    //écriture dans le vecteur
    while(std::getline(flux_lecture, ligne)){
        if("text "!=ligne.substr(0,5)){;
           std::cerr<<"le fichier n'est pas un fichier texte \t"<<fichier_i<<std::endl;
        return 1;}
            ligne=ligne.substr(6, ligne.size());
            std::istringstream iss(ligne.c_str());
            while(iss>>x_temp){
                x.push_back(x_temp);
            }
        }
flux_lecture.close();
    return 0;
   }
   
   
int read_poly(const std::string & fichier_i,
              std::vector<double> &x,
              std::vector<double> &y){
    std::ifstream flux(fichier_i.c_str(),std::ios::in);
    //test si le flux d'entrée échoue"
    if(flux.fail()){std::cerr<<"erreur dans la lecture de"<<fichier_i<<std::endl; return 1;}
    x.clear();
    y.clear();
    double x_temp=-666;
    double y_temp=-666;
    std::string ligne;
    //écriture dans le vecteur
    while(std::getline(flux, ligne)){
        if(""==ligne){continue;}
        if("Polyligne"!=ligne.substr(0,9)){
           std::cerr<<"le fichier n'est pas un fichier polyligne \t"<<fichier_i<<std::endl;
           return 1;}
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

int fichier_point(const std::string & fichier_i, std::vector<double> &x_point, std::vector<double> &y_point){
    std::ifstream flux_lecture(fichier_i.c_str(),std::ios::in);
    //test si le flux d'entrée échoue"
    if(flux_lecture.fail()){std::cerr<<"erreur dans la lecture de"<<fichier_i<<std::endl; return 1;}
flux_lecture.precision(12);
    x_point.clear();
    y_point.clear();
    double x_tempoint=-666;
    double y_tempoint=-666;
    std::string ligne;
    //écriture dans le vecteur
    while(std::getline(flux_lecture, ligne)){
if(""==ligne){continue;}
if("Point"!=ligne.substr(0,5)){
   std::cerr<<"le fichier n'est pas un fichier point \t"<<fichier_i<<std::endl;
   return 1;}
ligne=ligne.substr(6, ligne.size());
std::cerr<<ligne<<std::endl;
std::istringstream iss(ligne.c_str());
while(iss>>x_tempoint>>y_tempoint){
    x_point.push_back(x_tempoint);
    y_point.push_back(y_tempoint);
}
    }
    flux_lecture.close();
 return 0;
}

// 0 ok 1 erreur
int line(std::vector<double> x_poly,
         std::vector<double> y_poly,
         std::vector<double> x_point,
         std::vector<double> y_point,
         std::vector<std::string> x_text,
       std::string fichier_json)
{
std::ofstream flux_sortie(fichier_json.c_str(),std::ios::out|std::ios::trunc);
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
                        "\"type""\" "":"  "\"name""\" ,\n"
                         "\"name""\" "":"  "[";
                       //écriture dans le flux des différentes données mise dans les vecteurs
flux_sortie<<bodypoly;

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
std::vector<std::string> x_texte;
for(int i=1;i<argc;i++){
if(0!=read_poly(argv[1],
          x_poligne,
          y_poligne))
{
    std::cerr<<"erreur a la lecture du fichier "<<argv[1]<<std::endl;
return 1;
}
std::cerr<<"polyligne"<<std::endl;
for(unsigned long long int i=0;i<x_poligne.size();i++)
{
   std::cerr<<x_poligne[i]<<std::endl;
   std::cerr<<y_poligne[i]<<std::endl;
}
std::cerr<<"-------------"<<std::endl;
if(0!=fichier_point(argv[2],
          x_point1,
          y_point1))
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
if(0!=fichier(argv[3],
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
           argv[4]))
{
std::cerr<<"erreur a l execution de la fonction line"<<std::endl;
return 1;
}
}
    return 0;
}

