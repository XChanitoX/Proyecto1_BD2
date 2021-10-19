#ifndef SEQUENTIAL_FILE_H
#define SEQUENTIAL_FILE_H

#include "../Librerias.h"
#define AddressType int32_t
#define INVALID 'x'
#define MAX_CAPACITY 10

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

    void first_write_record_data(fstream& file, AddressType pos, char ref){
        if (!file.is_open())
            throw out_of_range("File not open @ first_write_record_data");
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

    void first_read_record_data(fstream& file, AddressType pos, char ref){
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
        auto n = number_of_records(file,file_id);
        file.close();
        return n;
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

    bool is_full(){
        if (number_of_records(this->AUXFILE_DP,AUXFILE) == MAX_CAPACITY)
            return true;
        return false;
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
            first_write_record_data(file,0,'d');
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
                add_record(record[i]);
        }
    }

    void add_record(Record record){
        if (is_empty(DATAFILE_DP)){
            fstream file(this->DATAFILE_DP, ios::binary | ios::out);
            record.nextDel = 1;
            record.ref = INVALID;
            first_write_record_data(file, 0, 'd');
            write_record(0, file, record, DATAFILE);
            file.close();
            return;
        }
        if (is_full()){
            // rebuild aux file if full
        }
        fstream file(this->DATAFILE_DP,ios::binary | ios::in | ios:out);
        file.close();
    }

    pair<RecordData,RecordData> sequential_search(Key key){
        fstream dataFile(this->DATAFILE_DP,ios::binary | ios::in);
        fstream auxFile(this->AUXFILE_DP,ios::binary | ios::in);
        AddressType curr_pos, prev_pos = -1;
        char curr_ref, prev_ref = INVALID;
        first_read_record_data(dataFile,curr_pos,curr_ref);
        Record curr_record, prev_record;
        while (curr_ref != INVALID) {
            if(curr_ref == 'd')
                read_record(curr_pos,dataFile,curr_record,DATAFILE);
            else if(curr_ref == 'a')
                read_record(curr_pos,auxFile,curr_record,AUXFILE);
            else
                throw invalid_argument("Invalid reference @ sequential_search");
            if (!curr_ref.less_than_key(key))
                break;
            prev_pos = curr_pos;
            prev_ref = curr_ref;
            prev_record = curr_record;
            curr_pos = curr_record.nextDel;
            curr_ref = curr_record.ref;
        }
        return  {RecordData(prev_pos,prev_ref,prev_record),RecordData(curr_pos,curr_ref,curr_record)};
    }
    
};

#endif //