#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define max(a,b) (a > b) ? a : b
#define min(a,b) (a > b) ? b : a
#define Fc (2.5*(10^9))
#define C_lightspeed (3*(10^8))
#define B1_Hbs 10
#define B1_Hms 1.5
#define B1_prime_Hbs 9.0
#define B1_prime_Hms 0.5
#define C1_Hbs 25
#define C1_Hms 1.5
#define D1_Hbs 32
#define D1_Hms 1.5
#define B1_D_prime_BP (((4) * (B1_prime_Hbs) * (B1_prime_Hms) * (Fc)) / (C_lightspeed))
#define C1_Dbp (((4) * (C1_Hbs) * (C1_Hms) * (Fc)) / (C_lightspeed))
#define D1_Dbp (((4) * (D1_Hbs) * (D1_Hms) * (Fc)) / (C_lightspeed))

double randomDouble(void) {
  // RAND_MAX is maximum random value of rand().
  // This dividing makes 0 ~ 1 value.
  return (double) rand() / RAND_MAX; 
  
}

/*
  B1 case formula
*/
double problem6_LoS1(double d){
    double PL_problem6_LoS1 = 22.7 * log10(d) + 41.0 + 20*log10(Fc/5.0);
    return PL_problem6_LoS1;
}

double problem6_LoS2(double d){
    double PL_problem6_LoS2 = 40.0 * log10(d) + 9.45 - 17.3*log10(B1_prime_Hbs) - 17.3*log10(B1_prime_Hms) + 2.7*log10(Fc/5.0);
    return PL_problem6_LoS2;
}


double problem6_NLoS(double dk, double d1){
    //
    double Nj = max(2.8 - 0.0024*dk, 1.84);
    double PL_LoS = 0;
    if(dk < B1_D_prime_BP){
        PL_LoS = problem6_LoS1(dk);
    }else{
        PL_LoS = problem6_LoS2(dk);
    }

    double PL_problem6_NLoS = PL_LoS +20 - 12.5*Nj +10*Nj*log10(d1) + 3*log10(Fc/5.0);
    //printf("problem6 NLoS dk : %n , d1 : %n, NLoS : %lf\n", dk, d1, PL_problem6_NLoS);
    return PL_problem6_NLoS;
}

/*
  C1 case formula
*/
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

/*
  D1 case formula
*/
double problem4_LoS1(double d){
    double PL_problem4_LoS1 = 21.5 * log10(d) + 44.2 + 20*log10(Fc/5.0);
    return PL_problem4_LoS1;
}

double problem4_LoS2(double d){
    double PL_problem4_LoS2 = 40.0 * log10(d) + 10.5 - 18.5*log10(D1_Hbs) - 18.5*log10(D1_Hms) + 1.5*log10(Fc/5.0);
    return PL_problem4_LoS2;
}

double problem4_NLoS(double d){
    double PL_problem4_NLoS = 25.1*log10(d) +55.4 - 0.13*(D1_Hbs-25)*log10(d/100) - 0.9*(D1_Hms - 1.5) + 21.3 * log10(Fc/5.0);
    return PL_problem4_NLoS;
}

void problem1(){
  /*
     problem 1, dbp = 4*hbs*hms*fc/c = 1250;
     f=2.5GHz , d = 30m ~ 5000m
     LoS 30m ~ dbp : A=23.8, B=41.2, C=20
                Alog10(d[m]) + b + Clog10(fc/5.0)
        dbp ~ 5000 : 40.0log10(d) + 11.65 - 16.2log10(hbs) - 16.2log10(hms) + 3.8log10(fc/5.0)
        hbs=25m, hms=1.5m
     NLoS (44.9 - 6.55log10hbs)log10(d) + 31.46 + 5.83log10(hbs) + 23log10(fc/5.0)
   */
    printf("problem1 start..\n");
    FILE *out_problem1_LoS;
    out_problem1_LoS = fopen("problem1_LoS.txt", "w");

    FILE *out_problem1_NLoS;
    out_problem1_NLoS = fopen("problem1_NLoS.txt", "w");
    int i=0;
    for(i=30; i <= 5000; i++){
        if(i>50){
            fprintf(out_problem1_NLoS, "%d, %lf\n", i, problem1_NLoS(i));
        }
        if(i<C1_Dbp){
            fprintf(out_problem1_LoS, "%d, %lf\n", i, problem1_LoS1(i));
        }else{
            fprintf(out_problem1_LoS, "%d, %lf\n", i, problem1_LoS2(i));
        }
    }
    fclose(out_problem1_NLoS);
    fclose(out_problem1_LoS);
    printf("problem1 end.\n");
}

