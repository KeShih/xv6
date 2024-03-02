#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(){
    int p[2];
    pipe(p);
    char buf[1] = "x";
    if(fork() == 0){
        read(p[0], buf, 1);
        printf("%d: received ping\n",getpid());
        write(p[1], buf, 1);
    } else {
        write(p[1], buf, 1);
        read(p[0], buf, 1);
        printf("%d: received pong\n",getpid());
    }
    exit(0);
}