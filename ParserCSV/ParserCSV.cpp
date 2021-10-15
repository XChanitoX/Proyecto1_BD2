#include "ParserCSV.h"
#include "../Librerias.h"

int main(){
    ofstream Archivo;
    Archivo.open("../ParserCSV/archivo.dat",ios::app|ios::binary);

    if(!Archivo.is_open()){
        throw new exception;
    }

    string fileName = "../ParserCSV/RealStateDataSet.csv";

    vector<vector<string>> parseado;
    parseado = ParserCSV(fileName);

    for (auto & i : parseado) {
        for (auto & j : i) {
            Archivo << j << " ";
        }
        Archivo << '\n';
    }

    return 0;
}