int isLoS_B1(double d){

    double exp_val = pow(M_E, -(d/36)); // M_E == e , It is define by _USE_MATH_DEFINES
    double min_val = min(18/d, 1);
    double Plos = min_val * (1 - exp_val) + exp_val;
    double randVal = randomDouble();

    if(randVal >= Plos){

        return 1;
    }else{

        return 0;
    }
}

int isLoS_C1(int d){

    double Plos = pow(M_E, -(d/200));
    double randVal = randomDouble();

    if(randVal >= Plos){
        return 1;
    }else{
        return 0;
    }
}

int isLoS_D1(int d){

    double Plos = pow(M_E, -(d/1000));
    double randVal = randomDouble();

    if(randVal >= Plos){
        return 1;
    }else{
        return 0;
    }
}

void problem2(){
  /*
     problem 2, dbp = 4*hbs*hms*fc/c = 1250;
     f=2.5GHz , d = 30m ~ 5000m
     LoS 30m ~ dbp : A=23.8, B=41.2, C=20
                Alog10(d[m]) + b + Clog10(fc/5.0)
        dbp ~ 5000 : 40.0log10(d) + 11.65 - 16.2log10(hbs) - 16.2log10(hms) + 3.8log10(fc/5.0)
        hbs=25m, hms=1.5m
     NLoS (44.9 - 6.55log10hbs)log10(d) + 31.46 + 5.83log10(hbs) + 23log10(fc/5.0)
   */
    printf("problem2 start..\n");
    FILE *out_problem2;
    out_problem2 = fopen("problem2.txt", "w");


    int i=0;
    for(i=30; i <= 5000; i++){

        if(i<50){
            fprintf(out_problem2, "%d, %lf\n", i, problem1_LoS1(i));
        }else{
            if(isLoS_C1(i)){
                if(i<C1_Dbp){
                    fprintf(out_problem2, "%d, %lf\n", i, problem1_LoS1(i));
                }else{
                    fprintf(out_problem2, "%d, %lf\n", i, problem1_LoS2(i));
                }
            }else{

                fprintf(out_problem2, "%d, %lf\n", i, problem1_NLoS(i));
            }
        }
    }
    fclose(out_problem2);
    printf("problem2 end.\n");
}

double getRSS(double pathLoss, double shadowFading){
    double Pbs = 46.0;
    return Pbs - pathLoss - shadowFading;
}

void problem3(){
    /* Pbs = 46 dbM
     RSS(d) = Pbs - PL(d) - |S(d)|

     shadow fading std,
     30 < d < dbp : 4
     dbp < d < 5000 : 6
     NLoS : 8

     draw RSS according to the distance
     Propagation condition is same as those of Problem2
    */
    printf("problem3 start..\n");
    FILE *out_problem3;
    out_problem3 = fopen("problem3.txt", "w");

    int i=0;
    for(i=30; i <= 5000; i++){
        if(i<50 || isLoS_C1(i)){
            if(i<C1_Dbp){
                fprintf(out_problem3, "%d, %lf\n", i, getRSS(problem1_LoS1(i), 4));
            }else{
                fprintf(out_problem3, "%d, %lf\n", i, getRSS(problem1_LoS2(i), 6));
            }
        }else{
            fprintf(out_problem3, "%d, %lf\n", i, getRSS(problem1_NLoS(i), 8));
        }
    }
    fclose(out_problem3);
    printf("problem3 end.\n");
}

