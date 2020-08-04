#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINE 1000
#define MAX_NS 4000        // the upper bound of possible values of Ns
#define YES 1              // the slot has been marked
#define NO  0              // the slot has not been marked
#define MAX_TSUR 11000000   // the max number of TSUR 

struct ns
{
    float   poss;          // possibility
    int     seq;
};

static struct ns  slot[MAX_NS];
static int  frn[MAX_TSUR];

/********* Define the comparison metric for qsort *********************/
int compi(const void *a, const void *b)
{
    const struct ns *p = a;
    const struct ns *q = b;
    if(p->poss > q->poss)
    {
        return 1;
    }  
    else
    {
        return -1;
    }
}
/*********************************************************************/


int main(int argc, char *argv[]) 
{
    clock_t begin = clock();
    FILE *fp;   
    char strLine[MAX_LINE];                             // read buffer     
    char   *posit;
    int  i, j, comp;

    i = 0; 
    if((fp = fopen("TSUR_2.txt","r")) == NULL)          // open the TSUR file
    {   
        printf("Open Falied!");   
        return -1;   
    }   
    while (!feof(fp))                                    
    {   
        fgets(strLine,MAX_LINE,fp);                     
    //  printf("%s", strLine);                          
        frn[i] = atoi(strLine);                         // store TSUR 
    //  printf("%d\n", frn[i]);
        i++; 
    }  
    comp = i;                                           // the total number of TSUR
    fclose(fp);                                         // close the TSUR file  
 // printf(" no[%d] = %d\n", comp-1, frn[comp-1]);
 
    /********* Initialize the poss array *********************/
    for (j = 0; j < MAX_NS; j++)
    {
        slot[j].poss = 1.0;
        slot[j].seq = j;
    }
    /*********************************** *********************/

    /**** Calculate the possibility (density) for each possible value ****/
    for (j = 2; j < MAX_NS; j ++)
    {
        posit = (char*)malloc(j*sizeof(char));
        for(i = 0; i < j; i++)
        {
            *(posit+i) = NO;
        }
        for (i = 0; i < comp; i++)
        {
            if(*(posit+frn[i]%j) == NO)
            {
                *(posit+frn[i]%j) = YES;
                slot[j].poss = slot[j].poss - 1/(float)j;
            }
        }
        free(posit);
    }
    clock_t mid = clock();
    double time1 = (double)(mid - begin) / CLOCKS_PER_SEC;
    printf("Beofre sorting, Time Spent: %f\n", time1);
    /*********************************** *********************************/

    qsort(slot+2, MAX_NS-2, sizeof(slot[0]), compi);        // quick sort 
    for(i = MAX_NS-1; i > MAX_NS - 11; i--)                 // output
    {
        printf("Ns(%d) possibility = %lf\n", slot[i].seq, slot[i].poss);
    }

    clock_t end = clock();
    double time = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("After sorting, Time Spent: %f\n", time);

    return 0;   
}