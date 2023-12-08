#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
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
  int width;
  int height;
}bmpHeaderInfo;

struct bmpHeader header;
struct bmpHeaderInfo headerInfo;

int main(int argc, char *argv[])
{
  int f1 = 0;
  int nrDeFisiere = 0;
  DIR *director;
  struct dirent *dp;
  char buffer[1000];
  if((director = opendir(argv[1])) == NULL)
  {
    perror("Eroare deschidere director!\n");
    exit(0);
  }
  
  if((f1 = open("statistica.txt", O_WRONLY)) < 0)
  {
     perror("Eroare deschidere fisier!\n");
     exit(1);
  } 

  while((dp = readdir(director)) != NULL)
  {
    char numeFisier[100];
    char numeDirector[100];
    strcpy(numeFisier, dp -> d_name);
    strcpy(numeDirector, argv[1]);
    snprintf(buffer, sizeof(buffer), "%s/%s", numeDirector, numeFisier);

    if(lstat(buffer, &fisier) < 0)
    {
      perror("Eroare!\n");
      exit(1);
    }

    if(S_ISREG(fisier.st_mode))
    {
      if(strstr(numeFisier, ".bmp") != NULL)
      {
	int f2 = 0;
        nrDeFisiere++;
        char buf[1000];
        sprintf(buf, "\nNumarul de fisiere: %d\n", nrDeFisiere);
        write(f1, buf, strlen(buf));
        strcpy(buf, " ");

        sprintf(buf, "Nume fisier: %s\n", numeFisier);
        write(f1, buf, strlen(buf));
        strcpy(buf, " ");

	if((f2 = open(numeFisier, O_RDONLY)) < 0)
	{
          perror("Eroare deschidere fisier!\n");
	  exit(2);
	}

        
	if(read(f2, &header, sizeof(header)) < 0)
	{
	  perror("Eroare citire header!\n");
	  exit(3);
	}
	
	if(read(f2, &headerInfo, sizeof(headerInfo)) < 0)
	{
	  perror("Eroare citire informatii header!\n");
	  exit(3);
	}

	sprintf(buf, "inaltime: %d\n", headerInfo.height);
        write(f1, buf, strlen(buf));
        strcpy(buf, " ");

        sprintf(buf, "lungime: %ld\n", fisier.st_blksize);
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

             sprintf(buf, "drepturi de acces altii: %s\n", drepturiAcces);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");

	     close(f2);
      }

      if(strstr(numeFisier, ".bmp") == NULL)
      {
             nrDeFisiere++;
        char buf[1000];
        sprintf(buf, "\nNumarul de fisiere: %d\n", nrDeFisiere);
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

             sprintf(buf, "drepturi de acces altii: %s\n", drepturiAcces);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");
      }
    }

    if(S_ISDIR(fisier.st_mode) && ((strcmp(numeFisier, ".") != 0) && (strcmp(numeFisier, "..") != 0)))
    {
      char buf[1000];
      nrDeFisiere++;
      sprintf(buf, "\n\nFisierul numarul %d\n\n", nrDeFisiere);
      write(f1, buf, strlen(buf));
      strcpy(buf, " ");
	    
      sprintf(buf, "nume director: %s\n", numeFisier);
      write(f1, buf, strlen(buf));
      strcpy(buf, " ");
	      
      sprintf(buf, "identificatorul utilizatorului: %d\n", fisier.st_uid);
      write(f1, buf, strlen(buf));
      strcpy(buf, " ");
      
      char drepturiAcces[3];
      strcpy(drepturiAcces, " ");
	       
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

      sprintf(buf, "drepturi de acces altii: %s\n", drepturiAcces);
      write(f1, buf, strlen(buf));
      strcpy(buf, " ");
    }

    if(S_ISLNK(fisier.st_mode))
    {
      char buf[1000];
      char target[1024];
      char numeFisierTarget[100];
      struct stat fisierTarget;
      ssize_t n = readlink(buffer, target, sizeof(target));
      
      
      if(n != -1)
      {
        target[n] = '\0';
	strcpy(numeFisierTarget, target);
	stat(target, &fisierTarget);
	
      }
      
      strcpy(numeFisierTarget, target);
      
      nrDeFisiere++;
      sprintf(buf, "\n\nFisierul numarul %d\n\n", nrDeFisiere);
      write(f1, buf, strlen(buf));
      strcpy(buf, " ");

      sprintf(buf, "nume legatura: %s\n", numeFisier);
      write(f1, buf, strlen(buf));
      strcpy(buf, " ");

      sprintf(buf, "dimensiune legatura: %ld\n", fisier.st_size);
      write(f1, buf, strlen(buf));
      strcpy(buf, " ");
      
      sprintf(buf, "dimensiune fisier target: %ld\n", fisierTarget.st_size);
      write(f1, buf, strlen(buf));
      strcpy(buf, " ");
 
      char drepturiAcces[3];
      strcpy(drepturiAcces, " ");
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
      strcpy(drepturiAcces, " ");
	     
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
	     drepturiAcces[3] = '\0'; 

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
             drepturiAcces[3] = '\0';
	     
	     sprintf(buf, "drepturi de acces altii: %s\n", drepturiAcces);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");
    }
  }
  
  close(f1);
  closedir(director);
  return 0;
}




