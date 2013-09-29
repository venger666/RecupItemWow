#ifndef SQL_H
#define SQL_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "SQL/sqlite3.h"

using namespace std;

class Sql
{
    private:
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char* data = "Callback appelle";

    public:
    Sql(const std::string &_db );
    ~Sql();

    static int callback(void *data, int argc, char **argv, char **azColName);

    void requete(const std::string &_requete);
};

#endif // SQL_H
