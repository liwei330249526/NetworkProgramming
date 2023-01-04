#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>

#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#include <fcntl.h>           /* Definition of AT_* constants */
#include <sys/stat.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>



// 宏定义错误退出

// 更专业一点
#define ERR_EXIT(m) \
        do \
        {  \
            perror(m); \
            exit(EXIT_FAILURE); \
        }while(0)

#define MAJOR(a) ((int)((unsigned short)a >> 8))            // 高8位
#define MINOR(a) ((int)((unsigned short)a & 0xff))         // 低8位

int printFileInfo(int argc, char *argv[]) ;
void fileperm(struct stat *buf, char *perm);


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usase %s file\n", argv[0]);            // 提示用法, ./01stat file
        exit(EXIT_FAILURE);
    }
    printf("Filename:%s\n", argv[1]);

    struct stat sbuf;
    if (lstat(argv[1], &sbuf) == -1) {
        ERR_EXIT("stat error");
    }

    printf("主:%d, 次:%d, st_ino:%d\n", MAJOR(sbuf.st_dev), MINOR(sbuf.st_dev), (int)sbuf.st_ino);

    char perm[11];

    fileperm(&sbuf, perm);
    printf("File permission bits = %o _ %s\n", sbuf.st_mode & 07777, perm);

    printFileInfo(argc, argv);

    exit(EXIT_SUCCESS);
}


int printFileInfo(int argc, char *argv[]) {
    struct stat sb;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (lstat(argv[1], &sb) == -1) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }

    printf("ID of containing device:  [%jx,%jx]\n",
            (uintmax_t) major(sb.st_dev),
            (uintmax_t) minor(sb.st_dev));

    printf("File type:                ");

    switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:  printf("block device\n");            break;
    case S_IFCHR:  printf("character device\n");        break;
    case S_IFDIR:  printf("directory\n");               break;
    case S_IFIFO:  printf("FIFO/pipe\n");               break;
    case S_IFLNK:  printf("symlink\n");                 break;
    case S_IFREG:  printf("regular file\n");            break;
    case S_IFSOCK: printf("socket\n");                  break;
    default:       printf("unknown?\n");                break;
    }

    printf("I-node number:            %ju\n", (uintmax_t) sb.st_ino);

    printf("Mode:                     %jo (octal)\n",
            (uintmax_t) sb.st_mode);

    printf("Link count:               %ju\n", (uintmax_t) sb.st_nlink);
    printf("Ownership:                UID=%ju   GID=%ju\n",
            (uintmax_t) sb.st_uid, (uintmax_t) sb.st_gid);

    printf("Preferred I/O block size: %jd bytes\n",
            (intmax_t) sb.st_blksize);
    printf("File size:                %jd bytes\n",
            (intmax_t) sb.st_size);
    printf("Blocks allocated:         %jd\n",
            (intmax_t) sb.st_blocks);

    printf("Last status change:       %s", ctime(&sb.st_ctime));
    printf("Last file access:         %s", ctime(&sb.st_atime));
    printf("Last file modification:   %s", ctime(&sb.st_mtime));

    exit(EXIT_SUCCESS);


}

void fileperm(struct stat *buf, char *perm) {
    strcpy(perm, "----------");
    perm[0] = '?';

    mode_t  mode;
    mode = buf->st_mode;
    switch (mode & S_IFMT)
    {
    case S_IFSOCK:
        perm[0] = 's';
        break;
    case S_IFLNK:
        perm[0] = 'l';
        break;
    case S_IFREG:
        perm[0] = '-';
        break;
    case S_IFBLK:
        perm[0] = 'b';
        break;
    case S_IFDIR:
        perm[0] = 'd';
        break;
    case S_IFCHR:
        perm[0] = 'c';
        break;
    case S_IFIFO:
        perm[0] = 'p';
        break;
    default:
        break;
    }

    if(mode & S_IRUSR) {
        perm[1] = 'r';
    }
    if(mode & S_IWUSR) {
        perm[2] = 'w';
    }
    if(mode & S_IXUSR) {
        perm[3] = 'x';
    }

    if(mode & S_IRGRP) {
        perm[4] = 'r';
    }
    if(mode & S_IWGRP) {
        perm[5] = 'w';
    }
    if(mode & S_IXGRP) {
        perm[6] = 'x';
    }

    if(mode & S_IROTH) {
        perm[7] = 'r';
    }
    if(mode & S_IWOTH) {
        perm[8] = 'w';
    }
    if(mode & S_IXOTH) {
        perm[9] = 'x';
    }

    perm[10] = '\0';
}

