#include "Bucket.h"

template<class Record, class Key>
Bucket<Record, Key>::Bucket():nextBucket(-1), count(0), nextDel(0) {}


template<class Record, class Key>
Bucket<Record, Key>::Bucket(int _nextBucket_):nextBucket(_nextBucket_), count(0), nextDel(0) {}


template<class Record, class Key>
int Bucket<Record, Key>::getNextBucket(){
    return nextBucket;
}

template<class Record, class Key>
int Bucket<Record, Key>::getNextDel(){
    return nextDel;
}

template<class Record, class Key>
void Bucket<Record, Key>::setNextBucket(int nextBucket) {
    Bucket::nextBucket = nextBucket;
}

template<class Record, class Key>
void Bucket<Record, Key>::addRecord(Record record){

}

template<class Record, class Key>
void Bucket<Record, Key>::sortBucket(){
    sort(arrayRecords, arrayRecords+count, compareRecords());
}

template<class Record, class Key>
void  Bucket<Record, Key>::setRecords(vector<Record> vector){
    count = 0;
    for(count = 0; count<vector.size(); count++)
        arrayRecords[count]=vector[count];
}

template<class Record, class Key>
bool Bucket<Record, Key>::isFull(){
    return count==BLOCKFACTOR;
}

template<class Record, class Key>
bool Bucket<Record, Key>::isEmpty(){
    return count==0;
}

template<class Record, class Key>
bool Bucket<Record, Key>::compareRecords(Record &recordA, Record &recordB) {
    return recordA<recordB;
}
template<class Record, class Key>
vector<Record> Bucket<Record, Key>::getRecords(){
    return vector<Record>(arrayRecords, arrayRecords+count);
}






