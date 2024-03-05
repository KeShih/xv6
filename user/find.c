#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path, char *name){
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    fd = open(path, 0);
    fstat(fd, &st);

    switch(st.type){
    case T_FILE:
        fprintf(2, "Usage: find <path> <name>\n");
        exit(1);
    case T_DIR:
        strcpy(buf,path);
        p = buf+strlen(buf);
        *p++ = '/';
        while(read(fd,&de,sizeof(de)) == sizeof(de)){
            if(de.inum == 0)
                continue;
            memmove(p,de.name,DIRSIZ);
            p[DIRSIZ] = 0;
            stat(buf,&st);
            switch (st.type)
            {
            case T_FILE:
                if(strcmp(name,de.name) == 0)
                    printf("%s\n",buf);
                break;
            case T_DIR:
                if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
                    continue;
                find(buf,name);
                break;
            }            
        }
    }
    close(fd);
}

int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(2, "Usage: find <path> <name>\n");
        exit(1);
    }
    find(argv[1], argv[2]);
    exit(0);
}