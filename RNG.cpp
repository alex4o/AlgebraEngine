#include "RNG.hpp"


void RNJ::init()
{
	#ifdef __linux__
	timeval time_seed;
		gettimeofday(&time_seed, NULL);
		srand(time_seed.tv_usec + time_seed.tv_sec);
		std::cout<<"init rand\n";
	#elif _WIN32
	srand(time(0));
#endif
}

 RNJ::RNJ()
{
	init();
}

bool  RNJ::nextBool()
{
	return rand()%2;
}

int  RNJ::nextInt(int low, int high)
{

	if(low > high){
		std::cout<<low<<" > "<<high<<"\n";
		return 0;
	}
		return rand()%(high-low+1) + low;
}

Number  RNJ::nextNumber(CoefDescriptor& cd)
{
    int r = nextInt(1, 100);
    int sign = 1;
    int r2 = nextInt(1, 100);
    if(r2<=cd.pNegative) sign = -1;

    if(r<=cd.pNatural)
    {
       return Number(sign*nextInt(cd.upLow, cd.upHigh));
    }
    else if(r>cd.pNatural and r<= cd.pRational + cd.pNatural)
    {
       return Number(sign*nextInt(cd.upLow, cd.upHigh), nextInt(cd.downLow, cd.downHigh));
    }
    else
    {
       return Number();
    }
}

Number  RNJ::nextNumber(RootDescriptor& rd)
{
    int r = nextInt(1, 100);
    int sign = 1;
    int r2 = nextInt(1, 100);
    if(r2<=rd.pNegative) sign = -1;

    if(r<=rd.pNatural)
    {
        return Number(sign*nextInt(rd.upLow, rd.upHigh));
    }
    else if(r>rd.pNatural and r<= rd.pFraction + rd.pNatural)
    {
        return Number(sign*nextInt(rd.upLow, rd.upHigh), nextInt(rd.downLow, rd.downHigh));
    }
    else
    {
        return Number();
    }
 }

Term RNJ::nextTerm(RootDescriptor &rd, int maxPower, char letter, bool nice, char l) {
    Term result;

    int power = nextInt(1, maxPower);
    result.coef = nextNumber(rd);

   // cout<<"term call, power: "<<power<<": ";

    int cSubTerms = nextInt(1, power);

    int powers[cSubTerms];
    createListOfInts(powers, cSubTerms, power, this);
    //for(int i = 0; i < cSubTerms; i++) cout<<powers[i]<<" ";
    //cout<<endl;

    for(int j = 0; j < cSubTerms; j++)//Subterm(aka Polynomial)
    {
        int cPower = powers[j];

        Polynomial poly;
        poly.monos.clear();

        Number root = nextNumber(rd);

        stringstream ss;
        root.print(false, false, ss);
        cout<<"\t\t root of subTerm: "<<ss.str()<<endl;
        ss.str("");

        if(!nice)
        {
            Monomial m1(Number(1), l);
            Monomial m2(root);

            poly.monos.push_back(m1);
            poly.monos.push_back(m2);
            poly.totalPower=1;
        }
        else
        {
            Monomial m1(Number(root.fraction.down), l);
            Monomial m2(Number(root.fraction.up));

            poly.monos.push_back(m1);
            poly.monos.push_back(m2);
            poly.totalPower=1;
        }

        poly.print(ss);
        cout<<"\t\t poly: "<<ss.str()<<endl;
        ss.str("");

        result.polys.push_back(poly);
        result.powers.push_back(cPower);
    }

    return result;
}

void createListOfInts(int* array, int size, int sum, RNJ* jesus)
{
    memset(array+4, 0, (size-1)*4);
    array[0]=sum;

    int chArr[size];

    for(int i = 0; i < size - 1; i++)
    {
        int chArrLen = 0;
        for(int j = 0; j <= i; j++)
        {
            if(array[j]>1) chArr[chArrLen++] = j;
        }

        int choice = jesus->nextInt(0, chArrLen-1);

        int newInt = jesus->nextInt(1, array[chArr[choice]]-1);
        array[i+1] = newInt;
        array[chArr[choice]] -= newInt;
    }
}