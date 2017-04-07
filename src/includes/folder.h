#ifndef _FOLDER_H_
#define _FOLDER_H_

#include <io.h>
#include "link.h"

#define FOLDER_SIGN     0x01
#define FILE_SIGN       0X02
#define NOFILE          0x04
#define ERROR_INPUT     0x08

typedef struct folder{
    struct _finddata_t property;                   //�ļ�������
    char* curwd;                                   //��ǰ·��
    int   filenum;                                 //���ļ�����
    int   foldernum;                               //���ļ�����
    struct sfn* filenamelhead;                     //���ļ���������ͷ���
    struct sfn* foldernamelhead;                   //���ļ�����������ͷ���
    struct folder* next;
}tfolder;

int isfolder(const char* name);
struct folder* getfolderproperty(const char* path);
void printFolderProperty(struct folder* pfolder);
int destroyFolderNode(struct folder* pfolder);
#endif // _ISFOLDER_H_

