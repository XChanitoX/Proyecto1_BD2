#ifndef RECORD_H
#define RECORD_H

#include "Librerias.h"

struct RecordEdu
{
    char Gender [1]{' '};
    char Nacionalidad [25]{' '};
    char PlaceofBirth [25]{' '};
    char StageID [15]{' '};
    char GradeID [4]{' '};
    char SectionID [1]{' '};
    char Topic [15]{' '};
    char Semester [1]{' '};
    char Relation [10]{' '};
    int raisedhands;
    int visitedResources;
    int announcements;
    int discussion;
    char parentAnswer [3]{' '};
    char parentSchool [4]{' '};
    char studentAbsent [7]{' '};
    char clase [1]{' '};
    int NextDel;
    char ref;
    //int dir=-1;
    //char file = 'd';
};

struct RecordState{

};

#endif // RECORD_H
