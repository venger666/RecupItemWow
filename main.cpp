#include <iostream>

#include "Item.h"

using namespace std;

int main()
{
    Item item;

    item.setId("Test");

    cout << item.getId() << endl;
    return 0;
}
