#include<stdio.h>

#define MAX_ROUTE 20
#define MAX_NODE 8
struct node
 {
    char network[MAX_ROUTE];
    int network_router[MAX_ROUTE];
    int hops[MAX_ROUTE];

 }rt[MAX_NODE];

 void initRouteTable(){
        rt[1].network[0] = 'B'; rt[1].network_router[0] = -1; rt[1].hops[0] = 1;
        rt[1].network[1] = '2'; rt[1].network_router[1] = -1; rt[1].hops[1] = 1;
        rt[1].network[2] = '4'; rt[1].network_router[2] = -1; rt[1].hops[2] = 1;

        rt[2].network[0] = 'C'; rt[2].network_router[0] = -1; rt[2].hops[0] = 1;
        rt[2].network[1] = '1'; rt[2].network_router[1] = -1; rt[2].hops[1] = 1;
        rt[2].network[2] = '3'; rt[2].network_router[2] = -1; rt[2].hops[2] = 1;

        rt[3].network[0] = 'D'; rt[3].network_router[0] = -1; rt[3].hops[0] = 1;
        rt[3].network[1] = '2'; rt[3].network_router[1] = -1; rt[3].hops[1] = 1;
        rt[3].network[2] = '5'; rt[3].network_router[2] = -1; rt[3].hops[2] = 1;

        rt[4].network[0] = 'A'; rt[4].network_router[0] = -1; rt[4].hops[0] = 1;
        rt[4].network[1] = '1'; rt[4].network_router[1] = -1; rt[4].hops[1] = 1;
        rt[4].network[2] = '5'; rt[4].network_router[2] = -1; rt[4].hops[2] = 1;
        rt[4].network[3] = '7'; rt[4].network_router[3] = -1; rt[4].hops[3] = 1;

        rt[5].network[0] = '3'; rt[5].network_router[0] = -1; rt[5].hops[0] = 1;
        rt[5].network[1] = '4'; rt[5].network_router[1] = -1; rt[5].hops[1] = 1;
        rt[5].network[2] = '6'; rt[5].network_router[2] = -1; rt[5].hops[2] = 1;

        rt[6].network[0] = 'E'; rt[6].network_router[0] = -1; rt[6].hops[0] = 1;
        rt[6].network[1] = 'F'; rt[6].network_router[1] = -1; rt[6].hops[1] = 1;
        rt[6].network[2] = '5'; rt[6].network_router[2] = -1; rt[6].hops[2] = 1;
        rt[6].network[3] = '7'; rt[6].network_router[3] = -1; rt[6].hops[3] = 1;

        rt[7].network[0] = '4'; rt[7].network_router[0] = -1; rt[7].hops[0] = 1;
        rt[7].network[1] = '6'; rt[7].network_router[1] = -1; rt[7].hops[1] = 1;

 }

 int getLength(int i[]){

    int a,cnt = 0;
    for(a=0; a<MAX_ROUTE; a++){
        if(i[a] == 0){
            cnt = a;
            break;
        }
    }
    return cnt;
 }

 void initLinkMatrix(){

 }
int main()
 {

    int maxNodeCnt = 7;
    //clrscr();
    initRouteTable();
    initLinkMatrix();

     int dmat[MAX_NODE][MAX_NODE] ={  // index 0 is guide index.
            {0,0,0,0,0,0,0,0},
            {0,0,1,0,1,0,0,0}, //1
            {0,1,0,1,0,0,0,0}, //2
            {0,0,1,0,0,1,0,0}, //3
            {0,1,0,0,0,1,0,1}, //4
            {0,0,0,1,1,0,1,1}, //5
            {0,0,0,0,0,1,0,1}, //6
            {0,0,0,0,1,1,1,0}  //7
        };

    int i,j,k,l,m, cnt, round = 0;
    bool check = false;

    do{
        ++round;
        printf("\n update round %d is \n",round);
        cnt = 0;
        for(i=1; i<MAX_NODE; i++){
            int routeSize = getLength(rt[i].network_router);
            for(j=1;j<MAX_NODE;j++){
                    if(dmat[i][j]){
                        int targetRouteSize = getLength(rt[j].network_router);

                        for(m=0; m<targetRouteSize; m++){
                            check = false;
                            char targetNetwork = rt[j].network[m];

                            for(l=0; l<routeSize; l++){
                                if(rt[i].network[l] == targetNetwork){
                                    check = true;
                                    if( rt[i].hops[l] > rt[j].hops[m]+1){
                                        rt[i].network_router[l] = j;
                                        rt[i].hops[l] = rt[j].hops[m]+1;
                                        cnt++;
                                    }
                                }
                            }

                            if(!check){
                                rt[i].network[routeSize-1] = targetNetwork;
                                rt[i].network_router[routeSize-1] = j;
                                rt[i].hops[routeSize-1] = rt[j].hops[m]+1;
                                routeSize++;
                                cnt++;
                            }
                        }

                    }
            }
        }
    }while(cnt!=0 && round < 15);


    for(i=1;i<MAX_NODE;i++)
    {
        printf("\n\n State value for router %d is \n",i);
        for(j=0;j<MAX_ROUTE;j++)
        {
            if(rt[i].network_router[j] != 0){
                printf("\t\n network %c via %d Distance %d", rt[i].network[j] , rt[i].network_router[j], rt[i].hops[j] );
            }

        }
    }
    printf("\n\n");
 }
