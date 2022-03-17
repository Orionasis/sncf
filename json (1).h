#ifndef JSON_H
#define JSON_H
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

class JSON
{
public:
    unsigned long long int suprimer(std::string &name);
    unsigned long long int read_poly(std::string &csvligne,std::vector<double> &x_poly,std::vector<double> &y_poly);
    int line(std::string jsonext, std::vector<std::string> x_texte, std::vector<double> x_poly,std::vector<double> y_poly);
    unsigned long long int read_texte(std::string &txtnom, std::vector<std::string> &x_texte);

};

#endif // JSON_H
