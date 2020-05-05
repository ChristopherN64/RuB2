/* Das Beispielprogramm dateiinfo.c ermittelt Informationen ueber die 
   als Argument angegebenen Dateinamen */ 

#include <stdio.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

/* Die Elemente in der Struktur stat haben nachstehende Bedeutung:

Datentyp:     Element:      Bedeutung:

dev_t         st_dev        device 
ino_t         st_ino        inode 
mode_t        st_mode       protection 
nlink_t       st_nlink      number of hard links 
uid_t         st_uid        user ID of owner 
gid_t         st_gid        group ID of owner 
dev_t         st_rdev       device type (if inode device) 
off_t         st_size       total size, in bytes 
unsigned long st_blksize    blocksize for filesystem I/O 
unsigned long st_blocks     number of blocks allocated 
time_t        st_atime      time of last access 
time_t        st_mtime      time of last modification 
time_t        st_ctime      time of last change 

*/

int main(int argc, char** argv) 
{ 
  int i, err; 
  mode_t typ, perm;
  struct stat buf; 
  char* ptr; 
  
  for (i = 1; i < argc; i++) {   /* Schleife ueber alle Argumente */
    printf("%s: ", argv[i]);     /* Ausgabe des Dateinamens       */

    err = lstat(argv[i], &buf);  /* Ermittlung der Informationen ueber die
                                    Datei argv[i], der Rueckgabewert ist 0 
                                    bei Erfolg, sonst < 0, 
                                    in buf stehen die Informationen */

 
    if (err < 0) {                           /* Abfrage auf Fehler */
      fprintf(stderr, "Fehler in lstat\n");   /* Fehlermeldung ausgeben */
      continue;                         /* weiter mit dem naechsten Argument */
    } 

    /* Ermittlung des Dateityps */
    
    typ = buf.st_mode >> 12;             /* die unteren Bits rausschieben, nur 
                                          die oberen 4 Bits werden benoetigt  */
    switch (typ) { 
      case 010: printf("Regulaere Datei,"); break;
      case 004: printf("Verzeichnis, "); break;
      case 002: printf("Zeichen-Geraetedatei, "); break; 
      case 006: printf("Block-Geraetedatei, "); break; 
      case 001: printf("FIFO, "); break; 
      case 012: printf("Symbolischer Link, "); break; 
      case 014: printf("Socket, "); break;
      default:  printf("unbekannter Typ,");
    }

    int uid = buf.st_uid;
    int gid = buf.st_gid;
    unsigned long size = buf.st_size;
    time_t time = buf.st_mtime;
    nlink_t nD = buf.st_nlink;
    char* buff;    //system("cat /etc/group  | grep %d | cut -d: -f1");

    char rechte[10];
    rechte[0] = '-';
    if(buf.st_mode & S_IRUSR) rechte[1]='r'; else rechte[1]='-' ;
    if(buf.st_mode & S_IWUSR) rechte[2]='w'; else rechte[2]='-' ;
    if(buf.st_mode & S_IXUSR) rechte[3]='x'; else rechte[3]='-' ;
    if(buf.st_mode & S_IRGRP) rechte[4]='r'; else rechte[4]='-' ;
    if(buf.st_mode & S_IWGRP) rechte[5]='w'; else rechte[5]='-' ;
    if(buf.st_mode & S_IXGRP) rechte[6]='x'; else rechte[6]='-' ;
    if(buf.st_mode & S_IROTH) rechte[7]='r'; else rechte[7]='-' ;
    if(buf.st_mode & S_IWOTH) rechte[8]='w'; else rechte[8]='-' ;
    if(buf.st_mode & S_IXOTH) rechte[9]='x'; else rechte[9]='-' ;

    printf("\n\n%c%c%c%c%c%c%c%c%c%c  ",rechte[0],rechte[1],rechte[2],rechte[3],rechte[4],rechte[5],rechte[6],rechte[7],rechte[8],rechte[9]);
    printf("%d %d %d %lu %s %s",nD,uid,gid,size,ctime(&time),argv[1]);

    /*
printf("Zugriffsrechte: 0%o\n", perm); // Rechte als Oktalzahl ausgeben
    printf("I-Node: %lu, ", buf.st_ino); // I-Node als Dezimalzahl ausgeben
    perm = buf.st_mode & 0777;   // Nur die unteren 12 Bits ausgeben
    printf("UID %d\n",buf.st_uid);
    printf("GID %d\n",buf.st_gid);
    printf("Dateigröße: %lu Byte\n",buf.st_size);
     */
  } 
  return 0;
}
