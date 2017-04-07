#define _ADDNAME_
#define _DESTORYNAME_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "folder.h"

#include "link.h"
#define SEARCH_PATH_INFO


destoryName(int,file,struct sfn**,head)
destoryName(int,folder,struct sfn**,head)

int addName(struct sfn** head,const char* name)
{
    struct sfn* p = NULL;
    struct sfn* ps = NULL;
    if(*head == NULL)
    {
        *head = (tsfn*) malloc(sizeof(tsfn));
        (*head)->name = (char*) malloc(sizeof(char)*strlen("head"));
        (*head)->next = NULL;
    }
    ps = (*head);
    p = ps->next;
    while(p)
    {
        ps = p;
        p = ps->next;
    }
    ps->next = (tsfn*) malloc(sizeof(tsfn));
    ps->next->name = (char*) malloc(sizeof(char)*(strlen(name)+1));
    strcpy(ps->next->name,name);
    ps->next->next = NULL;
    return 0;
}
int addFolder(struct folder** head,struct folder* pfolder)
{
    struct folder* p = NULL;
    if(*head == NULL)
    {
        *head = (struct folder*)malloc(sizeof(struct folder));
        (*head)->next = NULL;
    }
    if(pfolder == NULL)
        return -1;
    p = (*head);
    while(p->next!=NULL)
    {
        p = p->next;
    }
    p->next = pfolder;
    return 0;
}
/*
    pfolder不会为空
    pfolder->namehead 如果为NULL,说明没有子文件,那么返回空HEAD
    注意返回值:head 没有显示的内容
*/
struct folder* creatSonFolderList(struct folder* pfolder)
{
    struct folder* head = NULL;

    struct folder* p = NULL;
    struct folder* np = NULL;
    struct sfn* foldername = pfolder->foldernamelhead;
    char* name = (char* )malloc(sizeof(char)*FILENAME_MAX);

    if(foldername == NULL)
    {
        free(name);
        return NULL;
    }
    //说明存在子文件夹
    head = (struct folder*)malloc(sizeof(struct folder));
    head->next = NULL;
    p = head;
    while(foldername->next!=NULL)
    {
        strcpy(name,pfolder->curwd);
        strcat(name,"\\");
        foldername = foldername->next;
        strcat(name,foldername->name);

        np = getfolderproperty(name); //根据文件名创建文件节点
        p->next = np;
        p = np;
    }

    free(name);
    return head;
}
void mixList(struct folder** head,struct folder* list_head)
{
    struct folder* p = NULL;
    if(*head == NULL)
    {
        *head = (struct folder*) malloc(sizeof(struct folder));  //表头不放东西的哟
        (*head) ->next = NULL;
    }
    p = (*head);
    while(p->next != NULL)
    {
        p = p->next;
    }
    if(list_head != NULL)
    {
        p->next = list_head->next;   ///头结点没有啥玩意,需要释放
        free(list_head);
    }
}
int destoryList(struct folder** head)
{
    struct folder*  p = *head;
    struct folder*  dp = NULL;
    if(p == NULL)
        return 0;
    dp = p;          //说明有子文件 第一个节点肯定不为NULL，不用引起访问错误
    p = p->next;
    free(dp);       //头结点没有内容，需要特殊处
    *head = NULL;
    while(p!= NULL)
    {
        dp = p;
        p = p->next;
        destroyFolderNode(dp);   //释放节点
    }
    return 0;
}
int printName(tsfn* head)
{
    tsfn* p = NULL;
    if(head == NULL)
    {
        return -1;
    }
    p = head->next;
    while( p!=NULL )
    {
        printf("%s\n",p->name);
        p = p->next;
    }
    return 0;
}
int printFolderlist(struct folder* head)
{
    struct folder* p = head;
    if(head == NULL)
    {
        puts("list is empty");
        return -1;
    }
    while(p->next != NULL)
    {
        p = p->next;
        printf("this node name:%s,filenum:%d,son-foldernum:%d\n",p->property.name,p->filenum,p->foldernum);
        puts("file:");
        printName(p->filenamelhead);
        puts("folder:");
        printName(p->foldernamelhead);
    }
    return 0;
}
