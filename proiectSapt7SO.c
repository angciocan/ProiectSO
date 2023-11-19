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

struct stat buffer;
struct stat fisierBmp;

int main(int argc, char *argv[])
{
  int f1 = 0;

  DIR *dir;
  struct dirent *dp;
  if(stat(argv[1], &buffer) != 0)
  {
    perror("Eroare!\n");
    exit(0);
  }
  
  if((f1 = open("statistica.txt", O_WRONLY)) < 0)
  {
     perror("Eroare deschidere fisier!\n");
     exit(2);
  } 

  if(S_ISDIR(buffer.st_mode))
  {
    if((dir = opendir(argv[1])) == NULL)
    {
      perror("Eroare deschidere director!\n");
      exit(1);
    }

    while((dp = readdir(dir)) != NULL)
    {      
      if(dp -> d_type == DT_REG)
      {
	if(strstr(dp -> d_name, ".bmp") != NULL)//
	{
            char buf[100];
	    char numefisier[10];
	    strcpy(numefisier, dp -> d_name);
            sprintf(buf, "nume fisier: %s\n", numefisier);
            write(f1, buf, strlen(buf));
            strcpy(buf, " ");
  
            if(stat(dp -> d_name, &fisierBmp) < 0)
            {
               perror("Eroare!\n");
               exit(3);
            }

            sprintf(buf, "inaltime: %ld\n", fisierBmp.st_size);
            write(f1, buf, strlen(buf));
            strcpy(buf, " ");

            sprintf(buf, "lungime: %ld\n", fisierBmp.st_blksize);
            write(f1, buf, strlen(buf));
            strcpy(buf, " ");
  
	    /*sprintf(buf, "dimensiune: %d\n", header.fileSize);

             write(f1, buf, strlen(buf));
             strcpy(buf, " ");*/

             sprintf(buf, "identificatorul utilizatorului: %d\n", fisierBmp.st_uid);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");
             time_t time = fisierBmp.st_mtime;
             struct tm *data = localtime(&time);

             sprintf(buf, "timpul ultimei modificari: %d.%d.%d\n",
	     data -> tm_mday, data -> tm_mon + 1, data -> tm_year + 1900);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");

             sprintf(buf, "contorul de legaturi: %ld\n", fisierBmp.st_nlink);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");
             char drepturiAcces[3];

             //setareDrepturiDeAcces(fisierBmp.st_mode);  
  
             if(fisierBmp.st_mode & S_IRUSR)
                drepturiAcces[0] = 'R';
             else
                drepturiAcces[0] = '-';
             if(fisierBmp.st_mode & S_IWUSR)
                drepturiAcces[1] = 'W';
             else
                drepturiAcces[1] = '-';
             if(fisierBmp.st_mode & S_IXUSR)
                drepturiAcces[2] = 'X';
             else
                drepturiAcces[2] = '-';
             drepturiAcces[3] = '\0';
  
             sprintf(buf, "drepturi de acces user: %s\n", drepturiAcces);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");

             if(fisierBmp.st_mode & S_IRGRP)
                 drepturiAcces[0] = 'R';
             else
                 drepturiAcces[0] = '-';
             if(fisierBmp.st_mode & S_IWGRP)
                 drepturiAcces[1] = 'W';
             else
                 drepturiAcces[1] = '-';
             if(fisierBmp.st_mode & S_IXGRP)
                 drepturiAcces[2] = 'X';
             else
                 drepturiAcces[2] = '-';

             sprintf(buf, "drepturi de acces grup: %s\n", drepturiAcces);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");

             if(fisierBmp.st_mode & S_IROTH)
                drepturiAcces[0] = 'R';
             else
                drepturiAcces[0] = '-';
             if(fisierBmp.st_mode & S_IWOTH)
                drepturiAcces[1] = 'W';
             else
                drepturiAcces[1] = '-';
             if(fisierBmp.st_mode & S_IXOTH)
                drepturiAcces[2] = 'X';
             else
                drepturiAcces[2] = '-';

             sprintf(buf, "drepturi de acces altii: %s\n", drepturiAcces);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");

	     //close(f1);
	}
        //
	else if(strstr(dp -> d_name, ".bmp") == NULL)
	{
            char buf[100];
	    char numefisier[10];
	    strcpy(numefisier, dp -> d_name);
            sprintf(buf, "nume fisier: %s\n", numefisier);
            write(f1, buf, strlen(buf));
            strcpy(buf, " ");
  
            if(stat(dp -> d_name, &fisierBmp) < 0)
            {
               perror("Eroare!\n");
               exit(4);
            }
	    
	    /*sprintf(buf, "dimensiune: %d\n", header.fileSize);

             write(f1, buf, strlen(buf));
             strcpy(buf, " ");*/

             sprintf(buf, "identificatorul utilizatorului: %d\n", fisierBmp.st_uid);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");
             time_t time = fisierBmp.st_mtime;
             struct tm *data = localtime(&time);

             sprintf(buf, "timpul ultimei modificari: %d.%d.%d\n",
	     data -> tm_mday, data -> tm_mon + 1, data -> tm_year + 1900);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");

             sprintf(buf, "contorul de legaturi: %ld\n", fisierBmp.st_nlink);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");
             char drepturiAcces[3];

             //setareDrepturiDeAcces(fisierBmp.st_mode);  
  
             if(fisierBmp.st_mode & S_IRUSR)
                drepturiAcces[0] = 'R';
             else
                drepturiAcces[0] = '-';
             if(fisierBmp.st_mode & S_IWUSR)
                drepturiAcces[1] = 'W';
             else
                drepturiAcces[1] = '-';
             if(fisierBmp.st_mode & S_IXUSR)
                drepturiAcces[2] = 'X';
             else
                drepturiAcces[2] = '-';
             drepturiAcces[3] = '\0';
  
             sprintf(buf, "drepturi de acces user: %s\n", drepturiAcces);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");

             if(fisierBmp.st_mode & S_IRGRP)
                 drepturiAcces[0] = 'R';
             else
                 drepturiAcces[0] = '-';
             if(fisierBmp.st_mode & S_IWGRP)
                 drepturiAcces[1] = 'W';
             else
                 drepturiAcces[1] = '-';
             if(fisierBmp.st_mode & S_IXGRP)
                 drepturiAcces[2] = 'X';
             else
                 drepturiAcces[2] = '-';

             sprintf(buf, "drepturi de acces grup: %s\n", drepturiAcces);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");

             if(fisierBmp.st_mode & S_IROTH)
                drepturiAcces[0] = 'R';
             else
                drepturiAcces[0] = '-';
             if(fisierBmp.st_mode & S_IWOTH)
                drepturiAcces[1] = 'W';
             else
                drepturiAcces[1] = '-';
             if(fisierBmp.st_mode & S_IXOTH)
                drepturiAcces[2] = 'X';
             else
                drepturiAcces[2] = '-';

             sprintf(buf, "drepturi de acces altii: %s\n", drepturiAcces);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");

	     //close(f1);
	}
      }
      	else
	{
	  struct stat director;
	  stat(dp -> d_name, &director);
	  
	  if(S_ISDIR(director.st_mode))
	  {
	    char buf[100];
	    char numefisier[10];
	    strcpy(numefisier, dp -> d_name);
	    
            sprintf(buf, "nume director: %s\n", numefisier);
            write(f1, buf, strlen(buf));
            strcpy(buf, " ");
  
	    
	    /*sprintf(buf, "dimensiune: %d\n", header.fileSize);

             write(f1, buf, strlen(buf));
             strcpy(buf, " ");*/

             sprintf(buf, "identificatorul utilizatorului: %d\n", director.st_uid);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");
	     char drepturiAcces[3];
  
             if(director.st_mode & S_IRUSR)
                drepturiAcces[0] = 'R';
             else
                drepturiAcces[0] = '-';
             if(director.st_mode & S_IWUSR)
                drepturiAcces[1] = 'W';
             else
                drepturiAcces[1] = '-';
             if(director.st_mode & S_IXUSR)
                drepturiAcces[2] = 'X';
             else
                drepturiAcces[2] = '-';
             drepturiAcces[3] = '\0';
  
             sprintf(buf, "drepturi de acces user: %s\n", drepturiAcces);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");

             if(director.st_mode & S_IRGRP)
                 drepturiAcces[0] = 'R';
             else
                 drepturiAcces[0] = '-';
             if(director.st_mode & S_IWGRP)
                 drepturiAcces[1] = 'W';
             else
                 drepturiAcces[1] = '-';
             if(director.st_mode & S_IXGRP)
                 drepturiAcces[2] = 'X';
             else
                 drepturiAcces[2] = '-';

             sprintf(buf, "drepturi de acces grup: %s\n", drepturiAcces);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");

             if(director.st_mode & S_IROTH)
                drepturiAcces[0] = 'R';
             else
                drepturiAcces[0] = '-';
             if(director.st_mode & S_IWOTH)
                drepturiAcces[1] = 'W';
             else
                drepturiAcces[1] = '-';
             if(director.st_mode & S_IXOTH)
                drepturiAcces[2] = 'X';
             else
                drepturiAcces[2] = '-';

             sprintf(buf, "drepturi de acces altii: %s\n", drepturiAcces);
             write(f1, buf, strlen(buf));
             strcpy(buf, " ");

	     //close(f1);
	     printf("%s\n", dp -> d_name);
	  }
	  
	}
    }
  }
    
  else
  {
    printf("Argumentul nu este un director!\n");
  }

    close(f1);
  return 0;
}
