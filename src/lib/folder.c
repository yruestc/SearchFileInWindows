#include "folder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <io.h>          //_find first _find next  getcwd
#include <sys/stat.h>    //_stat

#define UANOMAL  (-1)
//�ж��ļ��л����ļ�
int isfolder(const char* name)
{
    struct _stat buf;
    if(name == NULL)
        return ERROR_INPUT;
    if( _stat( name, &buf ) == -1) //error
    {
        printf("error:no this file or folder <%s>\n",name);
        return NOFILE;
    }

    if(_S_IFDIR & buf.st_mode)
    {
        return FOLDER_SIGN;
    }
    else if(_S_IFREG & buf.st_mode)
    {
        return FILE_SIGN;
    }
    puts("error:i don't know what it is");
    while(1);
    return UANOMAL;
}
void cpyfinddata(struct _finddata_t* f1,struct _finddata_t* f2)
{
    strcpy(f1->name     ,   f2->name);

    f1->attrib          =   f2->attrib;
    f1->size            =   f2->size;
    f1->time_access     =   f2->time_access;
    f1->time_create     =   f2->time_create;
    f1->time_write      =   f2->time_write;
}
char* getpath()
{
    int size = 0;
    char* cur = (char*) malloc(sizeof(char)*FILENAME_MAX);
    char* scur = NULL;
    getcwd(cur,FILENAME_MAX);
    size = strlen(cur);
    if(!size)
        return NULL;
    scur = (char*) malloc(sizeof(char)*size+1);  ///��һ��Ϊ������Ŀ¼��ż��BUG
    strcpy(scur,cur);
    free(cur);

    return scur;
}
void initFolderNode(struct folder* pfolder)
{
    //pfolder->curwd = NULL;
    pfolder->filenum   = 0   ;
    pfolder->foldernum = 0   ;
    pfolder->filenamelhead = NULL;
    pfolder->foldernamelhead = NULL;
}
struct folder* getfolderproperty(const char* path)
{
    struct _finddata_t file;
    struct folder* pfolder = NULL;
    char* name = NULL;
    long lf;
    int filetype;

    if(isfolder(path)!= FOLDER_SIGN) ///����Ҳ���,���ؿ�
        return NULL;
    chdir(path);                     ///�л�������·
    lf = _findfirst(path,&file);     ///�϶������ҵ�
    pfolder = (tfolder*) malloc(sizeof(tfolder));
    cpyfinddata(&(pfolder->property),&file);
    pfolder->curwd = getpath();      ///�����Ŀ¼��ַ

    name = (char* ) malloc(sizeof(char)* FILENAME_MAX);
    strcpy(name,pfolder->curwd);
    strcat(name,"\\*");              ///�����ļ�/�ļ���
    lf = _findfirst(name,&file);
    initFolderNode(pfolder);
    while(_findnext(lf, &file) == 0)
    {
        if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0)
            continue;
        filetype = isfolder(file.name);
        if(filetype == FOLDER_SIGN)
        {
            //printf("%s will add\n",file.name);
            addName(&(pfolder->foldernamelhead),file.name);    ///������ļ��е�����
            //printf("%s has add\n",file.name);
            pfolder->foldernum++;
        }
        else if(filetype == FILE_SIGN)
        {
            addName(&(pfolder->filenamelhead),file.name);     ///������ļ�������
            pfolder->filenum++;
        }
        else  ///δ֪��ԭ�����,��������:�ļ������в���ascii���ϵ��ַ�
        {
            void err_msg(const char* path,struct _finddata_t file);
            err_msg(path,file);
        }
    }
    pfolder->next = NULL;
    free(name);
    return pfolder;
}
int destroyFolderNode(struct folder* pfolder)
{
    if(pfolder == NULL)
        return -1;
    free(pfolder->curwd);  ///������ֻҪfolder����,���ָ��Ͳ���Ϊ��,��Ӧ�ж�
    destoryName_folder(&(pfolder->foldernamelhead));
    destoryName_file(&(pfolder->filenamelhead));
    free(pfolder);
    return 0;
}
void printFolderProperty(struct folder* pfolder)
{
    printf("this folder<%s> has %d son-folder,%d file:\n",pfolder->curwd,pfolder->foldernum,pfolder->filenum);
    printName(pfolder->foldernamelhead);
    printName(pfolder->filenamelhead);
}
void err_msg(const char* path,struct _finddata_t file)
{
    printf("error:%s,%d\n",__FILE__,__LINE__);
    printf("error file:%s,press any key to continue\n",file.name);
    puts(path);
    getchar();
}
