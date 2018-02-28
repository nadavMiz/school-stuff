#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SUB_AMOUNT 100000
#define LINE_AMOUNT 10000000
#define STR_LEN 16
#define AMOUNT_OF_FILES 2
#define FILE_EXTENSION ".cdr"

typedef struct Sub
{
    char            m_imsi[STR_LEN];
    char            m_msisdn[STR_LEN];
    char            m_imei[STR_LEN];
    int             m_mcc;
}Sub;

int main()
{
    FILE* fp;
    int mcc[6] = {123456, 654987, 84534, 98763, 36549};
    Sub subs[SUB_AMOUNT];
    unsigned int x, i, j, k, callType;
    unsigned int num;
    char str[STR_LEN];
    char fileName[64] = "";
    char buff[6];
    char callDate[] = "01/06/1986";
    char callTime[] = "12:58:21";
    char brandName[] = "Dummy Corp";
    char* callTypeArr[5] = {"MOC", "MTC", "SMS-MO", "SMS-MT", "GPRS"};
    
    for (i = 0; i < SUB_AMOUNT; ++i)
    {
        memset(str, 0, STR_LEN);
        for (j = 0; j < 3; ++j)
        {
            num = rand() % 100000;
            sprintf(buff,"%d",num);
            strcat(str, buff);            
        }
        strcpy(subs[i].m_imsi, str);
        
        memset(str, 0, STR_LEN);
        for (j = 0; j < 3; ++j)
        {
            num = rand() % 100000;
            sprintf(buff,"%d",num);
            strcat(str, buff);          
        }
        strcpy(subs[i].m_msisdn, str);
        
        memset(str, 0, STR_LEN);
        for (j = 0; j < 3; ++j)
        {
            num = rand() % 100000;
            sprintf(buff,"%d",num);
            strcat(str, buff);              
        }
        strcpy(subs[i].m_imei, str);
        
        subs[i].m_mcc = mcc[rand() % 5];
    }
    
    for (x = 0; x < AMOUNT_OF_FILES; ++x)
    {
        printf("creating file #%u...\n", x);
        sprintf(fileName, "CDRFile%d%s", x, FILE_EXTENSION);
        fp = fopen(fileName, "w");
        fprintf(fp,"HEADER STUFF\n");

        for (i = 0; i < LINE_AMOUNT; ++i)
        {
            
            j = rand() % SUB_AMOUNT;
            k = rand() % SUB_AMOUNT;
            callType = rand() % 5;
            fprintf(fp, "%s|%s|%s|%s|%d|%s|", subs[j].m_imsi, subs[j].m_msisdn, subs[j].m_imei, brandName, mcc[0], callTypeArr[callType]);
            if ((0 == callType) || (1 == callType))
            {
                fprintf(fp, "%s|%s|%u|%f|%f|%s|%d", callDate, callTime, rand() % 1000, (float)0, (float)0, subs[k].m_msisdn, mcc[rand() % 6]);
            }
            if ((2 == callType) || (3 == callType))
            {
                fprintf(fp, "%s|%s|%u|%f|%f|%s|%d", callDate, callTime, 0, (float)0, (float)0, subs[k].m_msisdn, mcc[rand() % 6]);
            }
            if (4 == callType)
            {
                fprintf(fp, "%s|%s|%u|%f|%f|%s|%d", callDate, callTime, 0, (float)(rand()%1000)/100, (float)(rand()%1000)/100, " ", mcc[rand() % 6]);
            }
            fprintf(fp, "\n");
        }
        
        
        fclose(fp);
        
    }
    printf("done\n");
    return 0;
}
