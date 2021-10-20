#ifndef HASHINDEX_EXTENDIBLEHASH_H
#define HASHINDEX_EXTENDIBLEHASH_H
#include <iostream>
#include <cstring>
#include <fstream>
#include <functional>
#include <bitset>
#include "Bucket.h"
#include "FreeList.h"
#define MAXHEIGHT 3

using namespace std;

struct HashNode{
private:
    int position;
public:
    int left, right;
    int nextDel=0;
    bool isLeaf=true;

    HashNode();
    HashNode(int _left_, int _right_):left(_left_), right(_right_), isLeaf(false){}
    HashNode(int _position_):position(_position_){}
    int getPosition(){
        if(!isLeaf){
            cout<<"This node isnt a leaf!"<<endl;
            throw new exception;
        }
        return this->position;
    }
    void setPosition(int _position_){
        if(!isLeaf){
            cout<<"This node isnt a leaf!"<<endl;
            throw new exception;
        }
        this->position = _position_;
    }
};

template<class Record, class Key, class Hash=hash<Key>>
class ExtendibleHash{
private:
    FreeList<Bucket<Record, Key>> bucketFile;
    FreeList<HashNode> indexFile;
    Hash hash;
public:
    ExtendibleHash(){};
    ExtendibleHash(string indexFileName, string bucketFileName){
        bucketFile.setFileName(bucketFileName);
        indexFile.setFileName(indexFileName);
    }

    vector<Record> scanAll();
    vector<Record> searchRange(Key beginKey, Key endKey);
    vector<Record> search(Key key);
    int searchNode(int nodePosition, bitset<MAXHEIGHT> key, int height);
    void initializerValues();
    void setValues(vector<Record> records);
    void remove(Key key);
    void insert(Record record);
    void split(Record& record, int height, int curNodePos, HashNode& currentNode, int curBucketPos, Bucket<Record, Key>& bucket);
    void remove(int nodePos, Key key, bitset<MAXHEIGHT> hashKey, int& height);
    void deleteRecordBucket(Key key, HashNode &currentNode, int nodePos);

};
#endif //HASHINDEX_EXTENDIBLEHASH_H
