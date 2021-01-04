#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>

int main(int argc,char**argv){

  //initialisation des variables dont on a besoin 
  struct stat s ;
  char ref[1024];
  sprintf(ref,"%s",argv[1]);
  char nouveau[1024] = "copie" ;
  unsigned char buffer[3] ;
  unsigned char lettre ;
  int lecture ; 
  int ecriture ;
  int r = 0;
  int i = 0;
  int j = 0;
  int width ;
  int height ;
  int debut ;
  short nb_bit_pixel;
  int fichier_compresse ;
  unsigned char pixel_bleu ;
  unsigned char pixel_rouge;
  unsigned char pixel_vert;
  unsigned char pixel_gris;

  strcat(nouveau,ref);
  //on verifie si le fichier existe ou non 
  if (stat(argv[1], &s)== -1){
    perror("Le fichier/répertoire n'existe pas\n");
    exit(1);

    //on s'assure que ce n'est pas un repertoire 
  }else if (S_ISDIR(s.st_mode)){
      strcpy(ref,argv[1]);
      printf("Ce fichier est un répertoire\n");


      //voici le cas ou c'est bien un fichier ET  qu'il existe
  }else if (S_ISREG(s.st_mode)){
      strcpy(ref,argv[1]);
      printf("La taille de celui ci est de : %ld ko\n ",&s.st_size);
     
      lecture = open(ref,O_RDONLY,S_IRWXU); //on ouvre le fichier 

      // on defini le fichier d'ecriture
      ecriture = open(nouveau,O_WRONLY | O_CREAT | O_TRUNC,S_IRWXU);

      // on s'assure que le fichier a été crée
      if (ecriture == -1){
	perror("Le fichier n'a pas été créé");
	exit(0);
      }
      
      //on verifier si c'est bien un fichier bmp
      while(read(lecture, &lettre, sizeof(char))!=0 && i <2){
      if((i == 0 && lettre!='B') || (i == 1 && lettre!='M')){
	perror("Le fichier n'est pas un bmp");
	exit(0);
      }
      else{
	//write(ecriture, &lettre,sizeof(char));
	i++;
	}
      }

      /***************************************/
      /*     Information sur l'image         */
      /***************************************/

      //le debut de l'image
      lseek(lecture,10,SEEK_SET);
      read(lecture,&debut,sizeof(int));

      
      // information sur la résolution de l'image
      //la largeur de l'image : 
      lseek(lecture,18,SEEK_SET);
      read(lecture,&width,sizeof(int));
      printf("largeur de l'image = %d \n",width);

      //la hauteur de l'image :
      lseek(lecture,22,SEEK_SET);
      read(lecture,&height,sizeof(int));
      printf("largeur de l'image = %d \n",height);

      //le nombre de bit par pixel
      lseek(lecture,28,SEEK_SET);
      read(lecture,&nb_bit_pixel,sizeof(short));
      printf("il y a %d bits par pixel\n",nb_bit_pixel);

      
      //est - ce que le fichier est compresse
      lseek(lecture,30,SEEK_SET);
      read(lecture,&fichier_compresse,sizeof(int));
      printf("compression = %d\n",fichier_compresse);

      i = 0 ;
      //on verifie que le fichier bmp fait bien 24bit
      if(nb_bit_pixel != 24){
	printf("le nombre de bit n'est pas egale a 24");
	exit(0);
      }else{//si toutes les conditions sont reunis
	lseek(lecture,0,SEEK_SET);
	// ecriture de l'entete jusqu'au debut de l'image
	while(read(lecture,&lettre,sizeof(char))!=0 && i<=debut){
	  write(ecriture, &lettre,sizeof(char));
	  i++;
	}
	i = 0;
	lseek(lecture,debut,SEEK_SET);
	//on ecrit le reste de l'image après l'entete 
	while(read(lecture,&lettre,sizeof(char)) != 0){
	  buffer[i] = lettre;
	  i++;
	  if(i==3){
	    //on regarde les pixels bleu
	    pixel_bleu = buffer[0];
	    //on regarde les pixels vert
	    pixel_vert = buffer[1];
	    //on regarde les pixels rouges
	    pixel_rouge = buffer[2];
	    
	    pixel_gris = (unsigned char)(pixel_rouge*0.299 + pixel_vert*0.587 + pixel_bleu*0.114);
	    
	    lettre = pixel_gris;
	   
	    
	    for(j = 0; j<3; j++){
	      write(ecriture, &lettre,sizeof(char));
	     
	    }
	    i = 0;
	  }
	  
	}	
      }
  }
  
  for(i=0; i<4-((width*3)%4);i++){
    pixel_gris = (char)0;
    write(ecriture,&pixel_gris,sizeof(char));
  }

      
      //on ferme tout 
  close(lecture);
  close(ecriture);
      
      
}

