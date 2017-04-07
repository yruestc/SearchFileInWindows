#ifndef _FOLDER_H_
#define _FOLDER_H_

#include <io.h>
#include "link.h"

#define FOLDER_SIGN     0x01
#define FILE_SIGN       0X02
#define NOFILE          0x04
#define ERROR_INPUT     0x08

typedef struct folder{
    struct _finddata_t property;                   //文件夹属性
    char* curwd;                                   //当前路径
    int   filenum;                                 //子文件数量
    int   foldernum;                               //子文件数量
    struct sfn* filenamelhead;                     //子文件名字链表头结点
    struct sfn* foldernamelhead;                   //子文件夹名字链表头结点
    struct folder* next;
}tfolder;

int isfolder(const char* name);
struct folder* getfolderproperty(const char* path);
void printFolderProperty(struct folder* pfolder);
int destroyFolderNode(struct folder* pfolder);
#endif // _ISFOLDER_H_

