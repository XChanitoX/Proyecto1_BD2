#include "ExtendibleHash.h"


template<class Record, class Key, class Hash>
void ExtendibleHash<Record, Key, Hash>::deleteRecordBucket(Key key, HashNode &currentNode, int nodePos){
    int curBucketPos = currentNode.getPosition();
    Bucket<Record, Key> bucket = bucketFile.readRecord(curBucketPos);
    vector<Record> differentRecords = bucket.getAllDifferentRecords(key);
    bucket.setRecords(differentRecords);
    bucketFile.writeRecord(curBucketPos, bucket);

    if(bucket.isEmpty() && bucket.getNextBucket() != -1){
        currentNode.getPosition() = bucket.getNextBucket();
        bucketFile.deleteRecord(curBucketPos);
        indexFile.writeRecord(currentNode,nodePos);
        deleteRecordInBucket(key, currentNode, nodePos);
    }
}

template<class Record, class Key, class Hash>
void ExtendibleHash<Record, Key, Hash>::initializerValues() {
    HashNode root(1,2), A(0), B(1);
    Bucket<Record, Key> bucket1, bucket2;
    bucketFile.addRecord(bucket1);
    bucketFile.addRecord(bucket2);
    indexFile.addRecord(root);
    indexFile.addRecord(A);
    indexFile.addRecord(B);
}

template<class Record, class Key, class Hash>
vector<Record> ExtendibleHash<Record, Key, Hash>::scanAll(){
    int numBuckets = bucketFile.length();
    vector<Record> result;
    for(int i=0; i<numBuckets; i++){
        Bucket<Record, Key> temp = bucketFile.readRecord(i);
        if(temp.getNextDel()==-1)
            continue;
        for(auto& item: temp.getRecords())
            result.push_back(item);
    }
    sort(result.begin(), result.end(), Bucket<Record,Key>::compareRecords);
    return result;
}

template<class Record, class Key, class Hash>
void ExtendibleHash<Record, Key, Hash>::setValues(vector<Record> records) {
    if(bucketFile.length()==0)
        initializerValues();
    for(auto& record: records)
        insert(records);
}

template<class Record, class Key, class Hash>
int ExtendibleHash<Record, Key, Hash>::searchNode(int nodePosition, bitset<3> key, int height){
    HashNode node = indexFile.readRecord(nodePosition);
    if(!node.isLeaf)
        if(key[height]!=0)
            return searchNode(node.right, key, ++height);
        else
            return searchNode(node.left, key, ++height);
    else
        return nodePosition;
}

template<class Record, class Key, class Hash>
vector<Record> ExtendibleHash<Record, Key, Hash>::searchRange(Key beginKey, Key endKey) {
    int numBuckets = bucketFile.length();
    vector<Record> result;
    for(int i = 0; i < numBuckets; ++i){
        Bucket<Record, Key> bucket = bucketFile.readRecord(i);
        for(auto& item : bucket.getRecords()){
            if(item.greaterThanOrEqualToKey(beginKey) && item.lessThanOrEqualToKey(endKey)) {
                result.push_back(item);
            }
        }
    }
    sort(result.begin(), result.end(), Bucket<Record, Key>::compareRecords);
    return result;
}


template<class Record, class Key, class Hash>
vector<Record> ExtendibleHash<Record, Key, Hash>::search(Key key) {
    bitset<MAXHEIGHT> hashKey = hash(key);
    int height = 0;
    int curNodePos = searchNode(0, hashKey, height);
    HashNode curNode = indexFile.readRecord(curNodePos);

    int curBucketPos = curNode.getPosition();
    vector<Record> result;
    while(curBucketPos != -1){
        Bucket<Record, Key> bucket = bucketFile.readRecord(curBucketPos);

        for(auto& item: bucket.getRecords()){
            if(item.equalToKey(key)) {
                result.push_back(item); }
        }
        //current toma el valor del siguiente bucket
        curBucketPos = bucket.getNextBucket();
    }
    return result;
}

template<class Record, class Key, class Hash>
void ExtendibleHash<Record, Key, Hash>::remove(Key key){
    int height = 0;
    remove(0, key, hash(key), height);
}

