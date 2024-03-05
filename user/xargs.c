#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

// comand | xargs command
int main(int argc,char** argv){
    char* xargv[MAXARG];
    for(int i=1; i<argc; i++){
        xargv[i-1] = (char*)malloc(strlen(argv[i])+1);
        strcpy(xargv[i-1],argv[i]);
    }
    char* buf = (char*)malloc(512);
    xargv[argc] = 0;
    xargv[argc-1] = buf;
    char c;
    int cnt = 0;
    while(read(0,&c,1)==1){
        if(c == '\n'){
            if(fork() == 0){
                buf[cnt] = 0;
                exec(xargv[0],xargv);
            }else{
                wait(0);
                cnt = 0;
            }
        }else{
            buf[cnt++] = c;
        }
    }
    exit(0);
}