#include "Http.h"

#include "Item.h"

Http::Http(const string &_host)
{
    http.setHost(_host);
}

Http::~Http()
{
}

void Http::parse(const string &html, Item *item)
{
    unsigned int i;
    string position = "var g_pageInfo = {type: 3, typeId: ", tampon;

    if(string::npos != (i = html.find(position)))
    {
        i += position.size();

        while(html[i] != ',') //Recup id
        {
            tampon.push_back(html[i]);
            i++;
        }
        item->setId(tampon);
        tampon.clear();

        i+=9; //on passe name ...
        while(html[i] != '}')//Recup nom
        {
            tampon.push_back(html[i]);
            i++;
        }
        tampon.pop_back(); //on enleve le ' a la fin //popback c++11

        accent(tampon); //On vire la merde codé sur 2 octets
        item->setId(tampon);
        tampon.clear();

        position = "class=\"q";
        if(string::npos != (i = html.find(position)))//Recherche la qualité de lobjet
        {
            item->setQualite(html[i + position.size()]);
        }

        position = "Armure<br />";
        if(string::npos != (i = html.find(position)))//Recherche Armure
        {
            while(html[i] != '>')//Placement au debut
            {
                i--;
            }
            while(html[i] != ' ')//Placement au debut
            {
                tampon.push_back(html[i+1]);
                i++;
            }
            accent(tampon); //On vire la merde codé sur 2 octets
            item->setArmure(tampon);
            tampon.clear();
        }
        else
        {
            item->setArmure("0");
        }

        position = "Intelligence<br />";
        if(string::npos != (i = html.find(position)))//Recherche intel
        {
            while(html[i] != '>')//Placement au debut
            {
                i--;
            }
            while(html[i] != ' ')//Recupération
            {
                tampon.push_back(html[i+1]);
                i++;
            }
            accent(tampon); //On vire la merde codé sur 2 octets
            item->setIntel(tampon);
            tampon.clear();
        }
        else
        {
            item->setIntel("0");
        }

        position = "Endurance<br />";
        if(string::npos != (i = html.find(position)))//Recherche Endurance
        {
            while(html[i] != '>')//Placement au debut
            {
                i--;
            }
            while(html[i] != ' ')//Recupération
            {
                tampon.push_back(html[i+1]);
                i++;
            }
            accent(tampon); //On vire la merde codé sur 2 octets
            item->setEndu(tampon);
            tampon.clear();
        }
        else
        {
            item->setEndu("0");
        }

        position = "Esprit<br />";
        if(string::npos != (i = html.find(position)))//Recherche Esprit
        {
            while(html[i] != '>')//Placement au debut
            {
                i--;
            }
            while(html[i] != ' ')//Recupération
            {
                tampon.push_back(html[i+1]);
                i++;
            }
            accent(tampon); //On vire la merde codé sur 2 octets
            item->setEsprit(tampon);
            tampon.clear();
        }
        else
        {
            item->setEsprit("0");
        }

        position = "Force<br />";
        if(string::npos != (i = html.find(position)))//Recherche Esprit
        {
            while(html[i] != '>')//Placement au debut
            {
                i--;
            }
            while(html[i] != ' ')//Recupération
            {
                tampon.push_back(html[i+1]);
                i++;
            }
            accent(tampon); //On vire la merde codé sur 2 octets
            item->setForce(tampon);
            tampon.clear();
        }
        else
        {
            item->setForce("0");
        }

        position = "Agilit";
        position+=0xffffffc3;//é //Overtamére à changer signed unsigned
        position+=0xffffffa9;
        position+="<br />";
        if(string::npos != (i = html.find(position)))//Recherche Agilité
        {
            while(html[i] != '>')//Placement au debut
            {
                i--;
            }
            while(html[i] != ' ')//Recupération
            {
                tampon.push_back(html[i+1]);
                i++;
            }
            accent(tampon); //On vire la merde codé sur 2 octets
            item->setAgi(tampon);
            tampon.clear();
        }
        else
        {
            item->setAgi("0");
        }
    }
}


void Http::accent(string &texte) //A mettre dans classe utilitaire stat
{
    #ifdef _WIN32
    unsigned int i = 0;

    while(i < texte.size())
    {
        switch(texte[i])
        {
            case 0xffffffa2://â a2
            {
                CharToOemA("â", &texte[i-1]);

                texte.erase(i, 1);
                i--;
                break;
            }
            case 0xffffffa9://é a9
            {
                CharToOemA("é", &texte[i-1]);

                texte.erase(i, 1);
                i--;
                break;
            }
            case 0x5c:// / 5c
            {
                texte.erase(i, 1);
                i--;
                break;
            }
            case 0xffffffc2:// espace ? c2
            {
                texte[i+1] = ' ';
                texte.erase(i, 1);
                i--;
                break;
            }
            case 0xffffffbb: //û bb
            {
                CharToOemA("û", &texte[i-1]);

                texte.erase(i, 1);
                i--;
                break;
            }
            case 0xffffffa8: //è a8
            {
                CharToOemA("è", &texte[i-1]);

                texte.erase(i, 1);
                i--;
                break;
            }
            case 0xffffffb4: //ô b4
            {
                CharToOemA("ô", &texte[i-1]);

                texte.erase(i, 1);
                i--;
                break;
            }
            case 0xffffffaf: //ï b4af 3735
            {
                CharToOemA("ï", &texte[i-1]);

                texte.erase(i, 1);
                i--;
                break;
            }
            case 0xffffffa0: //à a0
            {
                CharToOemA("à", &texte[i-1]);

                texte.erase(i, 1);
                i--;
                break;
            }
            case 0xffffffaa: //ê aa
            {
                CharToOemA("ê", &texte[i-1]);

                texte.erase(i, 1);
                i--;
                break;
            }
            case 0xffffffae: //î ae
            {
                CharToOemA("î", &texte[i-1]);

                texte.erase(i, 1);
                i--;
                break;
            }
            case 0xffffffe2: // ' e2
            {
                CharToOemA("'", &texte[i]);

                texte.erase(i+1 , 2);
                i-=2;
                break;
            }
            case 0xffffffa7: // ç a7
            {
                CharToOemA("ç", &texte[i-1]);

                texte.erase(i, 1);
                i--;
                break;
            }
            case 0xffffff93: // oe c5
            {
                texte[i-1] = 'o';
                texte[i] = 'e';
                break;
            }
        }
        i++;
    }
    #endif
}
