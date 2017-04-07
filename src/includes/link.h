#ifndef _LINK_H_
#define _LINK_H_

#include "folder.h"
#include <string.h>

#ifdef _DESTORYNAME_
#define destoryName(type,fn,atype,a) \
type destoryName_##fn(atype a)\
{\
    tsfn* p = NULL;\
    tsfn* fp = NULL;\
    if( (*a) == NULL )\
        return -1;\
    fp = *a;\
    p = fp->next;\
    free(fp);\
    while( p != NULL )\
    {\
        fp = p;\
        p = p->next;\
        free(fp->name);\
        free(fp);\
    }\
    return 0;\
}

#endif
typedef struct sfn
{
	char* name;
	struct sfn* next;
}tsfn;



int addName(struct sfn**,const char*);  ///#define on above

int destoryName_folder(struct sfn**);
int destoryName_file(struct sfn**);
int printName(tsfn* head);
struct folder* creatSonFolderList(struct folder* pfolder);
int printFolderlist(struct folder* head);
int destoryList(struct folder** head);
void travel_aLayer(struct folder* head);
void travel_LayerByLayer(struct folder* root_layer);
void mixList(struct folder** head,struct folder* list_head);
#endif
