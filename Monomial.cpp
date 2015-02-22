#include <map>
#include "Monomial.hpp"

void Monomial::sortSimple() //Поддържаме простите едночлени сортирани по азбучен ред
{                 //Това ще улесни умножението на многочлени
    if(simples.empty()) return;
    sort(simples.begin(), simples.end(), cmpSimple);
}

Monomial::Monomial() //Стандартния конструктор
{
    totalPower=0;
    coef=Number(0);
}

Monomial::Monomial(Number n) //едночлен от нулева степен, т.е.
{                  //свободен член
    coef=n;
    totalPower=0;
}

Monomial::Monomial(std::string s, int* idx) //Конструктор със string
{
    //Във финалната версия няма да се ползва много, но сега
    coef=Number(1);               //ще е полезен за тестване, а може и да му се намери някоя
    if(isNumeric(s[*idx]))           //употреба за домашно по математика
    {
        int n = 0;

        while( isNumeric(s[*idx]) )
        {
            n*=10;
            n+=s[*idx]-'0';
            (*idx)++;
        }
        coef=Number(n);
    }

    totalPower=0;
    if(*idx>=s.size())
    {

        return;
    }

    while(*idx<s.size() and s[*idx]!=' ') //Вече е сигурно, че първия символ е буква
    {

        Simple si(s, idx);   //Затова правим прости едночлени докато можем
        simples.push_back(si);//Ето тук влиза пойнтъра към индекс в оня конструктор
        totalPower+=si.pow;
    }
    sortSimple();
}

Monomial::Monomial(Number c, std::vector<Simple> v)//Конструктор със коефицент и вектор от прости
{                                   //Може би него ще използваме по-нататък
    coef=c;
    totalPower=0;
    for(int i = 0; i < v.size(); i++)
    {
        totalPower+=v[i].pow;
        simples.push_back(v[i]);
    }
    sortSimple();
}

Monomial::Monomial(Number c, char letter)
{
    coef=c;
    Simple s(letter, 1);
    simples.push_back(s);
    totalPower=1;
}

Monomial::Monomial(Number c, char letter, int pow)
{
    coef=c;
    Simple s(letter, pow);
    simples.push_back(s);
    totalPower=pow;
}

Monomial operator*(const Monomial &m1, const Monomial &m2) //Умножението
{   //Мап за прости едночлени - но не като клас, а като двойка, където char е ключа
    std::map<char, int> powers; //Смятах да ползвам масив char от 256 елемента, но сметнах, че така ще е по-бързо(надявам се)
    for(int i = 0; i < m1.simples.size(); i++) powers[m1.simples[i].letter]+=m1.simples[i].pow;
    for(int i = 0; i < m2.simples.size(); i++) powers[m2.simples[i].letter]+=m2.simples[i].pow;

    Monomial result;
    result.coef = m1.coef*m2.coef; //Коефицента при умножение на едночлени
    //Може да се направи проверка дали е 0 в началото, но това са подробности
    std::map<char, int>::iterator it = powers.begin(); //и евентуално бъдещи оптимизации

    while(it!=powers.end())
    {
        Simple s(it->first, it->second); //Добавяме всички получени прости едночлени към резултата
        result.simples.push_back(s); //Хубавото на map-a е, че ни гарантира подредеността на простите едночлени
        it++;                        //така че няма нужда да викаме sortSimple
    }

    result.totalPower=m1.totalPower+m2.totalPower; //Надявам се това да е така
    //освен ако не съм забравил математиката за 7 кл.
    return result;
}

//След дълги опити, мисля че така е вярно и работи. Тествано
bool operator<(const Monomial &m1, const Monomial &m2)
{
    if(m1.totalPower<m2.totalPower) return true; //Първо се опитваме да сортираме по степен
    if(m2.totalPower<m1.totalPower) return false;

    if(m1.simples.size()>m2.simples.size()) return true; //После по дължина
    if(m2.simples.size()>m1.simples.size()) return false;

    int idx = 0;
    int lim = std::min(m1.simples.size(), m2.simples.size());  //И накрая по азбучен ред на буквите
    while(idx<lim)
    {
        if(m1.simples[idx].letter>m2.simples[idx].letter) return true;
        if(m2.simples[idx].letter>m1.simples[idx].letter) return false;

        if(m1.simples[idx].pow<m2.simples[idx].pow) return true;
        if(m2.simples[idx].pow<m1.simples[idx].pow) return false;
        idx++;
    }

    return false; //Ако сме стигнало до тук значи двата са еднакви
}                //Което не би трябвало да се случва

bool operator>(const Monomial &m1, const Monomial &m2)//Аналогично за >
{
    if(m1.totalPower>m2.totalPower) return true;
    if(m2.totalPower>m1.totalPower) return false;

    if(m1.simples.size()<m2.simples.size()) return true; //После по дължина
    if(m2.simples.size()<m1.simples.size()) return false;

    int idx = 0;
    int lim = std::min(m1.simples.size(), m2.simples.size());
    while(idx<lim)
    {
        if(m1.simples[idx].letter<m2.simples[idx].letter) return true;
        if(m2.simples[idx].letter<m1.simples[idx].letter) return false;

        if(m1.simples[idx].pow>m2.simples[idx].pow) return true;
        if(m2.simples[idx].pow>m1.simples[idx].pow) return false;
        idx++;
    }

    return false;
}

bool operator==(const Monomial &m1, const Monomial &m2) //Това ще трябва за многочлените
{
    if(m1.totalPower==0 and m2.totalPower==0) return true;
    if(m1.simples.size()!=m2.simples.size()) return false;
    if(m1.totalPower!=m2.totalPower) return false;

    for(int i = 0; i < m1.simples.size(); i++) //Ето тук сортировката на простите едночлени е полезна
    {                                          //Не съм сигурен какво става ако за вход на едночлен имаме ххх3
        if(m1.simples[i].letter!=m2.simples[i].letter) return false; //т.е. ако имаме дублиращи се букви
        if(m1.simples[i].pow!=m2.simples[i].pow) return false;       //но няма да е трудно да се оправи
    }
    return true;
}

bool cmpMono(Monomial m1, Monomial m2)
{
    return m1>m2;
}