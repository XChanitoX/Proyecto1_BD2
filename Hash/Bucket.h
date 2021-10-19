#ifndef HASHINDEX_BUCKET_H
#define HASHINDEX_BUCKET_H
#include <iostream>
#include <algorithm>
#define BLOCKFACTOR 10

/// M >= (n/fb)*(1+d) --> cantidad de buckets

using namespace std;

template<class Record, class Key>
class Bucket {
private:
    Record arrayRecords[BLOCKFACTOR];
    int nextBucket;
    int count;
    int nextDel;

public:
    Bucket();
    Bucket(int _nextBucket_);
    Bucket(Record *arrayRecords);

    int getNextBucket() const;
    int getNextDel();
    void setNextBucket(int nextBucket);
    void addRecord(Record record);
    void setRecords(vector<Record> vector);
    void sortBucket();
    bool isFull();
    bool isEmpty();
    bool compareRecords(Record& recordA, Record& recordB);
    vector<Record> getRecords();
};
#endif //HASHINDEX_BUCKET_H
