#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>

int main(int argc,char**argv){

  char buffer;
  char buf[3];
  unsigned char pixel_bleu ;
  unsigned char pixel_rouge;
  unsigned char pixel_vert;
  unsigned char pixel_gris;
  char ref[1024];
  char nouveau[1024] = "copie_rouge";
  strcpy(ref,argv[3]);
  int i = 0 ;
  int ecriture ;
  int truc = atoi(argv[1]);


  ecriture = open(nouveau,O_WRONLY | O_CREAT | O_TRUNC,S_IRWXU);

  printf("fils rouge\n");
  if (ecriture == -1){
    perror("erreur pour le fichier");
    exit(0);
  }
  while(read(truc,&buffer,sizeof(char))!=0 && i<=40) {
    write(ecriture, &buffer,sizeof(char));
    i++;
  }
  
  i = 0;

  
  printf("debut du fils rouge\n");
  
  while(read(truc,&buffer,sizeof(char)) != 0 ){

    buf[i] = buffer;
    i++;
      if(i==3){
	//on regarde les pixels bleu
	pixel_bleu = 0;
	//on regarde les pixels vert
	pixel_vert = 0;
	//on regarde les pixels rouges
	pixel_rouge = buf[2] & 255;
	buf[0] = pixel_bleu;
	buf[1] = pixel_vert;
	buf[2]= pixel_rouge;
	    
	//pixel_gris = (unsigned char)(pixel_rouge*0.299 + pixel_vert*0.587 + pixel_bleu*0.114);
	    
	buffer = buf;

	
	    

	write(ecriture, &pixel_rouge,sizeof(unsigned char));
	write(ecriture, &pixel_bleu,sizeof(unsigned char));
	write(ecriture, &pixel_vert,sizeof(unsigned char));

	i=0;
      }
	  
  }
  for(i=0 ; i<4-((atoi(argv[3])*3)%4) ; i++){
    pixel_rouge = (char)0;
    write(ecriture,&pixel_rouge,sizeof(char));
  }
  printf("fin  du fils rouge\n");
  close(ecriture);
  close(truc);
  exit(0);
}


