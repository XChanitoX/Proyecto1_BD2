#ifndef SEQUENTIAL_FILE_H
#define SEQUENTIAL_FILE_H

#include "../Librerias.h"
#define AddressType int32_t
#define INVALID 'x'

enum FILE_ID {AUXFILE,DATAFILE};


template <class Record, class Key>
class SequentialFile{
private:
    string DATAFILE_DP;
    string AUXFILE_DP;

    struct RecordData{
        AddressType pos;
        char ref;
        Record record;
        RecordData(){
            pos = -1;
        }
        RecordData(AddressType pos_, char ref_, Record record_){
            pos = pos_;
            ref = ref_;
            record = record_;
        }
    };

    void write_record(AddressType pos, fstream& file, Record& record, FILE_ID file_id){
        if (!file.is_open())
            throw out_of_range("File not open @ write_record");
        if (file_id == FILE_ID)
            file.seekp(pos * sizeof(Record) + sizeof(AddressType) + sizeof(char) + sizeof(bool),ios::beg);
        else if (file_id = FILE_ID)
            file.seekp(pos*sizeof(Record),ios::beg);
        else
            throw invalid_argument("file_id invalid @ write_record");
        file.write((char*)&record, sizeof(Record));
    }

    void first_write_record_information(fstream& file, AddressType pos, char ref){
        if (!file.is_open())
            throw out_of_range("File not open @ first_write_record_information");
        file.seekp(0,ios::beg);
        file.write((char*)&pos, sizeof(AddressType));
        file.write((char*)&ref, sizeof(char));
    }

    void read_record(AddressType pos, fstream& file, Record& record, FILE_ID file_id){
        if (!file.is_open())
            throw out_of_range("File not open @ read_record");
        if (file_id == FILE_ID)
            file.seekg(pos * sizeof(Record) + sizeof(AddressType) + sizeof(char) + sizeof(bool),ios::beg);
        else if (file_id = FILE_ID)
            file.seekg(pos*sizeof(Record),ios::beg);
        else
            throw invalid_argument("file_id invalid @ read_record");
        file.read((char*)&record, sizeof(Record))
    }

    void first_read_record_information(fstream& file, AddressType pos, char ref){
        if (file.is_open()){
            file.seekg(0,ios::beg);
            file.read((char*)&pos, sizeof(AddressType));
            file.read((char*)&ref, sizeof(char));
        }
        else{
            pos = -1;
            ref = INVALID;
        }
    }

    int number_of_records(fstream& file, FILE_ID file_id){
        if (file_id != DATAFILE && file_id != AUXFILE)
            throw invalid_argument("file_id invalid @ number_of_records");
        if (file.is_open()){
            file.seekg(0,ios::end);
            int n = (file_id == DATAFILE) ?
                ((int) file.tellg() - sizeof(AddressType) -sizeof(char) - sizeof(bool)) /sizeof(Record):
                ((int) file.tellg() - sizeof(Record));
            file.seekg(0,ios::beg);
            return n;
        }
        return 0;
    }

    int number_of_records(string filename, FILE_ID file_id){
        fstream file(filename,ios::binary |ios::in);
        auto result = number_of_records(file,file_id);
        file.close();
        return result;
    }

    static bool compare_records(Record& r1, Record& r2){
        return r1 < r2;
    }

    bool is_empty(FILE_ID file_id){
        if (file_id = DATAFILE)
            return number_of_records(this->DATAFILE_DP,DATAFILE) == 0;
        else if(file_id == AUXFILE)
            return number_of_records(this->AUXFILE_DP,AUXFILE) == 0;
        else
            throw invalid_argument("file_id invalid @ is_empty (record)");
    }
    
public:
    SequentialFile(string DATAFILE_DP_, string AUXFILE_DP_){
        this->DATAFILE_DP = DATAFILE_DP_;
        this->AUXFILE_DP = AUXFILE_DP_;
    }

    void insert_all(vector<Record> &record){
        if (is_empty(DATAFILE)){
            sort(record.begin(), record.end(),compare_records);
            fstream file(this->DATAFILE_DP,ios::binary | ios::out);
            first_write_record_information(file,0,'d');
            for (AddressType i =0; i < record.size(); i++){
                record[i].nextDel = i + 1;
                if (i == record.size()-1)
                    record[i].ref = INVALID;
                else
                    record[i].ref = 'd';
                write_record(i,file,record[i],DATAFILE);
            }
            file.close();
        }
        else{
            for (AddressType i=0;i<record.size();i++)
                //Add a single record
        }
    }

};

#endif //