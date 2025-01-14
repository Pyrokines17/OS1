#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define bufSize 1024

void outFile(char *name) {
  char* buffer = (char*)calloc(bufSize, sizeof(char));
  FILE *ptr = fopen(name, "rb");
  int retSym;

  if (ptr == NULL) {
    fprintf(stderr, "Error occurred while reading a file: %s\n", strerror(errno));
    return;
  }

  while ((retSym = fread(buffer, sizeof(char), bufSize, ptr)) == bufSize) {
    printf("%s", buffer);
  }

  for (int i = 0; i < retSym; ++i) {
    printf("%c", buffer[i]);
  }

  fclose(ptr);
}

void myMkdir(int argc, char **argv) {
  if (argc == 1) {
    fprintf(stderr, "need name\n");
    return;
  }

  if (mkdir(argv[1], S_IRWXU | S_IRWXG | S_IRWXO)) fprintf(stderr, "Error in mkdir: %s\n", strerror(errno));
}

void myLs(int argc, char **argv) {
  if (argc == 1) {
    fprintf(stderr, "need dir\n");
    return;
  }

  struct dirent *ep;
  DIR *dp;

  dp = opendir(argv[1]);

  if (dp != NULL) {
    while ((ep = readdir(dp)) != NULL) puts(ep->d_name);

    closedir(dp);

  } else {

    fprintf(stderr, "Error in ls: %s\n", strerror(errno));
  }
}

void myRmdir(int argc, char **argv) {
  if (argc == 1) {
    fprintf(stderr, "need dir\n");
    return;
  }

  if (rmdir(argv[1])) fprintf(stderr, "Error in rmdir: %s\n", strerror(errno));
}

void myTouch(int argc, char **argv) {
  if (argc == 1) {
    fprintf(stderr, "need name\n");
    return;
  }

  FILE *ptr = fopen(argv[1], "wb");

  if (ptr == NULL) {
    fprintf(stderr, "Error in touch: %s\n", strerror(errno));
    return;
  }

  fclose(ptr);
}

void myCat(int argc, char **argv) {
  if (argc == 1) {
    fprintf(stderr, "need name\n");
    return;
  }

  outFile(argv[1]);
}

void myRm(int argc, char **argv) {
  if (argc == 1) {
    fprintf(stderr, "need name\n");
    return;
  }

  if (remove(argv[1])) fprintf(stderr, "Error in rm: %s\n", strerror(errno));
}

void myLnS(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "need more argument's\n");
    return;
  }

  if (symlink(argv[1], argv[2])) fprintf(stderr, "Error in lnS: %s\n", strerror(errno));
}

void myCatLnS(int argc, char **argv) {
  if (argc == 1) {
    fprintf(stderr, "need name\n");
    return;
  }

  int size = 50;
  char *buffer = malloc(size);

  if (readlink(argv[1], buffer, size)) {
    fprintf(stderr, "Error in catLnS: %s\n", strerror(errno));
    return;

  } else {

    outFile(buffer);
  }
}

void myLn(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "need more argument's\n");
    return;
  }

  if (link(argv[1], argv[2])) fprintf(stderr, "Error in ln: %s\n", strerror(errno));
}

void myStat(int argc, char **argv) {
  if (argc == 1) {
    fprintf(stderr, "need name\n");
    return;
  }

  struct stat fs;

  if (stat(argv[1], &fs)) {
    fprintf(stderr, "Error in stat: %s\n", strerror(errno));
    return;
  }

  printf("%u -- mode\n\n", fs.st_mode);

  printf("File Permissions: \n");
    printf( (S_ISDIR(fs.st_mode)) ? "d" : "-");
    printf( (fs.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fs.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fs.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fs.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fs.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fs.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fs.st_mode & S_IROTH) ? "r" : "-");
    printf( (fs.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fs.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");

  printf("%lu -- count\n", fs.st_nlink);
}

void myChmod(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "need more argument's\n");
    return;
  }

  unsigned int mode[9] = {S_IRUSR, S_IWUSR, S_IXUSR, 
                          S_IRGRP, S_IWGRP, S_IXGRP, 
                          S_IROTH, S_IWOTH, S_IXOTH},
               result = 0;

  for (int i = 0; i < 3; ++i) {
    switch (argv[2][i] - '0') {
    case 1:
      result |= mode[3 * i + 2];
      continue;
    case 2:
      result |= mode[3 * i + 1];
      continue;
    case 4:
      result |= mode[3 * i];
      continue;
    case 5:
      result |= mode[3 * i + 2];
      result |= mode[3 * i];
      continue;
    case 6:
      result |= mode[3 * i + 1];
      result |= mode[3 * i];
      continue;
    case 7:
      result |= mode[3 * i + 2];
      result |= mode[3 * i + 1];
      result |= mode[3 * i];
      continue;
    default:
      fprintf(stderr, "mode not found(%d)\n", i);
      continue;
    }
  }

  if (chmod(argv[1], result)) fprintf(stderr, "Error in chmod: %s\n", strerror(errno));
}

int main(int argc, char **argv) {
  void (*operations[11])(int, char **) = {myMkdir, myLs,   myRmdir, myTouch,
                                          myCat,   myRm,   myLnS,   myCatLnS,
                                          myLn,    myStat, myChmod};
  char *namesOfOperations[11] = {
      "./myMkdir", "./myLs",     "./myRmdir", "./myTouch", "./myCat",  "./myRm",
      "./myLnS",   "./myCatLnS", "./myLn",    "./myStat",  "./myChmod"};

  for (int i = 0; i < 11; ++i) {
    if (!strcmp(namesOfOperations[i], argv[0])) {
      operations[i](argc, argv);
      return 0;
    }
  }

  fprintf(stderr, "operation not found\n");
  return 1;
}
