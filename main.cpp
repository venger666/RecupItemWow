#include <iostream>

#include "Item.h"
#include "Http.h"

using namespace std;

int main()
{
    Item item;
    Http http;

    int i = 3000;

    while(i < 5000)
    {
        if(http.process(&item, i))
        {
            item.afficher();
        }
        else
        {
            cout << "Pas d'item ID : " << i << endl << endl;
        }
        i++;
    }

    return 0;
}
