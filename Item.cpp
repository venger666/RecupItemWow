#include "Item.h"

Item::Item()
{
}

Item::~Item()
{
}

void Item::afficher()
{
    std::cout << "Id : " << id << " Nom : " ;

    #ifdef _WIN32
    switch(qualite)
    {
        case '0'://gris
        {
            color(8, 0);
            break;
        }
        case '1'://blanc
        {
            color(15, 0);
            break;
        }
        case '2'://vert
        {
            color(2, 0);
            break;
        }
        case '3'://bleu
        {
            color(9, 0);
            break;
        }
        case '4'://epique
        {
            color(5, 0);
            break;
        }
    }
    #endif

    std::cout << nom << std::endl;

    #ifdef _WIN32
    color(7, 0);
    #endif

    std::cout << "Armure : " << armure << " Intel : " << intel << " Endu : " << endu
              << " Force : " << force << " Agi : " << agi << " Esprit : " << esprit << std::endl << std::endl;
}

#ifdef _WIN32
void Item::color(int t, int f)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
}
#endif


//Setter
void Item::setId(const string &_id)
{
    id = _id;
}

void Item::setNom(const string &_nom)
{
    nom = _nom;
}

void Item::setArmure(const string &_armure)
{
    armure = _armure;
}

void Item::setEndu(const string &_endu)
{
    endu = _endu;
}

void Item::setIntel(const string &_intel)
{
    intel = _intel;
}

void Item::setEsprit(const string &_esprit)
{
    esprit = _esprit;
}

void Item::setAgi(const string &_agi)
{
    agi = _agi;
}

void Item::setForce(const string &_force)
{
    force = _force;
}

void Item::setQualite(const char &_qualite)
{
    qualite = _qualite;
}

//Getter
const string& Item::getId() const
{
    return id;
}

const string& Item::getNom() const
{
    return nom;
}

const string& Item::getArmure() const
{
    return armure;
}

const string& Item::getEndu() const
{
    return endu;
}

const string& Item::getIntel() const
{
    return intel;
}

const string& Item::getEsprit() const
{
    return esprit;
}

const string& Item::getAgi() const
{
    return agi;
}

const string& Item::getForce() const
{
    return force;
}

const char& Item::getQualite() const
{
    return qualite;
}
