#include "logger.h"

//initialize a static  variable
Logger *Logger::Instance(nullptr);


Logger *Logger::getInstance()
{
    if (Instance == nullptr){

    Instance = new Logger;
    }

   return Instance;
}

Logger::Logger()
{



}
