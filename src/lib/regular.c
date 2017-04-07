#include "regular.h"
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int reg_analyze(const char* pattern,const char* tar)
{
    regex_t compiled ;
    char buf[FILENAME_MAX];
    regmatch_t pmatch;
    const size_t nmatch = 1;
    int status = 0;
    int tar_size = strlen(tar);
    status = regcomp(&compiled,pattern,REG_EXTENDED);
    if(status!=0 )
    {
        return REG_COMPILE_ERROR;
    }
    strcpy(buf,tar);
    status = regexec(&compiled,buf,nmatch,&pmatch,0);
    if(status == REG_NOMATCH)
    {
        return REG_NOMATCH;
    }
    else if(status == REG_NOERROR)
    {
        if(pmatch.rm_so!=0 || pmatch.rm_eo!=tar_size)
        {
            return REG_MATCH_HALF;
        }
    }
    /*else if(status == 0)
    {
        puts("match:");
        for(i = pmatch.rm_so;i<pmatch.rm_eo;i++)
            putchar(buf[i]);
        putchar('\n');
    }*/
	regfree(&compiled);
    return REG_MATCH_ALL;
}


///regexec函数一行只匹配一次，如果想要获取其他结果，需要在匹配的字符串后面再进行一次
/*int regtest()
{
    const char* pattern = "[0-9]+@(163|qq)\\.com";
    const char* buf = {"158@163.com"};
    regex_t compiled ;
    regmatch_t pmatch[1];
    const size_t nmatch = 1;
    int status = 0;
    int i = 0;
    status = regcomp(&compiled,pattern,REG_EXTENDED);
    printf("re_nusb:%d\n",compiled.re_nsub);
    if(status != 0)
    {
        puts("compile false");
        return -1;
    }
    status = regexec(&compiled,buf,nmatch,pmatch,0);
    if(status == REG_NOMATCH)
        puts("no match");
    else if(status == 0)
    {
        puts("match\n :");
        for(i = pmatch[0].rm_so;i<pmatch[0].rm_eo;i++)
            putchar(buf[i]);
        putchar('\n');
    }

    regfree(&compiled);
    return 0;
}*/
