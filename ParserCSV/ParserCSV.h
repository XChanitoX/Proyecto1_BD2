#ifndef PROYECTO1_BD2_PARSERCSV_H
#define PROYECTO1_BD2_PARSERCSV_H

#include "../Librerias.h"
#include <unistd.h>

string SYSTEM_PATH = get_current_dir_name();

vector<vector<string>> ParserCSV(string fileName){
    string PATH = SYSTEM_PATH + '/' + fileName;
    ifstream data(PATH);
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

#endif //PROYECTO1_BD2_PARSERCSV_H