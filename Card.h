#ifndef _CARD_H_
#define _CARD_H_
#include <string>

class Card {
    private:
        std::string front;
        std::string back;

    public:
        Card(const std::string& front, const std::string& back);
        std::string getFront();
        std::string getBack();

};

#endif