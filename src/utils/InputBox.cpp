#include "InputBox.h"
#include <cstdlib>



InputBox::InputBox(const Rectangle& box){
    dimensions = box;
    inputText[0] = '\0';
    isEnteringInput = false;
    PInputValue = 0;
}

void InputBox::Update(){
    isEnteringInput = !isEnteringInput;
    if(!isEnteringInput){
        PInputValue = atoi(inputText);
        inputText[0] = '\0';
    }
}

void InputBox::Draw(){
    GuiTextBox(dimensions,inputText,100,true);
}

int InputBox::GetInputValue() const{
    return this->PInputValue;
}

bool InputBox::IsEnteringInput() const{
    return this->isEnteringInput;
}
