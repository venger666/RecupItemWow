#include "Sql.h"

Sql::Sql(const std::string &_db)
{
    /* Ouverture bdd */
    rc = sqlite3_open(_db.c_str(), &db);

    if(rc)
    {
        cout << "Ouverture bdd impossible : " <<  sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Ouverture bdd reussi" << endl;
    }
}

Sql::~Sql()
{
    std::cout << "Fermeture DB" << std::endl;
    sqlite3_close(db);
}

void Sql::requete(const std::string &_requete)
{
    rc = sqlite3_exec(db, _requete.c_str(), Sql::callback, 0, &zErrMsg);

    if(rc != SQLITE_OK)
    {
        cout << "Erreur SQl : " << zErrMsg << endl;
        sqlite3_free(zErrMsg);
    }
    else
    {
        cout << "Execution reussi" << endl;
    }
}

int Sql::callback(void *data, int argc, char **argv, char **azColName)
{
    std::cout << argc << std::endl;
    int i;
    //fprintf(stderr, "%s: ", (const char*)data);

    for(i = 0; i < argc; i++)
    {
        std::string c = azColName[i], d = argv[i];
        std::cout << c.size() << "  " << d.size() << std::endl;

        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    cout << endl;;

    return 0;
}
