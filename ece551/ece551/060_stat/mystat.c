#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}
//get the file type and return it
char * getFileType(struct stat buf) {
  char * str = NULL;
  switch (buf.st_mode & S_IFMT) {
    case S_IFBLK:
      str = "block special file";
      break;
    case S_IFCHR:
      str = "character special file";
      break;
    case S_IFDIR:
      str = "directory";
      break;
    case S_IFIFO:
      str = "fifo";
      break;
    case S_IFLNK:
      str = "symbolic link";
      break;
    case S_IFREG:
      str = "regular file";
      break;
    case S_IFSOCK:
      str = "socket";
      break;
    default:
      str = "unknown?";
      break;
  }
  return str;
}
//print rest of the first line
void print_firstLine(struct stat buf, char * str) {
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         buf.st_size,
         buf.st_blocks,
         buf.st_blksize,
         str);
  if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode)) {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n\
",
           buf.st_dev,
           buf.st_dev,
           buf.st_ino,
           buf.st_nlink,
           major(buf.st_rdev),
           minor(buf.st_rdev));
  }
  else {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
           buf.st_dev,
           buf.st_dev,
           buf.st_ino,
           buf.st_nlink);
  }
}
//print the access information
void forthLine(struct stat buf) {
  char access[80];
  unsigned int octal = buf.st_mode & (~S_IFMT);

  switch (buf.st_mode & S_IFMT) {
    case S_IFBLK:
      access[0] = 'b';
      break;
    case S_IFCHR:
      access[0] = 'c';
      break;
    case S_IFDIR:
      access[0] = 'd';
      break;
    case S_IFIFO:
      access[0] = 'p';
      break;
    case S_IFLNK:
      access[0] = 'l';
      break;
    case S_IFREG:
      access[0] = '-';
      break;
    case S_IFSOCK:
      access[0] = 's';
      break;
    default:
      access[0] = ' ';
      break;
  }
  //bit 2
  if ((buf.st_mode & S_IRUSR) == 0) {
    access[1] = '-';
  }
  else {
    access[1] = 'r';
  }
  //bit 3
  if ((buf.st_mode & S_IWUSR) == 0) {
    access[2] = '-';
  }
  else {
    access[2] = 'w';
  }
  //bit 4
  if ((buf.st_mode & S_IXUSR) == 0) {
    access[3] = '-';
  }
  else {
    access[3] = 'x';
  }
  //bit 5,6,7
  if ((buf.st_mode & S_IRGRP) == 0) {
    access[4] = '-';
  }
  else {
    access[4] = 'r';
  }
  if ((buf.st_mode & S_IWGRP) == 0) {
    access[5] = '-';
  }
  else {
    access[5] = 'w';
  }
  if ((buf.st_mode & S_IXGRP) == 0) {
    access[6] = '-';
  }
  else {
    access[6] = 'x';
  }
  //bit 8,9,10
  if ((buf.st_mode & S_IROTH) == 0) {
    access[7] = '-';
  }
  else {
    access[7] = 'r';
  }
  if ((buf.st_mode & S_IWOTH) == 0) {
    access[8] = '-';
  }
  else {
    access[8] = 'w';
  }
  if ((buf.st_mode & S_IXOTH) == 0) {
    access[9] = '-';
  }
  else {
    access[9] = 'x';
  }
  access[10] = '\0';
  printf("Access: (%04o/%s)", octal, access);
}
//print uid and guid
void uid(struct stat buf) {
  struct passwd * password = getpwuid(buf.st_uid);
  struct group * group = getgrgid(buf.st_gid);
  printf("  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
         buf.st_uid,
         password->pw_name,
         buf.st_gid,
         group->gr_name);
}
//print time
void lastFourLines(struct stat buf) {
  char * timestr = time2str(&buf.st_atime, buf.st_atim.tv_nsec);
  printf("Access: %s\n", timestr);
  free(timestr);
  char * timestr1 = time2str(&buf.st_mtime, buf.st_mtim.tv_nsec);
  printf("Modify: %s\n", timestr1);
  free(timestr1);
  char * timestr2 = time2str(&buf.st_ctime, buf.st_ctim.tv_nsec);
  printf("Change: %s\n", timestr2);
  free(timestr2);
  printf(" Birth: -\n");
}
int main(int argc, char ** argv) {
  struct stat buf;
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  // get the infomation of file. and print all input file information
  for (int i = 1; i < argc; i++) {
    if (argv[i] == NULL) {
      perror("Invalid input argument");
      return EXIT_FAILURE;
    }
    if (lstat(argv[i], &buf) == -1) {
      fprintf(stderr, "stat: cannot stat '%s': ", argv[i]);
      perror("");
      return EXIT_FAILURE;
    }
    // check if input file is smybolic link and print correct file name
    if (S_ISLNK(buf.st_mode)) {
      char linktarget[256];
      ssize_t len = readlink(argv[i], linktarget, 256);
      if (len == -1) {
        perror("something wrong with readlink!");
        return EXIT_FAILURE;
      }
      if (len > 255) {
        fprintf(stderr, "wrong size!");
        return EXIT_FAILURE;
      }
      linktarget[len] = '\0';
      printf("  File: %s -> %s\n", argv[i], linktarget);
    }
    else {
      printf("  File: %s\n", argv[i]);
    }
    char * str = NULL;
    str = getFileType(buf);
    print_firstLine(buf, str);
    forthLine(buf);
    uid(buf);
    lastFourLines(buf);
  }
  return EXIT_SUCCESS;
}
