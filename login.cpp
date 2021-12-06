#include "login.h"

//initialize a static  variable
Login *Login::Instance(nullptr);


Login *Login::getInstance()
{
    if (Instance == nullptr){

    Instance = new Login();
    }

    return Instance;
}

QString Login::getUsername()
{
    return username;
}

void Login::setUsername(QString &name)
{
    username  = name;
}


//constructor
Login::Login()
:username ("")

{

}
