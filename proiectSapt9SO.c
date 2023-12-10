#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h>

struct stat fisier;

struct bmpHeader{
  char signature[2];
  int fileSize;
  int reserved;
  int dataOffset;
}bmpHeader;

struct bmpHeaderInfo{
  int size;
  long long int width;
  long long int height;
  int planes;
  int BitCount;
  int Compresion;
  int imageSize;
}bmpHeaderInfo;

struct stat fisier;

struct bmpHeader header;
struct bmpHeaderInfo headerInfo;

int main(int argc, char *argv[])
{
  if(argc != 4)
  {
    perror("Numar insuficient de argumente!\n");
    exit(0);
  }
  
  int f1;
  int status = 0;
  int p1[2];
  int numarDePropozitii = 0;
  
  if(pipe(p1) < 0)
  {
    perror("Eroare pipe!\n");
    exit(0);
  }
  
  pid_t pid;
  DIR *directorIntrare, *directorIesire = NULL;
  struct dirent *dpInp, *dpOut;
  char fisierStatistici[1000];
  char buffer[1000];

  if((pid = fork()) < 0)
  {
    perror("Eroare creare proces!\n");
    exit(3);
  }

   if((directorIntrare = opendir(argv[1])) == NULL)
   {
       perror("Eroare deschidere director intare!\n");
       exit(0);
   }

   if((directorIesire = opendir(argv[2])) == NULL)
   {
       perror("Eroare deschidere director iesire!\n");
       exit(0);
   }

  while((dpOut = readdir(directorIesire)) != NULL)
  {
    if(strcmp(dpOut -> d_name, "statistica.txt") == 0)
    {
      if((f1 = open(dpOut -> d_name, O_WRONLY)) < 0)
      {
        perror("Eroare deschidere fisier statistica!\n");
	exit(2);
      }
      
      strcpy(fisierStatistici, dpOut -> d_name);
    }
  }
  
  while((dpInp = readdir(directorIntrare)) != NULL)
  {
    char numeFisier[100];
    char numeDirector[100];
    strcpy(numeFisier, dpInp -> d_name);
    strcpy(numeDirector, argv[1]);

    snprintf(buffer, sizeof(buffer), "%s/%s", numeDirector, numeFisier); 

    if(lstat(buffer, &fisier) < 0)
    {
      perror("Eroare!\n");
      exit(2);
    }

    /*if(read(p1[0], &fisierStatistici, sizeof(fisierStatistici)) < 0)
     {
       printf("Eroare!\n");
       }*/
 
    if(pid == 0)
    {
      close(p1[0]);

      if(write(p1[1], &fisierStatistici, sizeof(fisierStatistici)) < 0)
      {
        printf("Eroare!\n");
      }
      
      if(strstr(numeFisier,".bmp") != NULL)
      {
        continue;
      }
     
      if((strcmp(numeFisier, ".") == 0) || (strcmp(numeFisier, "..") == 0))
        continue;
	 
      char buf[1010];
      snprintf(fisierStatistici, sizeof(fisierStatistici), "%s_statistica.txt", numeFisier);

      sprintf(buf, "%s\n", fisierStatistici);
      write(f1, buf, strlen(buf));
      strcpy(buf, " ");
      
      sprintf(buf, "Nume fisier: %s\n", numeFisier);
      write(f1, buf, strlen(buf));
      strcpy(buf, " ");
      
	sprintf(buf, "dimensiune: %ld\n", fisier.st_size);
	write(f1, buf, strlen(buf));
	strcpy(buf, " ");
	
        sprintf(buf, "identificatorul utilizatorului: %d\n", fisier.st_uid);
        write(f1, buf, strlen(buf));
        strcpy(buf, " ");

        time_t time = fisier.st_mtime;
        struct tm *data = localtime(&time);

        sprintf(buf, "timpul ultimei modificari: %d.%d.%d\n",
	data -> tm_mday, data -> tm_mon + 1, data -> tm_year + 1900);
        write(f1, buf, strlen(buf));
        strcpy(buf, " ");
	
        sprintf(buf, "contorul de legaturi: %ld\n", fisier.st_nlink);
        write(f1, buf, strlen(buf));
        strcpy(buf, " ");
	
        char drepturiAcces[3];
  
        if(fisier.st_mode & S_IRUSR)
           drepturiAcces[0] = 'R';
        else
           drepturiAcces[0] = '-';
        if(fisier.st_mode & S_IWUSR)
           drepturiAcces[1] = 'W';
        else
           drepturiAcces[1] = '-';
        if(fisier.st_mode & S_IXUSR)
           drepturiAcces[2] = 'X';
        else
           drepturiAcces[2] = '-';
        drepturiAcces[3] = '\0';
  
             sprintf(buf, "drepturi de acces user: %s\n", drepturiAcces);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");
	     
             if(fisier.st_mode & S_IRGRP)
                 drepturiAcces[0] = 'R';
             else
                 drepturiAcces[0] = '-';
             if(fisier.st_mode & S_IWGRP)
                 drepturiAcces[1] = 'W';
             else
                 drepturiAcces[1] = '-';
             if(fisier.st_mode & S_IXGRP)
                 drepturiAcces[2] = 'X';
             else
                 drepturiAcces[2] = '-';

             sprintf(buf, "drepturi de acces grup: %s\n", drepturiAcces);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");
	     
             if(fisier.st_mode & S_IROTH)
                drepturiAcces[0] = 'R';
             else
                drepturiAcces[0] = '-';
             if(fisier.st_mode & S_IWOTH)
                drepturiAcces[1] = 'W';
             else
                drepturiAcces[1] = '-';
             if(fisier.st_mode & S_IXOTH)
                drepturiAcces[2] = 'X';
             else
                drepturiAcces[2] = '-';

             sprintf(buf, "drepturi de acces altii: %s\n\n", drepturiAcces);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");
             p1[1] = system("./scriptSapt9SO.sh");
             close(p1[1]);
    }

    if(pid != 0)
    {         
      wait(NULL);
       
      if(WIFEXITED(status))
      {
	printf("Procesul fiu s-a terminat cu pid-ul %d si codul %d!\n", getpid(), WEXITSTATUS(status)); 
        printf("Au fost identificate in total %d propozitii corecte care contin caracterul %c!\n", numarDePropozitii, argv[3][0]);
      }
    }
  }
  
  closedir(directorIntrare);
  closedir(directorIesire);
  
  return 0;
}
