#include <stdio.h>
#include <stdlib.h>
#include "search.h"
#include "folder.h"
#include "cmd.h"
#include "regular.h"
#include "link.h"

/*add function at this file */


static void srch_func_reg(struct folder* pf,struct srchinfo* pinfo);
static void srch_func_pathinfo(struct folder* pf,struct srchinfo* pinfo);
static void srch_func_fileinfo(struct folder* pf,struct srchinfo* pinfo);
static void srch_func_mtchstrct(struct folder* pf,struct srchinfo* pinfo);

/*you can add any function in this array,and add opt at cmd.c*/
void (*para_func[])(struct folder*,struct srchinfo*) =
{
	srch_func_reg,
	srch_func_pathinfo,
	srch_func_fileinfo,
	srch_func_mtchstrct
	//...
};
/*typedef struct tarfile
{
    char name[FILENAME_MAX];
    char path[PATH_MAX];
    struct tarfile* next;
}t_tarfile;
t_tarfile filebuf = {"error","error-path",NULL};*/


//regular expression
void srch_func_reg(struct folder* pf,struct srchinfo* pinfo)
{
    //t_tarfile* pfilebuf_node = &filebuf;
	char* name_srch = pinfo->name;
	tsfn* name_actul = NULL;
	if(pinfo->paraflag&(0x01<<SRCH_TYPE_FILE)) //srch file
		name_actul = pf->filenamelhead;
	else
		name_actul = pf->foldernamelhead;           //search folder
	while(name_actul!=NULL)
	{
	    if(reg_analyze(name_srch,name_actul->name)==REG_MATCH_ALL)  //if match,print info
        {
            if((pinfo->paraflag&(0x01<<SRCH_PARA_FILEINFO))==0)
                printf("%s %s\n",pf->curwd,name_actul->name);
        }
		name_actul = name_actul->next;
	}
}
void srch_func_mtchstrct(struct folder* pf,struct srchinfo* pinfo)
{
	char* name_srch = pinfo->name;
	tsfn* name_actul = NULL;
	if(pinfo->paraflag&(0x01<<SRCH_TYPE_FILE)) //srch file
		name_actul = pf->filenamelhead;
	else
		name_actul = pf->foldernamelhead;           //search folder
	while(name_actul!=NULL)
	{
		if(strcmp(name_actul->name,name_srch) ==0 )  //if match,print info
			printf("%s %s\n",pf->curwd,name_actul->name);
        /*you can uncomment so that you can sue the higher-end features*/
        //while(pfilebuf_node->next!=NULL)
        //{
        //    pfilebuf_node = pfilebuf_node->next;
        //}
        //pfilebuf_node = (t_tarfile*)malloc(sizeof(t_tarfile));
        //strcpy(pfilebuf_node->name , name_actul->name);
        //strcpy(pfilebuf_node->path , pf->curwd);
        //pfilebuf_node->next = NULL;*/
        name_actul = name_actul->next;
	}
}
void srch_func_fileinfo(struct folder* pf,struct srchinfo* pinfo)
{
	//printf("in srch_func_fileinfo\n");
}
void srch_func_pathinfo(struct folder* pf,struct srchinfo* pinfo)
{
	//printf("in srch_func_pathinfo\n");
}
//search target file in a layer
int srchAlayer(struct folder* pf_head,struct srchinfo* pinfo)
{
	struct folder* pf = pf_head->next;
	int paraflag = pinfo->paraflag;
    int i ;
	while(pf!=NULL)
	{
		for(i = 0;i<PARA_NUM;i++)
		{
			if(paraflag&0x00000001)
			{
				para_func[i](pf,pinfo);
			}
			paraflag >>= 1;
		}
		pf = pf->next;
		paraflag = pinfo->paraflag;
	}
	return 0;
}

void srch(struct folder* root_layer,struct srchinfo* pinfo)
{
    struct folder* son_head_list = NULL;
    struct folder* son = NULL;
    struct folder* nextlayer = NULL;
    if(root_layer == NULL)   //如果表头存在那么肯定会有第一个元素
        return ;
    srchAlayer(root_layer,pinfo);
    son = root_layer;
    while(son->next != NULL)  //while循环建立下一层
    {
         son = son->next;
         son_head_list = creatSonFolderList(son);  //即使是空表，下层函数会处理
         mixList(&nextlayer,son_head_list);        //建立第二层
    }
    destoryList(&root_layer);                      //销毁已经失去作用的表
    srch(nextlayer,pinfo);
}
