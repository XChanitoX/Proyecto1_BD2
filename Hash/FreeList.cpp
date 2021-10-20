#include "FreeList.h"
#include <unistd.h>

template<class Record>
int FreeList<Record>::length(fstream& file) {
    file.open(fileName, ios::ate|ios::binary);
    if(!file.is_open())
        throw new exception;
    int bytes = (int)file.tellg() - sizeof(int);
    return bytes/ sizeof(Record);
}

template<class Record>
int FreeList<Record>::addRecord(Record record) {
    //Fuente:https://www.delftstack.com/es/howto/c/c-check-if-file-exists/
    if(!access(fileName.c_str(), F_OK)){
        fstream file(fileName, ios::in|ios::out|ios::binary);
        if(!file.is_open()){
            throw new exception;
        }
        int header = readHeader(file);
        int recordPosition;
        if( (int)header == -1) {
            recordPosition = length(file);
            file.close();
            file.open(fileName, ios::out|ios::binary);
            writeRecord(record, recordPosition, file);
        }
        else{
            Record temp = readRecord(header,file);
            recordPosition = header;
            header = temp.nextDel;
            writeHeader(header,file);
            writeRecord(record, recordPosition, file);
        }
        file.close();
        return recordPosition;
    }
    else{
        fstream file(fileName, ios::out|ios::binary);
        int header = -1;
        writeHeader(header,file);
        writeRecord(record,0,file);
        return 0;
    }
}

template<class Record>
Record& FreeList<Record>::readRecord(int pos) {
    fstream file(fileName, ios::in|ios::binary);
    int numRecords = length(file);
    if(numRecords == 0){
        cout<<"Could not read record in this position, because empty file!" << endl;
        return nullptr;
    }
    if( 0<=pos && pos<numRecords){
        Record record = readRecord(pos, file);
        file.close();
        return record;
    }
    else
        cout<<"Could not read record, because position is wrong!" << endl;
        throw new exception;
}

template<class Record>
void FreeList<Record>::writeRecord(Record record, int pos) {
    fstream file(fileName, ios::in|ios::binary);
    int numRecords = length(file);
    if(numRecords==0){
        cout << "Could not write record, because empty file!" << endl;
        return;
    }
    if(pos<numRecords && pos >=0){
        file.close();
        file.open(fileName, ios::in|ios::binary);
        writeRecord(record,pos,file);
        file.close();
    }
    else{
        cout<<"Could not write record, because position is wrong!" << endl;
        return;
    }
}


template<class Record>
bool FreeList<Record>::deleteRecord(int pos) {
    fstream file(fileName, ios::in|ios::out|ios::binary);
    int numRecords = length(file);
    if(numRecords==0){
        cout << "Could not delete record, because empty file!" << endl;
        return false;
    }

    if(pos< numRecords && pos>=0){
        int header = readHeader(file);
        writeHeader(pos, file);
        Record record = readRecord(pos,file);
        record.nextDel = header;
        writeRecord(record, pos, file);
        file.close();
        return true;
    }
    else{
        cout<<"Could not delete record, because position is wrong!"<<endl;
        return false;
    }
}

template<class Record>
vector<Record> FreeList<Record>::scanAll() {
    vector<Record> vector;
    fstream file(fileName, ios::in|ios::binary);
    if(!file.is_open())
        throw new exception;
    Record temp;
    file.seekg(sizeof(int), ios::beg);
    while(!file.eof()){
        file.read((char*)& temp, sizeof(Record));
        if(!temp.nextDel)
            vector.push_back(temp);
    }
    file.close();
    return vector;
}

template<class Record>
void FreeList<Record>::setFileName(const string &fileName) {
    FreeList::fileName = fileName;
}
