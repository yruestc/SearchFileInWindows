#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmd.h"
#include <io.h>
#define ERROR 			   -1


void setParaBit(int* paraflag,int bit)
{
	*paraflag |= (0x01<<bit);
}
void resetParaBit(int* paraflag,int bit)
{
	*paraflag &= (~(0x01<<bit));
}

/*
    you can add any opt in here,but don't forget add corresponding to the parameters of the function in srch.c,
and change PARA_NUM in srch.h,Thank you for reading,good luck!
*/
char* parameterlist[] =
{
	"-reg",
	"-pathinfo",
	"-fileinfo",
    "...", //no use
	//...
	//...
	"-file",
	"-folder"
};

int srchPara(char* name)
{
	char* paraname = name;
	int i ;
	for(i=0;i<PARA_NUM;i++)
		if(strcmp(paraname,parameterlist[i]) == 0)
			return i;
	return -1;
}
struct srchinfo* getParameter(int argc,char** argv)
{
	int i;
	int para_index;
	int paraflag = 0x00;
	char* str_index = NULL;
	char name[FILENAME_MAX];
	char path[PATH_MAX];
	struct srchinfo* pinfo = NULL;
	if(argc < 2)
		return NULL;
	for(i=1;i<argc;i++)   //ignor argv[0]
	{
		str_index = argv[i];
		if(*str_index == '-')
		{
			if(strcmp(str_index,"-file") == 0 )
			{
				setParaBit(&paraflag,SRCH_TYPE_FILE);
				resetParaBit(&paraflag,SRCH_TYPE_FOLDER);
				if(argv[i+1]== NULL)
					return NULL;
				strcpy(name,argv[i+1]);
				name[strlen(name)] = '\0';
				i++; //jump next
			}
			else if(strcmp(str_index,"-folder")==0)
			{
				setParaBit(&paraflag,SRCH_TYPE_FOLDER);
				resetParaBit(&paraflag,SRCH_TYPE_FILE);
				if(argv[i+1]== NULL)
					return NULL;
				strcpy(name,argv[i+1]);
				name[strlen(name)] = '\0';
				i++;
			}
			else
			{
				para_index = srchPara(argv[i]);
				if(para_index == -1)
                {
                    puts("srch error");
                    return NULL;
                }
				setParaBit(&paraflag,para_index);
			}

		}
		else
			strcpy(path,argv[i]);
	}
	if( (paraflag & (0x01<<SRCH_PARA_REG)) == 0)  //如果没有正则表达式
    {
        setParaBit(&paraflag,SRCH_PARA_MTCHSTRCT);
    }
	//int checkParameter();
	if(strcmp(path,".\\") == 0)
	{
	    memset(path,'\0',strlen(path));
	    getcwd(path,PATH_MAX+1);
	    path[strlen(path)] = '\0';
	}

	pinfo =  getSrchInfo(name,path,paraflag);
    if(pinfo->name==NULL || pinfo->path==NULL)
    {
        free(pinfo);
        return NULL;
    }
	return pinfo;
}

//writing for debug only,and print some message

struct srchinfo* getSrchInfo(char* name,char* path,int paraflag)
{
	struct srchinfo* pinfo = (struct srchinfo*) malloc(sizeof(struct srchinfo));
	strcpy(pinfo->name,name);
	strcpy(pinfo->path,path);
	pinfo->paraflag = paraflag;

	return pinfo;
}
void printPara(int paraflag)
{
	int i;
	for(i = 0 ;i<PARA_NUM+2;i++)
	{
		if(paraflag&0x01)
		{
			printf("%s,",parameterlist[i]);
		}
		paraflag >>= 1;
	}
	putchar('\n');
}
void prinSrchInfo(struct srchinfo* p)
{
    if(p==NULL)
        return ;
    printf("parameter:");
    printPara(p->paraflag);
    printf("file:%s,path:%s\n",p->name,p->path);
}
void err_sys(const char* format)
{
    printf("error:");
    printf("%s\n",format);
}
void helpMsg()
{
    int i;
    puts("this tool is used to search file or folder");
    printf("some option now:\n");
    for(i = 0;i<PARA_NUM+2;i++)
        printf("        --%s\n",parameterlist[i]);
    printf("example: srchfile [-file filename] [opt...] [pathname(strict)]\n");
}

