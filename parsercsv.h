#include <fstream>
using namespace std;
class Parser //Orientierung an Klasse des XML Parsers ClattToken
{

public:
    void parserCSV(ifstream&);
    int csvreader;
    void zeigeCSV();
    char *zeigeKennzeichen(int id) {return sendungskennzeichen[id];};
    char *zeigeStaffel(int id) {return staffel[id];};
    char *zeigeEpisoden(int id) {return episoden[id];};


private:
    char *sendungskennzeichen[50];
    char *staffel[50];
    char *episoden[50];

};
