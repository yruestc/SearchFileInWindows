#ifndef _CMD_H_
#define _CMD_H_
#include <limits.h>
#define SRCH_PARA_REG   	0        //bit for regular expression
#define SRCH_PARA_PATHINFO  1        //bit for search-path-info
#define SRCH_PARA_FILEINFO  2		 //bit for file-info:time size type
#define SRCH_PARA_MTCHSTRCT 3        //—œ∏Ò∆•≈‰
//...
#define SRCH_TYPE_FILE 		4        //bit for file or folder
#define SRCH_TYPE_FOLDER    5

#define PARA_NUM            4

typedef struct srchinfo
{
	int paraflag;
	char name[FILENAME_MAX];
	char path[PATH_MAX];
}tsrchinfo;
void helpMsg();
struct srchinfo* getSrchInfo(char* name,char* path,int paraflag);
struct srchinfo* getParameter(int argc,char** argv);
void prinSrchInfo(struct srchinfo* p);
#endif // _CMD_H_
