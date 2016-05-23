#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Fc (2.5*(10^9))
#define C_lightspeed (3*(10^8))
#define C1_Hbs 25
#define C1_Hms 1.5
#define C1_Dbp (((4) * (C1_Hbs) * (C1_Hms) * (Fc)) / (C_lightspeed))


double problem1_LoS1(double d){
    double PL_problem1_LoS1 = 23.8 * log10(d) + 41.2 + 20*log10(Fc/5.0);

    return PL_problem1_LoS1;
}

double problem1_LoS2(double d){
    double PL_problem1_LoS2 = 40.0 * log10(d) + 11.65 - 16.2*log10(C1_Hbs) - 16.2*log10(C1_Hms) + 3.8*log10(Fc/5.0);
    return PL_problem1_LoS2;
}

double problem1_NLoS(double d){
    double PL_problem1_NLoS = (44.9 - 6.55*log10(C1_Hbs))*log10(d) + 31.46 + 5.83*log10(C1_Hbs) + 23*log10(Fc/5.0);
    return PL_problem1_NLoS;
}

void p1(){

    int i=0;
    for(i=30; i <= 5000; i++){
        if(i>50){
            printf("%d, %lf\n", i, problem1_NLoS(i));
        }
        if(i<C1_Dbp){
            printf("%d, %lf\n", i, problem1_LoS1(i));
        }else{
            printf("%d, %lf\n", i, problem1_LoS2(i));
        }
    }
}


int main (void)
{
    p1();
    return 0;
}
