#ifndef HASHINDEX_FREELIST_H
#define HASHINDEX_FREELIST_H
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

template<class Record>
class FreeList {
private:
    string fileName;
    int readHeader();
    void writeHeader(int header);
    Record& readRecord(unsigned int position);
    
public:
    FreeList(string _fileName_): fileName(_fileName_){}
    int length();
    int addRecord(Record record);///Al agregar un registro, devuelve la posicion logica del registro agregado para mapearlo en hash.h
    Record readRecord(int pos);
    void writeRecord(Record record, int pos);
    vector<Record> scanAll();
    bool deleteRecord(int pos);
};

#endif //HASHINDEX_FREELIST_H