template<class Record, class Key, class Hash>
void ExtendibleHash<Record, Key, Hash>::insert(Record record) {
    if(bucketFile.length()==0) {
        initializerValues();
    }
    int height =0;
    bitset<MAXHEIGHT> hashKey = hash(record.getKey());
    int curNodePos  = searchNode(0, hashKey, height);
    HashNode curNode = indexFile.readRecord(curNodePos);
    int curBucketPos = curNode.getPosition();
    Bucket<Record, Key> bucket = bucketFile.readRecord(curBucketPos);

    if(!bucket.isFull()){
        bucket.addRecord(record);
        bucket.sortBucket();
        bucketFile.writeRecord(bucket, curBucketPos);
    }
    else {
        split(record, height, curNodePos, curNode, curBucketPos, bucket);
    }
}

template<class Record, class Key, class Hash>
void ExtendibleHash<Record, Key, Hash>::split(Record &record, int height, int curNodePos, HashNode &currentNode,
                                              int curBucketPos, Bucket<Record, Key> &bucket){
    if(height == MAXHEIGHT){
        Bucket<Record, Key> temp;
        temp.addRecord(record);
        temp.setNextBucket(curBucketPos);
        currentNode.getPosition() = bucketFile.addRecord(temp);
        indexFile.writeRecord(currentNode, curNodePos);
        return;
    }
    Bucket<Record, Key> bucket1, bucket2;
    bool splitAgain = false;
    bool splitToLeft = false;
    vector<Record> records = bucket.getRecords();
    records.push_back(record);

    for(auto& item : records){
        Bucket<Record, Key> hashKey = hash(item.getPrimaryKey());
        if(hashKey[height] == 0){
            if(!bucket1.isFull()) {
                bucket1.addRecord(item);
            }
            else{
                splitAgain = true;
                splitToLeft = true;
            }
        }
        else{
            if(!bucket2.isFull()) {
                bucket2.addRecord(item);
            }
            else {
                splitAgain = true;
            }
        }
    }
    bucketFile.deleteRecord(curBucketPos);
    bucket1.sortBucket();
    bucket2.sortBucket();
    int bucketPos1 = bucketFile.addRecord(bucket1);
    int bucketPos2 = bucketFile.addRecord(bucket2);
    HashNode leftNode(bucketPos1), rightNode(bucketPos2);
    currentNode.left = indexFile.addRecord(leftNode);
    currentNode.right = indexFile.addRecord(rightNode);
    currentNode.isLeaf = false;
    indexFile.writeRecord(currentNode,curNodePos);
    if(splitAgain){
        int splitNodePos;
        HashNode splitNode;
        if(splitToLeft) {
            splitNodePos = currentNode.left;
            splitNode = indexFile.readRecord(splitNodePos);
            split(record, height+1, splitNodePos, splitNode, bucketPos1, bucket1);
        }else{
            splitNodePos = currentNode.right;
            splitNode = indexFile.readRecord(splitNodePos);
            split(record, height+1, splitNodePos, splitNode, bucketPos2, bucket2);
        }
    }
}

template<class Record, class Key, class Hash>
void ExtendibleHash<Record, Key, Hash>::remove(int nodePos, Key key, bitset<3> hashKey, int &height){
    HashNode currentNode = indexFile.readRecord(nodePos);
    if (currentNode.isLeaf) {
        deleteRecordBucket(key, currentNode, nodePos);
        return;
    }
    if(hashKey[height] == 0) {
        remove(currentNode.left, key, hashKey, ++height);
    }
    else {
        remove(currentNode.right, key, hashKey, ++height);
    }

    if(nodePos == 0) return;
    HashNode left = indexFile.readRecord(currentNode.left);
    HashNode right = indexFile.readRecord(currentNode.right);

    if (left.isLeaf && right.isLeaf) {
        Bucket<Record, Key> bucket1 = bucketFile.readRecord(left.getPosition());
        Bucket<Record, Key> bucket2 = bucketFile.readRecord(right.getPosition());
        if (bucket1.isEmpty() && bucket2.isEmpty()) {
            bucketFile.deleteRecord(left.getPosition());
            bucketFile.deleteRecord(right.getPosition());
            indexFile.deleteRecord(currentNode.left);
            indexFile.deleteRecord(currentNode.right);
            Bucket<Record, Key> tempBucket;
            currentNode.isLeaf = true;
            currentNode.getPosition() = bucketFile.addRecord(tempBucket);
            indexFile.writeRecord(currentNode,nodePos);
        }
    }
}
