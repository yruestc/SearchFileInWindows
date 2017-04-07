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
    pfolder����Ϊ��
    pfolder->namehead ���ΪNULL,˵��û�����ļ�,��ô���ؿ�HEAD
    ע�ⷵ��ֵ:head û����ʾ������
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
    //˵���������ļ���
    head = (struct folder*)malloc(sizeof(struct folder));
    head->next = NULL;
    p = head;
    while(foldername->next!=NULL)
    {
        strcpy(name,pfolder->curwd);
        strcat(name,"\\");
        foldername = foldername->next;
        strcat(name,foldername->name);

        np = getfolderproperty(name); //�����ļ��������ļ��ڵ�
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
        *head = (struct folder*) malloc(sizeof(struct folder));  //��ͷ���Ŷ�����Ӵ
        (*head) ->next = NULL;
    }
    p = (*head);
    while(p->next != NULL)
    {
        p = p->next;
    }
    if(list_head != NULL)
    {
        p->next = list_head->next;   ///ͷ���û��ɶ����,��Ҫ�ͷ�
        free(list_head);
    }
}
int destoryList(struct folder** head)
{
    struct folder*  p = *head;
    struct folder*  dp = NULL;
    if(p == NULL)
        return 0;
    dp = p;          //˵�������ļ� ��һ���ڵ�϶���ΪNULL������������ʴ���
    p = p->next;
    free(dp);       //ͷ���û�����ݣ���Ҫ���⴦
    *head = NULL;
    while(p!= NULL)
    {
        dp = p;
        p = p->next;
        destroyFolderNode(dp);   //�ͷŽڵ�
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
