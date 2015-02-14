#include "RNG.hpp"

class ChooseList
{
private:
    int numbers[1000], len;
    RNJ* jesus;
    bool external;

    void remove(int idx)
    {
        if(idx>=len) return;
        numbers[idx] = numbers[len-1];
        len--;
    }

public:
    ChooseList()
    {
        len=0;
        jesus = new RNJ;
        jesus->init();
        external=false;
    }

    ChooseList(RNJ* ext)
    {
        len=0;
        jesus=ext;
        external=true;
    }

    ChooseList(int cElements)
    {
        for(int i = 0; i < cElements; i++) numbers[i]=i;
        len=cElements;

        jesus = new RNJ;
        jesus->init();
        external=false;
    }

    ChooseList(int cElements, RNJ* ext)
    {
        for(int i = 0; i < cElements; i++) numbers[i]=i;
        len=cElements;
        jesus=ext;
        external=true;
    }

    bool fill(int cElements)
    {
        if(cElements>1000) return false;
        for(int i = 0; i < cElements; i++) numbers[i]=i;
        len=cElements;
        return true;
    }

    int choose()
    {
        int choice = jesus->nextInt(0, len-1);
        int val = numbers[choice];
        remove(choice);
        return val;
    }
};