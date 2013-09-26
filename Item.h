#ifndef ITEM_H
#define ITEM_H

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

class Item
{
    private:
        string id, nom, armure, endu, intel, esprit, agi, force;
        char qualite;

        void accentWin(string &texte);
        #ifdef _WIN32
        void color(int t, int f);
        #endif

    public:
        Item();
        ~Item();

        void afficher();

        //Nous c'est le gout ou la ref
        void setId(const string &_id);
        void setNom(const string &_nom);
        void setArmure(const string &_armure);
        void setEndu(const string &_endu);
        void setIntel(const string &_intel);
        void setEsprit(const string &_esprit);
        void setAgi(const string &_agi);
        void setForce(const string &_force);
        void setQualite(const char &_qualite);

        const string& getId() const;
        const string& getNom() const;
        const string& getArmure() const;
        const string& getEndu() const;
        const string& getIntel() const;
        const string& getEsprit() const;
        const string& getAgi() const;
        const string& getForce() const;
        const char& getQualite() const;
};

#endif // ITEM_H
