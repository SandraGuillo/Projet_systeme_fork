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
  unsigned char lettre ;
  int lecture ; 
  int ecriture ;
  int width ;
  int height ;
  int debut ;
  short nb_bit_pixel;
  int fichier_compresse ;
 
  int tube[2];
  int tube_bleu[2];
  int tube_rouge[2];
  int tube_vert[2];
  pipe(tube);
  pipe(tube_bleu);
  pipe(tube_rouge);
  pipe(tube_vert);
  pid_t pid ;
  pid_t pid1;
  char arg[1024];
  char arg1[1024];
  char arg2[1024];
  char arg3[1024];
  //sprintf(arg,"%d",tube[0]);
  sprintf(arg,"%d",tube_bleu[0]);
  //sprintf(arg,"%d",tube_rouge[0]);
  sprintf(arg1,"%d",tube_vert[0]);
  sprintf(arg2,"%d",tube_rouge[0]);
  sprintf(arg3,"%d",tube[0]);
  
  switch(pid = fork()){
  case (pid_t) - 1 ://le cas qui fonctionne pas
    perror("erreur");
    exit(1);
    
  case (pid_t) 0 ://cas où on se situe dans le fils
    close(tube_vert[1]);
    execl("./v","v",arg1,debut,width,ref,NULL);
    //printf("tube\n");
    //close(tube[2]);
    // execl("./b","b",tube[2],debut,width,ref,NULL);
    /*execl("./fils_vert","v",arg,debut,width,ref,NULL);*/
    //execl("./g","g",arg,debut,width,ref,NULL);
  default :// cas où on se situe bien dans le pere
    switch(pid1 = fork()){
    case (pid_t) - 1 ://le cas qui fonctionne pas
      perror("erreur");
      exit(1);
      
    case (pid_t) 0 ://cas où on se situe dans le fils
      
      close(tube_bleu[1]);
      execl("./b","b",arg,debut,width,ref,NULL);
      /*execl("./fils_vert","v",arg,debut,width,ref,NULL);*/
      //execl("./g","g",arg,debut,width,ref,NULL);
    default:
      switch(pid1 = fork()){
      case (pid_t) - 1 ://le cas qui fonctionne pas
	perror("erreur");
	exit(1);
      
      case (pid_t) 0 ://cas où on se situe dans le fils
      
	close(tube_rouge[1]);
	execl("./r","r",arg2,debut,width,ref,NULL);
	/*execl("./fils_vert","v",arg,debut,width,ref,NULL);*/
	//execl("./g","g",arg,debut,width,ref,NULL);
      default:
	switch(pid1 = fork()){
      case (pid_t) - 1 ://le cas qui fonctionne pas
	perror("erreur");
	exit(1);
      
      case (pid_t) 0 ://cas où on se situe dans le fils
      
	close(tube[1]);
	execl("./g","g",arg3,debut,width,ref,NULL);
	/*execl("./fils_vert","v",arg,debut,width,ref,NULL);*/
	//execl("./g","g",arg,debut,width,ref,NULL);
      default:
	break;
	
      }
	
      }
      //break;
    
    }
    close(tube[0]);
    close(tube_rouge[0]);
    close(tube_bleu[0]);
    close(tube_vert[0]);
    if(argc == 3){
      strcpy(ref, argv[1]); //copie dans ref
    }else{
      printf("le nombre d'argument n'est pas correct");
    }
    
    //strcat(nouveau,ref);
    //on verifie si le fichier existe ou non 
    if (stat(ref, &s)== -1){
      perror("Le fichier/répertoire n'existe pas\n");
      exit(1);

      //on s'assure que ce n'est pas un repertoire 
    }else if (S_ISDIR(s.st_mode)){
      strcpy(ref,argv[1]);
      printf("Ce fichier est un répertoire\n");

      
      
      //voici le cas ou c'est bien un fichier ET  qu'il existe
    }
    strcat(nouveau,argv[2]);//copie du fichier
    if (S_ISREG(s.st_mode)){
      //strcpy(ref,argv[1]);
      printf("La taille de celui ci est de : %ld ko\n ",&s.st_size);
     
      lecture = open(ref,O_RDONLY,S_IRWXU); //on ouvre le fichier 

      // on defini le fichier d'ecriture
      ecriture = open(nouveau,O_WRONLY | O_CREAT | O_TRUNC,S_IRWXU);

      // on s'assure que le fichier a été crée
      if (ecriture == -1){
	perror("Le fichier n'a pas été créé");
	exit(0);
      }
      int i = 0 ;
      //on verifier si c'est bien un fichier bmp
      while(read(lecture, &lettre, sizeof(char))!=0){
	if((i == 0 && lettre!='B') || (i == 1 && lettre!='M')){
	  perror("Le fichier n'est pas un bmp");
	  exit(0);
	}
	i++;
       
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

      /******************************************/
      i = 0 ;
      //on verifie que le fichier bmp fait bien 24bit
      if(nb_bit_pixel != 24){
	printf("le nombre de bit n'est pas egale a 24");
	exit(0);
      }
      //si toutes les conditions sont reunis
      lseek(lecture,0,SEEK_SET);
      
      // ecriture de l'entete jusqu'au debut de l'image
      while(read(lecture,&lettre,sizeof(char))!=0){
	write(ecriture, &lettre,sizeof(char));//envoi dans le tube
	  
      }
      
      lseek(lecture,0,SEEK_SET);
      while(read(lecture,&lettre,sizeof(char))!=0){
	write(tube[1], &lettre,sizeof(char));//envoi dans le tube
	/*	write(tube_rouge[1], &lettre,sizeof(char));//envoi dans le tube
	write(tube_bleu[1], &lettre,sizeof(char));//envoi dans le tube
	write(tube_vert[1], &lettre,sizeof(char));//envoi dans le tube*/
      }
      lseek(lecture,0,SEEK_SET);
      while(read(lecture,&lettre,sizeof(char))!=0){
	//	write(tube[1], &lettre,sizeof(char));//envoi dans le tube
	write(tube_rouge[1], &lettre,sizeof(char));//envoi dans le tube
	/*write(tube_bleu[1], &lettre,sizeof(char));//envoi dans le tube
	  write(tube_vert[1], &lettre,sizeof(char));//envoi dans le tube*/
      }
            lseek(lecture,0,SEEK_SET);
      while(read(lecture,&lettre,sizeof(char))!=0){
	/*	write(tube[1], &lettre,sizeof(char));//envoi dans le tube
		write(tube_rouge[1], &lettre,sizeof(char));//envoi dans le tube*/
	write(tube_bleu[1], &lettre,sizeof(char));//envoi dans le tube
	//write(tube_vert[1], &lettre,sizeof(char));//envoi dans le tube
      }
            lseek(lecture,0,SEEK_SET);
      while(read(lecture,&lettre,sizeof(char))!=0){
	/*	write(tube[1], &lettre,sizeof(char));//envoi dans le tube
	write(tube_rouge[1], &lettre,sizeof(char));//envoi dans le tube
	write(tube_bleu[1], &lettre,sizeof(char));//envoi dans le tube*/
	write(tube_vert[1], &lettre,sizeof(char));//envoi dans le tube
      }
      
	
      printf("fin du pere\n");
      //on ferme tout 
      close(lecture);
      close(ecriture);	
      
    
    }
    break; 
    
  }
  
  //break;
  close(tube[1]);
  close(tube_rouge[1]);
  close(tube_vert[1]);
  close(tube_bleu[1]);
  exit(0);
      
}
