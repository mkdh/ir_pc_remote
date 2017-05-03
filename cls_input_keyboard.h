#ifndef CLSINPUTKEYBOARD_H
#define CLSINPUTKEYBOARD_H

//http://stackoverflow.com/questions/3063110/get-the-current-operating-system-during-runtime-in-c
#ifdef WIN32
#define WINVER 0x0500
#include "windows.h"
#endif

#include <QString>
//https://batchloaf.wordpress.com/2012/10/18/simulating-a-ctrl-v-keystroke-in-win32-c-or-c-using-sendinput/

class clsInputKeyboard
{
public:
    clsInputKeyboard();
    //    void test();
    void input_single_command(QString str_key);
private:
#ifdef WIN32
    INPUT ip;
#endif

};

#endif // CLSINPUTKEYBOARD_H
