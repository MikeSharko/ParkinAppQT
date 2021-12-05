#ifndef LOGGER_H
#define LOGGER_H
#include <QString>


class Logger
{
public:

    static Logger *getInstance();
    ~Logger();
private:
    static Logger *Instance;
    Logger();
    QString username;
};

#endif // LOGGER_H
