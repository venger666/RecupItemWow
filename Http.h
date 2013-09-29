#ifndef HTTP_H
#define HTTP_H

#include <iostream>
#include <sstream>

#include <SFML/Network.hpp>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

class Item;

class Http
{
    private:
        sf::Http http;

        bool recupPage(string &html, int id);
        void parse(const string &html, Item *item);
        void accent(string &texte);

    public:
        Http();
        ~Http();

        bool process(Item *item, int id);
};

#endif // HTTP_H
