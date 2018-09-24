#include <iostream>
#include <fstream>
#include <string>
#include "main.h"
#include "konvertierunganzeigen.h"
using namespace std;
int anzeigen()
{
    char dateiname[100];
    ifstream eingabe;
    ClTokenneu *tokenneu;

    cout << "Bitte geben Sie den Dateinamen der konvertierten XML-Datei inklusive Suffix (.xml) an. " << endl;
    cin >> dateiname;
    eingabe.open(dateiname);

    tokenneu=new ClTokenneu;
   if (tokenneu->getTokenneu(eingabe)!=0) tokenneu->druckeTokenneu(1);

eingabe.close();
return 0;
}


int ClattTokenneu::getAttListneu(
char                      *eingabe)
{
char puffer[100];
int zaehler;
enum zustandneu { zwischenTagsneu, inNamenneu, erwarteAttributNamenneu, erwarteAttributWertneu,
               verarbeiteAttributWertneu} ;
enum zustandneu zustand;

for (zaehler=0,zustand=inNamenneu,anzahlAttneu=0;*eingabe!='\0';
     eingabe = eingabe + 1)
    {
   switch(*eingabe)
      {
   case ' ':
      if (zustand == inNamenneu)
         {
         zustand = erwarteAttributNamenneu;
         *eingabe='\0';
         zaehler=0;
         }
      else if (zustand == verarbeiteAttributWertneu)
         {
         puffer[zaehler] = *eingabe;
         zaehler++;
         }
      break;

   case '=':
      if (zustand == erwarteAttributNamenneu)
         {
         zustand = erwarteAttributWertneu;
         puffer[zaehler] = '\0';
         attNameneu[anzahlAttneu] = new char[zaehler+1];
         strcpy(attNameneu[anzahlAttneu],puffer);
         zaehler=0;
         }
      else if (zustand == verarbeiteAttributWertneu)
         {
         puffer[zaehler] = *eingabe;
         zaehler++;
         }
      else cout << "Fehlerhaftes Zeichen! '='" << endl;
      break;

   case '"':
      if (zustand == erwarteAttributWertneu)
         {
         zustand = verarbeiteAttributWertneu;
         zaehler = 0;
         }
      else if (zustand == verarbeiteAttributWertneu)
         {
         zustand = erwarteAttributNamenneu;
         puffer[zaehler] = '\0';
         attValueneu[anzahlAttneu] = new char[zaehler+1];
         strcpy(attValueneu[anzahlAttneu],puffer);
         zaehler=0;
         anzahlAttneu++;
         }
      else cout << "Fehlerhaftes Zeichen! '\"'" << endl;
      break;

   default:
         puffer[zaehler] = *eingabe;
         zaehler++;
      break;
      }
   }

return 1;
}


//von der Datei tokenlib.cpp
ClTokenneu::ClTokenneu()
{
*tokenNameneu='\0';
tokenChildneu=NULL;
tokenSiblingneu=NULL;
tokenInhaltneu=new char[1];
*tokenInhaltneu='\0';
}

int  ClTokenneu::getTokenneu(
ifstream              &dateineu)
{
int zaehler;
enum zustandneu zustand;
char zeichen;
char puffer[100];
ClTokenneu *childneu;

cleanTokenneu();

for (zaehler=0;;)
    {
    dateineu.get(zeichen);
    if (dateineu.eof())
       {
       if (*tokenNameneu == '\0' && tokenChildneu == NULL && tokenInhaltneu == NULL)
          return fillTokenneu(0);
       return fillTokenneu(1);
       }
    switch(zeichen)
       {
    case '<':
       dateineu.get(zeichen);
       if (zeichen=='/')
          {
          zustand = istEndTagneu;
          if (zaehler!=0)
             {
             puffer[zaehler]='\0';
             tokenInhaltneu = new char[zaehler+1];
             strcpy(tokenInhaltneu,puffer);
             }
          }
       else
          {
          dateineu.putback(zeichen);
          if (*tokenNameneu!='\0')
             {
             dateineu.putback('<');
         if (tokenChildneu==NULL)
            {
                tokenChildneu=new ClTokenneu;
                if (tokenChildneu->getTokenneu(dateineu)==0) return fillTokenneu(0);
        }
         else
            {
        for (childneu=tokenChildneu;;childneu=childneu->tokenSiblingneu)
            {
            if (childneu->tokenSiblingneu==NULL)
               {
               childneu->tokenSiblingneu=new ClTokenneu;
                       if (childneu->tokenSiblingneu->getTokenneu(dateineu)==0)
                  return fillTokenneu(0);
               break;
               }
            }
        }
             }
          else zustand=istStartTagneu;
          }
       zaehler=0;
       break;
    case '>':
       puffer[zaehler]='\0';
       if (zustand==istEndTagneu)
          {
      if (strcmp(tokenNameneu,puffer))
         {
         cout << "Fehlerhaftes End Tag" << endl;
         cout << "Erhalten: '" << puffer << "'; erwartet: '"
              << tokenNameneu << "'" << endl;
             return fillTokenneu(0);
         }
      return fillTokenneu(1);
      }
       if (zustand==istStartTagneu)
          {
          attneu.getAttListneu(puffer);
          strcpy(tokenNameneu,puffer);
          }
       zaehler=0;
       break;
    case '\n':
       break;
    default:
       puffer[zaehler]=zeichen;
       zaehler++;
       break;
       }
    }
}

int ClTokenneu::fillTokenneu(
int                    mode)
{
if (*tokenNameneu=='\0')
   strcpy(tokenNameneu,"Unbekanntes Element");
if (tokenInhaltneu==NULL)
   {
   tokenInhaltneu=new char[1];
   *tokenInhaltneu='\0';
   }

return mode;
}

void ClTokenneu::cleanTokenneu(void)
{
*tokenNameneu='\0';
if (tokenChildneu!=NULL)
   {
   delete tokenChildneu;
   tokenChildneu=NULL;
   }
if (tokenInhaltneu!=NULL)
   {
   delete tokenInhaltneu;
   tokenInhaltneu=NULL;
   }
}


void ClTokenneu::druckeTokenneu(
int                       ebeneneu)
{
ClTokenneu *childneu;

druckeTokenEbeneneu(ebeneneu);
cout << nameneu() << " - " << inhaltneu() << endl;
if (attneu.zahlAttneu() > 0)
   {
   for (int i=0;i<attneu.zahlAttneu();i++)
       {
       druckeTokenEbeneneu(ebeneneu);
       cout << "Attribut " << attneu.zeigeAttNameneu(i) << " hat den Wert "
            << attneu.zeigeAttWertneu(i) << endl;
       }
   }
if (tokenChildneu!=NULL) tokenChildneu->druckeTokenneu(ebeneneu+1);
if (tokenSiblingneu!=NULL) tokenSiblingneu->druckeTokenneu(ebeneneu);
}

void ClTokenneu::druckeTokenEbeneneu(
int                            ebeneneu)
{
while (ebeneneu > 0)
      {
      ebeneneu = ebeneneu - 1;
      }
}

