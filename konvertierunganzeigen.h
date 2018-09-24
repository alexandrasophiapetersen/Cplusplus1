#include <fstream>
using namespace std;
class ClattTokenneu
   {
private:
   int anzahlAttneu;
   char *attNameneu[10];
   char *attValueneu[10];
public:
   int getAttListneu(char *eingabe);
   char *zeigeAttNameneu(int id) {return attNameneu[id];}
   char *zeigeAttWertneu(int id) {return attValueneu[id];}
   int zahlAttneu() {return anzahlAttneu;}
   };

class ClTokenneu
   {
public:
   ClTokenneu();
   char *nameneu() { return tokenNameneu; }
   ClTokenneu *childneu() { return tokenChildneu; }
   char *inhaltneu() { return tokenInhaltneu; }
   void druckeTokenneu(int ebeneneu);
   int getTokenneu(ifstream &dateineu);
   ClattTokenneu attneu;
private:
   void cleanTokenneu();
   void druckeTokenEbeneneu(int ebeneneu);
   int fillTokenneu(int modeneu);
   char tokenNameneu[100];
   ClTokenneu *tokenChildneu;
   ClTokenneu *tokenSiblingneu;
   char *tokenInhaltneu;
   } ;

enum zustandneu { istStartTagneu, istEndTagneu } ;
