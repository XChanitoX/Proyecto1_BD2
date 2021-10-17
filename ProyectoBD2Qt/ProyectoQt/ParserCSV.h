#ifndef PARSERCSV_H
#define PARSERCSV_H

#include "Librerias.h"

vector<vector<string>> ParserCSV(string fileName){
    ifstream data(fileName);
    string line;
    vector<vector<string>> parsedCsv;
    while(getline(data,line))
    {
        stringstream lineStream(line);
        string cell;
        vector<string> parsedRow;
        while(getline(lineStream,cell,','))
        {
            parsedRow.push_back(cell);
        }

        parsedCsv.push_back(parsedRow);
    }
    return parsedCsv;
}

#endif // PARSERCSV_H
