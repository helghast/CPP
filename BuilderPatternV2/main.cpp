/**
https://sourcemaking.com/design_patterns/builder/java/2
Intent
Separate the construction of a complex object from its representation so that the same construction process can create different representations.
Parse a complex representation, create one of several targets.

Problem
An application needs to create the elements of a complex aggregate. The specification for the aggregate exists on secondary storage and one of many representations needs to be built in primary storage.

Check list
-Decide if a common input and many possible representations (or outputs) is the problem at hand.
-Encapsulate the parsing of the common input in a Reader class.
-Design a standard protocol for creating all possible output representations. Capture the steps of this protocol in a Builder interface.
-Define a Builder derived class for each target representation.
-The client creates a Reader object and a Builder object, and registers the latter with the former.
-The client asks the Reader to “construct”.
-The client asks the Builder to return the result.

Discussion
The forte of Builder is constructing a complex object step by step. An abstract base class declares the standard construction process, and concrete derived classes define the appropriate implementation for each step of the process. In this example, "distributed work packages" have been abstracted to be persistent and platform independent.

This means that the platform-specific mechanism for implementing files, queues, and concurrency pathways is defined in each platform's concrete derived class. A single "reader" object (i.e. parser) retrieves the archived specification for a DistrWorkPackage and proceeds to delegate each build step to the builder object that was registered by the client. Upon completion, the client retrieves the end result from the builder. */

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

#define NUM_ENTRIES 6
#define PERSISTENCE_VALUES 30
#define DISTR_DESC 200
#define DISTR_TEMP 80

enum PersistenceType{ File, Queue, Pathway };

struct PersistenceAttribute{
    PersistenceType type;
    char value[PERSISTENCE_VALUES];
};

class DistrWorkPackage{
public:
    DistrWorkPackage(char* type){sprintf(desc, "Distributed Work Package for: %s", type);}
    void setFile(char* f, char* v){
        sprintf(temp, "\n File(%s): %s", f, v);
        strcat(desc, temp);
    }
    void setQueue(char* q, char *v){
        sprintf(temp, "\n Queue(%s): %s", q, v);
        strcat(desc, temp);
    }
    void setPathway(char* p, char *v){
        sprintf(temp, "\n Pathway(%s): %s", p, v);
        strcat(desc, temp);
    }
    const char* getState(){ return desc; }
private:
    char desc[DISTR_DESC], temp[DISTR_TEMP];
};

class Builder{
public:
    virtual void configureFile(char*) = 0;
    virtual void configureQueue(char*) = 0;
    virtual void configurePathway(char*) = 0;
    DistrWorkPackage* getResult(){return result;}
protected:
    DistrWorkPackage* result;
};

class UnixBuilder : public Builder{
public:
    UnixBuilder(){ result = new DistrWorkPackage("Unix");}
    void configureFile(char* name){result->setFile("flatFile", name);}
    void configureQueue(char* queue){result->setQueue("FIFO", queue);}
    void configurePathway(char* type){result->setPathway("thread", type);}
};

class VmsBuilder : public Builder{
public:
    VmsBuilder(){ result = new DistrWorkPackage("Vms");}
    void configureFile(char* name){result->setFile("ISAM", name);}
    void configureQueue(char* queue){result->setQueue("priority", queue);}
    void configurePathway(char* type){result->setPathway("LWP", type);}
};

class Reader{
public:
    void setBuilder(Builder* b){builderPtr = b;}
    void construct(PersistenceAttribute list[], const int num){
        for(int i = 0; i < num; ++i){
            switch(list[i].type){
                case PersistenceType::File: {builderPtr->configureFile(list[i].value); break;}
                case PersistenceType::Queue: {builderPtr->configureQueue(list[i].value); break;}
                case PersistenceType::Pathway: {builderPtr->configurePathway(list[i].value); break;}
            }
        }
    };
private:
    Builder* builderPtr;
};

PersistenceAttribute input[NUM_ENTRIES]{
    {File, "state.dat"}, {File, "config.sys"}, {Queue, "compute"}, {Queue, "log"}, {Pathway, "authentication"}, {Pathway, "error processing"}
};

int main()
{
    UnixBuilder uBuilder;
    VmsBuilder vBuilder;

    Reader rObj;

    rObj.setBuilder(&uBuilder);
    rObj.construct(input, NUM_ENTRIES);
    cout << uBuilder.getResult()->getState() << endl;

    rObj.setBuilder(&vBuilder);
    rObj.construct(input, NUM_ENTRIES);
    cout << vBuilder.getResult()->getState() << endl;

    return 0;
}
