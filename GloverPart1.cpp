// TOOP Final.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


enum class ErrorLevel { SEVERE, ERROR, WARNING, INFO };
extern void SDAOSlogger(struct ErrorContext& logcontext);


struct ErrorContext {
    ErrorLevel errlevel;
    const char* logmsg;
};

/*This could definitely be a function I believe but I wrote it as a class and don't want to run out of time error checking the conversion*/
class ErrorPacker {
public:
    void Conversion(ErrorLevel level, std::string code) {
        ErrorContext msg;
        msg.errlevel = level;
        msg.logmsg = code.c_str();;
        SDAOSlogger(msg);
    }
};


class ErrorSingleton {
private:
    static ErrorSingleton* instance;
    ErrorSingleton();
public:
    static ErrorSingleton* getInstance();

    void sendSevere(std::string code) {
        ErrorPacker a;
        a.Conversion(ErrorLevel::SEVERE, code);
        // this is where we will pass it to the facade
    }
    void sendError(std::string code) {
        ErrorPacker a;
        a.Conversion(ErrorLevel::ERROR, code);
        // this is where we will pass it to the facade
    }
    void sendWarning(std::string code) {
        ErrorPacker a;
        a.Conversion(ErrorLevel::WARNING, code);
        // this is where we will pass it to the facade
    }
    void sendInfo(std::string code) {
        ErrorPacker a;
        a.Conversion(ErrorLevel::INFO, code);
        // this is where we will pass it to the facade
    }
};

ErrorSingleton* ErrorSingleton::instance = 0;

ErrorSingleton* ErrorSingleton::getInstance() {
    if (instance == 0){
        instance = new ErrorSingleton();
    }
    return instance;
}
ErrorSingleton::ErrorSingleton(){}




int main()
{
    ErrorSingleton* s = ErrorSingleton::getInstance();

    std::string y = "Help";
    s->sendError(y);
    s->sendInfo("this aint great");
}

void SDAOSlogger(ErrorContext& logcontext)
{
    std::cout << static_cast<int> (logcontext.errlevel) << " " << logcontext.logmsg << std::endl;
}
