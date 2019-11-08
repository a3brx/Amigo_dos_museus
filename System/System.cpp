#include "System.h"

using namespace std;

System::System(string fileName) {
    this->fileName=fileName;
    ifstream file;
    string namemuseus , namecards, nameevents;
    file.open(fileName);
    getline(file,nameevents);
    getline(file,namecards);
    getline(file,namemuseus);
    file.close();
    Card *c;
    Museum m;
    file.open(namemuseus);
    while(!file.eof()){

        file>>m;
        this->museums.push_back(new Museum(m));
    }

    while(!file.eof()){
        int type;
        file>>type;
        switch (type) {
            case 0:
                file>>*c;
                this->cards.push_back(new IndividualCard(c));


        }

    }
    while(!file.eof()){
        Event e;
        file>>e;
        this->museums.push_back(new m);
    }
}
