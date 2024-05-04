#pragma once
#include <raylib.h>
#include <raygui/raygui.h>

class InputBox{
    private:
        Rectangle dimensions;
        char inputText[100];
        bool isEnteringInput;
        int  PInputValue;
        
public:
        InputBox(const Rectangle&);
        void Update();
        void Draw();
        int GetInputValue() const;
        bool IsEnteringInput() const;
};
