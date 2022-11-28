#include <fstream>
#include <sstream>
#include <string>
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








    unsigned long long int JSON::read_texte(std::string &txtnom,std::vector<std::string> &x_texte){
        std::ifstream flux_lecture(txtnom.c_str(),std::ios::in);
                if(flux_lecture.fail()){
                    std::cerr<<"erreur a la lecture de "<<txtnom<<std::endl;
                    return 1;}
            x_texte.clear();
            std::string x_temp="";
            std::string ligne;
            while(std::getline(flux_lecture, ligne)){
                if("text "!=ligne.substr(0,5)){;
                   std::cerr<<"le fichier n'est pas un fichier texte \t"<<txtnom<<std::endl;
                return 1;}
                    ligne=ligne.substr(6, ligne.size());
                    std::istringstream iss(ligne.c_str());
                    while(iss>>x_temp){
                        x_texte.push_back(x_temp);
                    }
                }
        flux_lecture.close();
            return 0;
           }


    unsigned long long int JSON::read_poly(std::string &csvligne,std::vector<double> &x_poly,std::vector<double> &y_poly){
        std::ifstream flux(csvligne.c_str(),std::ios::in);
        //test si le flux d'entrée échoue"
           if(flux.fail()){std::cerr<<"erreur dans la lecture de"<<csvligne<<std::endl; return 1;}
           x_poly.clear();
           y_poly.clear();
           double x_temp=-666;
           double y_temp=-666;
           std::string ligne;
           while(std::getline(flux, ligne)){
               if(""==ligne){continue;}
               if("Polyligne"!=ligne.substr(0,9)){
                  std::cerr<<"le fichier n'est pas un fichier polyligne \t"<<csvligne<<std::endl;
                  return 1;}
                   ligne=ligne.substr(10, ligne.size());
                   std::istringstream iss(ligne.c_str());
                   while(iss>>x_temp>>y_temp){
                       x_poly.push_back(x_temp);
                       y_poly.push_back(y_temp);
                   }//end while iss>>
           }//end while getline
           flux.close();
           return 0;
    }
    int JSON::line(std::string json, std::vector<std::string> x_texte, std::vector<double> x_poly,std::vector<double> y_poly){
        std::ofstream flux(json.c_str(),std::ios::out|std::ios::trunc);
        //test si le flux de sortie échoue"
        if(flux.fail()){
            std::cerr<<"erreur dans le fichier"<<json<<std::endl;
            return 1;
        }
        flux.precision(12);
        std::string begin="{" "\"FileHeader""\":" "{" "\n";
                          std::string bodybegin= "\"Libelle""\" : ""\"nc""\""",""\n"
                "\"GuidGaia""\" "":""\"nc""\""",""\n"
                "\"DateReleve""\" "":" "\"JJ/MM/AAAA""\",""\n"
                          "\"NatureElement""\":" "\"nc""\""",""\n"
                          "\"NomEngin""\""":""\"nc""\""",""\n"
                                                  "\"IdPhoto""\" "":" "\"nc""\",""\n"
                                                  "\"PkDebut""\" "":" "\"KKK+MMM""\"," "\n"                                                  
                                                   "\"GpsDebutVCI""\" "":""[0.0,0.0,0.0],""\n"
                                                  "\"PkFin""\" "":" "\"KKK+MMM""\",""\n"
                                                  "\"GpsFinVCI""\" "":""[" "0.0"",0.0,0.0],""\n"
                                                  "\"NumeroLigneVCI""\" "":" "0""," "\n"
                                                  "\"NomLigneVCI""\" "":""\"nc""\"," "\n"
                                                  "\"NomVCI""\" "":""\"nc""\"," "\n"
                                                  "\"NombreVCO""\" "":""2""," "\n"
                                                  "\"NumLigneVCOG""\" "":" "0," "\n"
                                                  "\"NomLigneVCOG""\" "":""\"nc""\"," "\n"
                                                  "\"NomVCOG""\" "":""\"nc""\"," "\n"
                                                  "\"NumLigneVCOD""\" "":" "0," "\n"
                                                  "\"NomLigneVCOD""\" "":""\"nc""\"," "\n"
                                                  "\"NomVCOD""\" "": ""\"nc""\"," "\n"
                                                  "\"NombreProfil""\" "":""1" "}," "\n";
                    flux<<begin;
                    flux<<bodybegin;
                   std::string tete= "\"Profile""\":" "[{" "\n"
                            "\"NumeroProfil""\":" "1" ",""\n"
                            "\"PkProfil""\":" "\"KKK+MMM""\" ""," "\n"
                            "\"GpsProfil""\":" "[0.0,0.0,0.0] ""," "\n"
                            "\"CoordonneesRailsVCI""\":" "[0.0,0.0,0.0,0.0]" "," "\n"
                            "\"FlecheVCI""\":" "0.0 ""," "\n"
                            "\"DeversVCI""\":" "0.0 ""," "\n"
                            "\"CoordonneesRailsVCOG""\":""[0.0,0.0,0.0,0.0]""," "\n"
                            "\"FlecheVCOG""\":" "0.0""," "\n"
                            "\"DeversVCOG""\":" "0.0,""" "\n"
                            "\"IncertitudeDeversVCOG""\" :" "0.0""," "\n"
                            "\"IncertitudeZVCOG""\" :" "0.0""," "\n"
                            "\"CoordonneesRailsVCOD""\" :" "[0.0,0.0,0.0,0.0]""," "\n"
                           "\"FlecheVCOD""\" :" " 0.0""," "\n"
                           "\"DeversVCOD""\":" "0.0""," "\n"
                           "\"IncertitudeDeversVCOD""\":" "0.0""," "\n"
                            "\"IncertitudeZVCOD""\":" "0.0""," "\n"
                            "\"CoordonneeCatenaireVCI""\":" "[0.0,0.0]""," "\n"
                            "\"CoordonneeCatenaireVCOG""\" :" "[0.0,0.0]""," "\n"
                            "\"CoordonneeCatenaireVCOD""\":" "[0.0,0.0]""," "\n"
                            "\"NombrePointProfil""\":" "7""," "\n";
                    flux<<tete;
       //std::string end="]}]}";
       std::string bodypoly="\"Points""\":" "[";
       //écriture dans le flux de sortie
flux<<bodypoly;
           for(unsigned long long int i=0;i<x_poly.size();i++){
                          flux<<"[";
                         flux<<x_poly[i];
                         flux<<",";
                          flux<<y_poly[i];
                          flux<<"]";
                          flux<<",";
                          }
flux<<"]\n}]\n}";
          flux.close();
        return 0;
    }
