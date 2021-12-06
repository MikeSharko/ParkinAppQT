#ifndef LOGIN_H
#define LOGIN_H
#include <QString>


class Login
{
public:

    static Login *getInstance();
    QString getUsername();
    void setUsername(QString &name);

    ~Login();
private:
    static Login *Instance;

    //private constructor
    Login();
    QString username;
};

#endif // LOGIN_H
