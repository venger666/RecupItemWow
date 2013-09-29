#include <iostream>

#include "Item.h"
#include "Http.h"
#include "Sql.h"

using namespace std;

int main()
{
    Item item;
    Http http;

    Sql sql("item.db");

    int i = 0;

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
