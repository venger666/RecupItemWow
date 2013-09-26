#ifndef HTTP_H
#define HTTP_H

#include <iostream>

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

        void parse(const std::string &html, Item *item);
        void accent(string &texte);

    public:
        Http(const string &_host);
        ~Http();
};

#endif // HTTP_H
