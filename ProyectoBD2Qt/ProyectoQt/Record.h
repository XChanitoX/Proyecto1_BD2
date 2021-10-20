#ifndef RECORD_H
#define RECORD_H

#include "Librerias.h"

struct RecordEdu
{
    char ID [10]{' '};
    char Gender [10]{' '};
    char Nacionalidad [25]{' '};
    char PlaceofBirth [25]{' '};
    char StageID [15]{' '};
    char GradeID [10]{' '};
    char SectionID [10]{' '};
    char Topic [15]{' '};
    char Semester [10]{' '};
    char Relation [10]{' '};
    char raisedhands [10]{' '};
    char visitedResources [10]{' '};
    char announcements [10]{' '};
    char discussion [10]{' '};
    char parentAnswer [10]{' '};
    char parentSchool [10]{' '};
    char studentAbsent [10]{' '};
    char clase [10]{' '};

    int nextDel;
    char ref;

    RecordEdu() = default;
    RecordEdu(string ID, string Gender, string Nacionalidad, string PlaceofBirth, string StageID, string GradeID, string SectionID, string topic, string semester, string relation, string raisedhands, string visitedResources, string announcements, string discussions, string parentAnswer, string parentSchool, string studentAbsent, string clase){


        strcpy(this->ID, ID.c_str());
        strcpy(this->Gender, Gender.c_str());
        strcpy(this->Nacionalidad, Nacionalidad.c_str());
        strcpy(this->PlaceofBirth, PlaceofBirth.c_str());
        strcpy(this->StageID, StageID.c_str());
        strcpy(this->GradeID, GradeID.c_str());
        strcpy(this->SectionID, SectionID.c_str());
        strcpy(this->Topic, topic.c_str());
        strcpy(this->Semester, semester.c_str());
        strcpy(this->Relation, relation.c_str());
        strcpy(this->raisedhands, raisedhands.c_str());
        strcpy(this->visitedResources, visitedResources.c_str());
        strcpy(this->announcements, announcements.c_str());
        strcpy(this->discussion, discussions.c_str());
        strcpy(this->parentAnswer, parentAnswer.c_str());
        strcpy(this->parentSchool, parentSchool.c_str());
        strcpy(this->studentAbsent, studentAbsent.c_str());
        strcpy(this->clase, clase.c_str());

        this->nextDel = 0;
        this->ref = 'd';

    }

    const char* get_key()const{
        return GradeID;
    }

    bool equal_key(const char* key){
        return strcmp(this->GradeID, key) == 0;
    }

    bool less_than_key(const char* key){
        return strcmp(this->GradeID, key) < 0;
    }

    bool greater_than_key(const char* key){
        return strcmp(this->GradeID, key) > 0;
    }

    bool less_or_equal(const char* key){
        return strcmp(this->GradeID, key) <= 0;
    }

    bool greater_or_equal(const char* key){
        return strcmp(this->GradeID, key) >= 0;
    }

    bool operator < (RecordEdu& other){
        return strcmp(this->GradeID, other.GradeID) < 0;
    }

    bool operator == (RecordEdu& other){
        return strcmp(this->GradeID, other.GradeID) == 0;
    }


};

struct RecordState{

};

#endif // RECORD_H
