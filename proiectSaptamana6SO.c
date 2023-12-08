#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct bmpHeader{
  char signature[2];
  int fileSize;
  int reserved;
  int dataOffset;
}bmpHeader;

struct bmpHeaderInfo{
  int size;
  int width;
  int height;
  }bmpHeaderInfo;

struct bmpHeader header;
struct bmpHeaderInfo headerInfo;

void setareDrepturiDeAcces(mode_t mod)
{
  if(mod & S_IWGRP)
    mod = ~S_IWGRP;
  if(mod & S_IXGRP)
    mod = ~S_IXGRP;
  if(mod & S_IWOTH)
    mod = ~S_IWOTH;
  if(mod & S_IXOTH)
    mod = ~S_IXOTH;
}

struct stat BUF;

int main(int argc, char *argv[])
{
  int f1 = 0, f2 = 0;
  if((f1 = open(argv[1], O_RDONLY)) < 0)
  {
    perror("Eroare deschidere fisier BMP!\n");
    exit(0);
  }

  if(argc > 2 && strcmp(argv[1], "poza.bmp") != 0)
  {
    char text[100];
    sprintf(text, "Usage %s %s\n", argv[0], argv[1]);
    perror(text);
    exit(1);
  }

  if((f2 = open("statistica.txt", O_WRONLY)) < 0)
  {
    perror("Eroare deschidere fisier iesire!\n");
    exit(2);
  }
  
  char buf[100];
  sprintf(buf, "nume fisier: %s\n", argv[1]);
  write(f2, buf, strlen(buf));
  strcpy(buf, " ");
  
  if(read(f1, &header, sizeof(header)) < 0)
  {
    perror("Eroare citire header fisier!\n");
    exit(3);
  }
  
  if(read(f1, &headerInfo, sizeof(headerInfo)) < 0)
  {
    perror("Eroare citire informatii header!\n");
    exit(4);
  }

  
  if(stat(argv[1], &BUF) != 0)
  {
    perror("Eroare!\n");
    exit(5);
  }

  sprintf(buf, "inaltime: %d\n", headerInfo.height);
  write(f2, buf, strlen(buf));
  strcpy(buf, " ");

  sprintf(buf, "lungime: %ld\n", BUF.st_blksize);
  write(f2, buf, strlen(buf));
  strcpy(buf, " ");
  
  sprintf(buf, "dimensiune: %ld\n", BUF.st_size);

  write(f2, buf, strlen(buf));
  strcpy(buf, " ");

  sprintf(buf, "identificatorul utilizatorului: %d\n", BUF.st_uid);
  write(f2, buf, strlen(buf));
  strcpy(buf, " ");
  time_t time = BUF.st_mtime;
  struct tm *data = localtime(&time);

  sprintf(buf, "timpul ultimei modificari: %d.%d.%d\n", data -> tm_mday, data -> tm_mon + 1, data -> tm_year + 1900);
  write(f2, buf, strlen(buf));
  strcpy(buf, " ");

  sprintf(buf, "contorul de legaturi: %ld\n", BUF.st_nlink);
  write(f2, buf, strlen(buf));
  strcpy(buf, " ");
  char drepturiAcces[3];

  setareDrepturiDeAcces(BUF.st_mode);  
  
  if(BUF.st_mode & S_IRUSR)
    drepturiAcces[0] = 'R';
  else
    drepturiAcces[0] = '-';
  if(BUF.st_mode & S_IWUSR)
    drepturiAcces[1] = 'W';
  else
    drepturiAcces[1] = '-';
  if(BUF.st_mode & S_IXUSR)
    drepturiAcces[2] = 'X';
  else
    drepturiAcces[2] = '-';
  drepturiAcces[3] = '\0';
  
  sprintf(buf, "drepturi de acces user: %s\n", drepturiAcces);
  write(f2, buf, strlen(buf));
  strcpy(buf, " ");

  if(BUF.st_mode & S_IRGRP)
    drepturiAcces[0] = 'R';
  else
    drepturiAcces[0] = '-';
  if(BUF.st_mode & S_IWGRP)
    drepturiAcces[1] = 'W';
  else
    drepturiAcces[1] = '-';
  if(BUF.st_mode & S_IXGRP)
    drepturiAcces[2] = 'X';
  else
    drepturiAcces[2] = '-';

  sprintf(buf, "drepturi de acces grup: %s\n", drepturiAcces);
  write(f2, buf, strlen(buf));
  strcpy(buf, " ");

  if(BUF.st_mode & S_IROTH)
    drepturiAcces[0] = 'R';
  else
    drepturiAcces[0] = '-';
  if(BUF.st_mode & S_IWOTH)
    drepturiAcces[1] = 'W';
  else
    drepturiAcces[1] = '-';
  if(BUF.st_mode & S_IXOTH)
    drepturiAcces[2] = 'X';
  else
    drepturiAcces[2] = '-';

  sprintf(buf, "drepturi de acces altii: %s\n", drepturiAcces);
  write(f2, buf, strlen(buf));
  strcpy(buf, " ");
  
  close(f1); 
  close(f2);
  return 0;
}
