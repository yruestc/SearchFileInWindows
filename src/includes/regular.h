#ifndef _REGULAR_H_
#define _REGULAR_h_
#include <regex.h>
#define REG_MATCH_HALF          0x10
#define REG_MATCH_ALL           0x11
#define REG_COMPILE_ERROR       0x12
int regtest();
int reg_analyze(const char* pattern,const char* tar);
#endif // _REGULAR_H_
