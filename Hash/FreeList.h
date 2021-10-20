#ifndef HASHINDEX_FREELIST_H
#define HASHINDEX_FREELIST_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

template<class Record>
class FreeList {
private:
    string fileName;
    int readHeader(fstream& file){
        int header;
        file.seekg(0, ios::beg);
        file.read((char*)&header, sizeof(int));
        return header;
    }
    void writeHeader(int header, fstream& file){
        file.seekp(0, ios::beg);
        file.write((char*)& header, sizeof(int));
    }
    void writeRecord(Record& record, int pos, fstream& file){
        file.seekp(pos*sizeof(Record)+ sizeof(int), ios::beg);
        file.write((char*)& record, sizeof(Record));
    }

    Record& readRecord(unsigned int pos, fstream& file){
        Record record;
        file.seekg(pos*sizeof(Record)+sizeof(int), ios::beg);
        file.read((char*)& record, sizeof(Record));
        return record;
    }
public:
    FreeList(){};
    FreeList(string _fileName_): fileName(_fileName_){}
    int length(fstream& file);
    ///Al agregar un registro, devuelve la posicion logica del registro agregado.
    int addRecord(Record record);
    Record& readRecord(int pos);
    void writeRecord(Record record, int pos);
    void setFileName(const string &fileName);
    bool deleteRecord(int pos);
    vector<Record> scanAll();
};

#endif //HASHINDEX_FREELIST_H
