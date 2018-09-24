#include "parsercsv.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Der CSV Parser orientiert sich an ClElement *verarbeite(ifstream& datei) von Beispiel 7: Objekte und Rekursion (http://hki.uni-koeln.de/beispiel-7-2/)
// und den Zuständen des XML Parsers.
int zeigecsv (){

    ifstream csvdatei;
    csvdatei.open("sendungsliste.csv");
    Parser *prs;
    prs = new Parser();
    prs->parserCSV(csvdatei);
    prs->zeigeCSV();

   csvdatei.close();

   return 0;

}


void Parser::parserCSV(ifstream& prs){
    char zeichen;
    char puffer[100];
    int counter=0;
    enum zustandCSV {parseSendungskennzeichen, parseStaffel, parseEpisoden};
    enum zustandCSV zustand = parseSendungskennzeichen;

    for(prs.get(zeichen); !prs.eof(); prs.get(zeichen)){  //aus Beispiel 7
        switch(zeichen){

        case ',':
            if (zustand==parseSendungskennzeichen){    //Aufbau der Zustände wie in XML Parser.(siehe case '='.
                zustand = parseStaffel;
                puffer[counter]='\0';
                sendungskennzeichen[csvreader] = new char[counter+1];
                strcpy(sendungskennzeichen[csvreader],puffer);
                counter=0;
            }

            else if (zustand==parseStaffel){
                zustand = parseEpisoden;
                puffer[counter]='\0';
                staffel[csvreader] = new char[counter+1];
                strcpy(staffel[csvreader],puffer);
                counter=0;
            }

            break;

        case '\n':
            zustand = parseSendungskennzeichen;
            puffer[counter]='\0';
            episoden[csvreader] = new char[counter+1];
            strcpy(episoden[csvreader],puffer);
            counter=0;
            csvreader++;

            break;

        default:
            puffer[counter] = zeichen;
            counter++;
            break;
        }
    }
}

void Parser::zeigeCSV(){
    for (int i=0; i<csvreader; i++){
        cout << "Neuer Datensatz:" <<endl;
        cout << "Sendungskennzeichen: " << zeigeKennzeichen(i) << endl;
        cout << "Staffel: " << zeigeStaffel(i) << endl;
        cout << "Episodenanzahl: " << zeigeEpisoden(i) << endl;
    }
}
