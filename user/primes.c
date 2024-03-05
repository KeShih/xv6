#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(){
    int p[2];
    int q[2];
    pipe(p);
    int pid = fork();
    if(pid == 0){
        close(p[1]);
        int n;
        int first = 1;
        int fork_flag = 1;
        int prime;
        while(read(p[0], &n, sizeof(n))){
            if(first){
                prime = n;
                fprintf(1, "prime %d\n", prime);
                first = 0;
            }
            if(n % prime != 0){
                if(fork_flag){
                    pipe(q);
                    if(fork() == 0){
                        close(q[1]);
                        close(p[0]);
                        p[0] = q[0];
                        fork_flag = 1;
                        first = 1;
                    } else {
                        close(q[0]);
                        fork_flag = 0;
                    }
                }
                write(q[1], &n, sizeof(n));
            }
        }
        close(p[0]);
        if(fork_flag == 0){
            close(q[1]);
            wait(0);
        }
    } else {
        close(p[0]);
        for(int i = 2; i <= 35; i++)
            write(p[1], &i, sizeof(i));
        close(p[1]);
        wait(0);
    }
    exit(0);
}