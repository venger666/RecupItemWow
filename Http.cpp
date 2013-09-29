#include "Http.h"

#include "Item.h"

Http::Http()
{
    http.setHost("http://nostalgeek-serveur.com");
}

Http::~Http()
{
}

bool Http::process(Item *item, int id)
{
    string page;

    if(recupPage(page, id))
    {
        parse(page, item);

        return true;
    }
    else
    {
        return false;
    }
}

bool Http::recupPage(string &html, int id)
{
    // cr�er un flux de sortie int en string
    std::ostringstream nombre;
    nombre << id;

    sf::Http::Request request("db/?item="+nombre.str());
    // Send the request
    sf::Http::Response response = http.sendRequest(request);
    sf::Http::Response::Status status = response.getStatus();

    if (status == sf::Http::Response::Ok)
    {
        if(response.getBody().size() != 5212) //Taille page id item invalide
        {
            html = response.getBody();

            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        std::cout << "Error " << status << std::endl;
        return false;
    }
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

        accent(tampon); //On vire la merde cod� sur 2 octets
        item->setNom(tampon);
        tampon.clear();

        position = "class=\"q";
        if(string::npos != (i = html.find(position)))//Recherche la qualit� de lobjet
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
            accent(tampon); //On vire la merde cod� sur 2 octets
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
            while(html[i] != ' ')//Recup�ration
            {
                tampon.push_back(html[i+1]);
                i++;
            }
            accent(tampon); //On vire la merde cod� sur 2 octets
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
            while(html[i] != ' ')//Recup�ration
            {
                tampon.push_back(html[i+1]);
                i++;
            }
            accent(tampon); //On vire la merde cod� sur 2 octets
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
            while(html[i] != ' ')//Recup�ration
            {
                tampon.push_back(html[i+1]);
                i++;
            }
            accent(tampon); //On vire la merde cod� sur 2 octets
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
            while(html[i] != ' ')//Recup�ration
            {
                tampon.push_back(html[i+1]);
                i++;
            }
            accent(tampon); //On vire la merde cod� sur 2 octets
            item->setForce(tampon);
            tampon.clear();
        }
        else
        {
            item->setForce("0");
        }

        position = "Agilit";
        position+=0xffffffc3;//� //Overtam�re � changer signed unsigned
        position+=0xffffffa9;
        position+="<br />";
        if(string::npos != (i = html.find(position)))//Recherche Agilit�
        {
            while(html[i] != '>')//Placement au debut
            {
                i--;
            }
            while(html[i] != ' ')//Recup�ration
            {
                tampon.push_back(html[i+1]);
                i++;
            }
            accent(tampon); //On vire la merde cod� sur 2 octets
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
            case 0xffffffa2://� a2
            {
                CharToOemA("�", &texte[i-1]);

                texte.erase(i, 1);
                i--;
                break;
            }
            case 0xffffffa9://� a9
            {
                CharToOemA("�", &texte[i-1]);

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
            case 0xffffffbb: //� bb
            {
                CharToOemA("�", &texte[i-1]);

                texte.erase(i, 1);
                i--;
                break;
            }
            case 0xffffffa8: //� a8
            {
                CharToOemA("�", &texte[i-1]);

                texte.erase(i, 1);
                i--;
                break;
            }
            case 0xffffffb4: //� b4
            {
                CharToOemA("�", &texte[i-1]);

                texte.erase(i, 1);
                i--;
                break;
            }
            case 0xffffffaf: //� b4af 3735
            {
                CharToOemA("�", &texte[i-1]);

                texte.erase(i, 1);
                i--;
                break;
            }
            case 0xffffffa0: //� a0
            {
                CharToOemA("�", &texte[i-1]);

                texte.erase(i, 1);
                i--;
                break;
            }
            case 0xffffffaa: //� aa
            {
                CharToOemA("�", &texte[i-1]);

                texte.erase(i, 1);
                i--;
                break;
            }
            case 0xffffffae: //� ae
            {
                CharToOemA("�", &texte[i-1]);

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
            case 0xffffffa7: // � a7
            {
                CharToOemA("�", &texte[i-1]);

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