void problem4(){

    /*
     4-1
    */
    printf("problem4 start..\n");
    FILE *out_problem4_1_LoS;
    out_problem4_1_LoS = fopen("problem4_1_LoS.txt", "w");

    FILE *out_problem4_1_NLoS;
    out_problem4_1_NLoS = fopen("problem4_1_NLoS.txt", "w");
    int i=0;
    for(i=10; i <= 5000; i++){
        if(i>50){
            fprintf(out_problem4_1_NLoS, "%d, %lf\n", i, problem4_NLoS(i));
        }
        if(i<D1_Dbp){
            fprintf(out_problem4_1_LoS, "%d, %lf\n", i, problem4_LoS1(i));
        }else{
            fprintf(out_problem4_1_LoS, "%d, %lf\n", i, problem4_LoS2(i));
        }
    }
    fclose(out_problem4_1_NLoS);
    fclose(out_problem4_1_LoS);

    /*
     4-2
    */
    FILE *out_problem4_2;
    out_problem4_2 = fopen("problem4_2.txt", "w");


    for(i=10; i <= 5000; i++){

        if(i<50){
            fprintf(out_problem4_2, "%d, %lf\n", i, problem4_LoS1(i));
        }else{
            if(isLoS_D1(i)){
                if(i<D1_Dbp){
                    fprintf(out_problem4_2, "%d, %lf\n", i, problem4_LoS1(i));
                }else{
                    fprintf(out_problem4_2, "%d, %lf\n", i, problem4_LoS2(i));
                }
            }else{
                fprintf(out_problem4_2, "%d, %lf\n", i, problem4_NLoS(i));
            }

        }

    }
    fclose(out_problem4_2);

    /*
     4-3
    */
    FILE *out_problem4_3;
    out_problem4_3 = fopen("problem4_3.txt", "w");

    for(i=10; i <= 5000; i++){
        if(i<50 || isLoS_D1(i)){
            if(i<D1_Dbp){
                fprintf(out_problem4_3, "%d, %lf\n", i, getRSS(problem4_LoS1(i), 4));
            }else{
                fprintf(out_problem4_3, "%d, %lf\n", i, getRSS(problem4_LoS2(i), 6));
            }
        }else{
            fprintf(out_problem4_3, "%d, %lf\n", i, getRSS(problem4_NLoS(i), 8));
        }
    }
    fclose(out_problem4_3);
    printf("problem4 end.\n");
}

void problem6(){
    printf("problem6 start..\n");
    FILE *out_problem6;
    out_problem6 = fopen("problem6.txt", "w");

    int i =0;
    int d1, d2 = 0;
    for(i=10; i <= 1000; i++){
        d1=i;
        if(i > 500){  // d2 should be 0 until d1 < 500.
            d1=500;
            d2=i-d1;
        }
        // Considering the Line of sight probabilities of B1

        if(d2<10 || isLoS_B1(d1+d2)){
            if(i<B1_D_prime_BP){
                fprintf(out_problem6, "%d, %lf\n", d1+d2, getRSS(problem6_LoS1(d1), 3));
            }else{
                fprintf(out_problem6, "%d, %lf\n", d1+d2, getRSS(problem6_LoS2(d1), 3));
            }
        }else{

            fprintf(out_problem6, "%d, %lf\n", d1+d2, getRSS(min(problem6_NLoS(d1,d2), problem6_NLoS(d2,d1)), 4));
        }
    }
    fclose(out_problem6);
    printf("problem6 end.\n");
}

int main (void)
{
    srand(time(NULL)); // to add seed (time) on rand() function.

    problem1();
    problem2();
    problem3();
    problem4();
    problem6();

    return 0;
}
