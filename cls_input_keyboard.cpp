#include "cls_input_keyboard.h"

clsInputKeyboard::clsInputKeyboard()
{
#ifdef WIN32

    // Create a generic keyboard event structure
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
#endif

}

void clsInputKeyboard::input_single_command(QString str_key)
{
#ifdef WIN32

    if(str_key == "Up")
    {
        // Press the "Ctrl" key
        ip.ki.wVk = VK_UP;
        ip.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &ip, sizeof(INPUT));


        // Release the "Ctrl" key
        ip.ki.wVk = VK_UP;
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
    }
    else if(str_key == "Down")
    {
        // Press
        ip.ki.wVk = VK_DOWN;
        ip.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &ip, sizeof(INPUT));


        // Release
        ip.ki.wVk = VK_DOWN;
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
    }
    else if(str_key == "Left")
    {
        // Press
        ip.ki.wVk = VK_LEFT;
        ip.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &ip, sizeof(INPUT));


        // Release
        ip.ki.wVk = VK_LEFT;
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
    }
    else if(str_key == "Right")
    {
        // Press
        ip.ki.wVk = VK_RIGHT;
        ip.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &ip, sizeof(INPUT));


        // Release
        ip.ki.wVk = VK_RIGHT;
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
    }
    else if(str_key == "Enter")
    {
        // Press
        ip.ki.wVk = VK_RETURN;
        ip.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &ip, sizeof(INPUT));


        // Release
        ip.ki.wVk = VK_RETURN;
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
    }
    else if(str_key == "Space")
    {
        // Press
        ip.ki.wVk = VK_SPACE;
        ip.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &ip, sizeof(INPUT));


        // Release
        ip.ki.wVk = VK_SPACE;
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
    }
    else if(str_key == "PgUp")
    {//http://www.setnode.com/blog/mapvirtualkey-getkeynametext-and-a-story-of-how-to/
        // Press
        ip.ki.wVk = VK_PRIOR;
        ip.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &ip, sizeof(INPUT));


        // Release
        ip.ki.wVk = VK_PRIOR;
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
    }
    else if(str_key == "PgDn")
    {
        // Press
        ip.ki.wVk = VK_NEXT;
        ip.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &ip, sizeof(INPUT));


        // Release
        ip.ki.wVk = VK_NEXT;
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
    }

#endif
}

//void clsInputKeyboard::test()
//{
//    while(1)
//    {
//        // Press the "Ctrl" key
//        ip.ki.wVk = VK_CONTROL;
//        ip.ki.dwFlags = 0; // 0 for key press
//        SendInput(1, &ip, sizeof(INPUT));

//        // Press the "V" key
//        ip.ki.wVk = 'V';
//        ip.ki.dwFlags = 0; // 0 for key press
//        SendInput(1, &ip, sizeof(INPUT));

//        // Release the "V" key
//        ip.ki.wVk = 'V';
//        ip.ki.dwFlags = KEYEVENTF_KEYUP;
//        SendInput(1, &ip, sizeof(INPUT));

//        // Release the "Ctrl" key
//        ip.ki.wVk = VK_CONTROL;
//        ip.ki.dwFlags = KEYEVENTF_KEYUP;
//        SendInput(1, &ip, sizeof(INPUT));

//        Sleep(1000); // pause for 1 second
//    }
//}
