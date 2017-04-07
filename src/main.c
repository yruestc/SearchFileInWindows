#include <stdio.h>
#include <stdlib.h>

#include "link.h"
#include "folder.h"
#include "regular.h"
#include "cmd.h"
#include "srch.h"

/*open source,you can use any. ^_^ */
/*I write this tool is to solve practical problems*/

int main(int argc,char* argv[])
{
    struct folder* head = (struct folder* ) malloc(sizeof(struct folder));
    struct srchinfo* pinfo = NULL;
    if(argc<2)
    {
        puts("error input");
        exit(-1);
    }
    if(strcmp(argv[1],"--help")==0)
    {
        helpMsg();
        exit(0);
    }

    pinfo = getParameter(argc,&argv[0]);
    if(pinfo==NULL)
    {
        helpMsg();
        exit(0);
    }
    head->next = getfolderproperty(pinfo->path);
    srch(head,pinfo);   //会释放所有申请的内存,I'm not sure

    exit(0);
}
