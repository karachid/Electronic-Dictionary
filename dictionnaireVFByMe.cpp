/*
Projet réalisé par : Rachid KABBAB Ecole Nationale Supérieure des Mines de Rabat (Ex ENIM 2017)
*/
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<windows.h>
#include<stddef.h>
#include<ctype.h>

// Définition de la structure d'un noeud -ça marche-
struct lettre 
{
       char car;
       struct lettre *fils;
       struct lettre *pere;
       char signification[50];
       struct lettre *frere;
};
typedef struct lettre *l;

// Liste d'aide -ça marche-
struct dictionnaire
{
	char mot[20],sign[200];
	struct dictionnaire *suiv;
};
typedef struct dictionnaire dico;

// Création du dictionnaire -ça marche-
l creerDictionnaire()
{
                      l d = (l)malloc(sizeof(l));
                      d->car = '*';
                      d->fils=NULL;
                      d->pere=NULL;
                      strcpy(d->signification,"RACINE");
                      d->frere=NULL;
                      return d;
}

// Chercher un mot dans le dictionnaire -ça marche-
int chercher(lettre *R,char* x)
{
	printf("Search function is gonna be executed ... \n");
    lettre *p,*q;
    printf("ICI 1 \n");
    if(R->fils==NULL)
    {
    	printf("ICI 2 \n");
    	return 0;
    }
    q=R->fils;
    while(x[0]!='\0')
    {
        p=q;
        while (p!=NULL && p->car<x[0]) p=p->frere;
	if(p==NULL || p->car>x[0])
        {
	   return 0;	
	}
	q=p->fils;
	x++;
    }
    printf("Search function is done ... \n");
    return 1;
}

// - ça marche -
void detruireDictionnaire(l racine)
{
     //printf("\ndebut detruire\n");
     if(racine!=NULL)
     {
                      if(racine->fils != NULL)
                      {
                                      detruireDictionnaire(racine->fils);                
                      }
     		      if(racine->frere != NULL)
		      {
                                      detruireDictionnaire(racine->frere);                
          	      }
          	      free(racine);
     }
     //printf("\nfin detruire\n");
}

//Fonction d'ajout -ça marche-
void ajouterMot(l racine, char *word, char *s)
{
               l tmp = NULL;
               l f = NULL;
               l c = NULL;
               l courant = racine;
               //printf("\n le mot est %s \n", word);
               if(word[0] != '\0')
	       {
                       	  //printf("\n au debut de la fonction %c", word[0]);
                          if(courant->fils==NULL)
			  {
                          	//("\nici\n");
                          	//printf("\nif---debut");
                          	//printf("\ntest\n");
                          	f = (lettre*)malloc(sizeof(struct lettre)); // ATTENTION
                          	/*if(f==NULL)
				{
                                	//printf("\nallcation impossible\n");
                                        //exit;
                                }
                                printf("\nhere0\n");*/
                                f->car=word[0];
                                //printf("\nhere00\n");
                                f->frere=NULL;
                                f->fils=NULL;
                                f->pere=courant;
                                //printf("\nhere1\n");
                                courant->fils=f;
                                //printf("\nhere\n");
                                //courant->frere=NULL; 
				courant=f;
                                word++;  
                                ajouterMot(courant,word,s);
                                // printf("\nif---fin\n");    
                                //printf("ici2");  
                          }
                          else
			  {
                               c = courant;
                               courant = courant->fils;
                               while(courant!=NULL && courant->car < word[0])
			       {
                               		tmp=courant;
                                        courant=courant->frere;
                               }
                               if(courant!=NULL)
			       {
					if(courant->car == word[0])
					{
						word++;
                                                ajouterMot(courant,word,s);      
                                        }
                                        else if(courant->car > word[0])
					{
                                        	if(tmp==NULL)
						{
                                                	f = (lettre*)malloc(sizeof(lettre));
							f->car=word[0];
                                                        f->fils=NULL;
                                                        f->pere=c;
							f->frere=courant;
							c->fils=f;
							courant=f;
							word++;
							ajouterMot(courant,word,s);
						}
                                                if(tmp!=NULL)
						{
							f = (lettre*)malloc(sizeof(lettre));
							f->car=word[0];
                                                        f->fils=NULL;
							f->pere=c;
							tmp->frere=f;
							f->frere=courant;
							courant=f;
							word++;
							ajouterMot(courant,word,s);
                                                }				
                                       }
                                }
				else
				{
					f = (lettre*)malloc(sizeof(lettre));
                                        f->car=word[0];
                                        f->fils=NULL;
                                        f->pere=c;
					tmp->frere=f;
					word++;
					courant=f;
					ajouterMot(courant,word,s);
				}
                         }
                               } 
							   else 
							   {
								strcpy(courant->signification,s);
							   }
               }

// -ça marche-               
void ajouterlist(dico *l,dico *e){
	dico *p=NULL,*q=NULL;
	p=l;
	q=p->suiv;
	while(q!=NULL && strcmp(q->mot,e->mot)<0){
                  p=p->suiv;
                  q=q->suiv;
	}
	if(q==NULL){
                p->suiv=e;
                e->suiv=NULL;
        }
	else{
		e->suiv=q;
		p->suiv=e;
	}
}

// -ça marche-
void afficher(dico *l){
	if(l->suiv!=NULL){
		printf("\n\nLes mots contenus dans le dictionnaire sont : \n");
		dico *p;
		p=l->suiv;
		while(p!=NULL){
			printf("%s : %s.\n",p->mot,p->sign);
			p=p->suiv;
		}
	}
	else printf("\n\nLe dictionnaire ne contient aucun mot pour l'instant ! \n");
}

// Suppression aide -ça marche-
void supprimerlist(dico *l,char *x){
	dico *p=NULL,*q=NULL;
	q=l;
	p=l->suiv;
	while( p!=NULL){ 
           if(strcmp(p->mot,x)==0){
                                   q->suiv=p->suiv;
                                   free(p);
                                   p=NULL;
                                   p=q->suiv;
                                   }
           else{
                q=p;
                p=p->suiv;		
        }
        }
}

// Suppression d'un mot qui existe dans le dictionnaire -ça marche-
void supprimer(l R,dico *l,char x[]){
      dico *p,*q;
	  supprimerlist(l,x);	
	  afficher(l);
	  //printf("test1");
	  q=l;
	  p=l->suiv;
	  //printf("test2");
   	while(p!=NULL){
        //           printf("\nhere3\n");
		ajouterMot(R,p->mot,p->sign);
		//printf("\nhere4\n");
		q=p;
		p=p->suiv;
	}
}
	
// Fonction d'enregistrement du dictionnaire dans un fichier -ça marche-
void sauvegarderDictionnaire(dico *racine){
    FILE *fichier;
	dico *p;
	fichier=fopen("D:/bootstrap/dico.txt","a");
	p=racine->suiv;
	while(p!=NULL){
                   fprintf(fichier,"%s : %s\n",p->mot,p->sign);
                   p=p->suiv;
                   }
                   fclose(fichier);
     }

// Fonction de récupération d'un dicionnaire prèalablement sauvgardé dans un fichier -ça marche-
void chargerDictionnaire(lettre *R,dico *l){
	FILE *fichier;
	dico *e,*p,*q;
	char m[20],d[200];
	fichier=fopen("D:/bootstrap/dico.txt","r");
	while(fscanf(fichier,"%s : %s",m,d)==2){ 
	    e=(dico*)malloc(sizeof(dico));
	    strcpy(e->mot,m);
    	strcpy(e->sign,d);
		ajouterlist(l,e);
	}
      q=l;
	  p=l->suiv;
    while( p!=NULL){ 
		ajouterMot(R,p->mot,p->sign);
		q=p;
		p=p->suiv;
	}
}

// Affichage de tous les mots du dictionnaire par ordre alphabétique (Version recursive - Encore un problème -)
void afficherDictionnaire(l racine){
                            if(racine!=NULL){
                                              printf("%c",racine->car);
                                              afficherDictionnaire(racine->fils);
                                              printf("\n");
                                              afficherDictionnaire(racine->frere);
                                              }
                         }
                         
                         
                         
void menuPrincipal(){
    lettre *racine;
	dico *l,*e,*a;
	char mot[20],signi[200];
	int i=1;
	char choix;
	racine=creerDictionnaire();
	l=(dico*)malloc(sizeof(dico));
	if(l==NULL){
		printf("Not Enough Memory !!");
		exit (-1);
	}
	strcpy(l->mot,"null");
	strcpy(l->sign,"null");
	l->suiv=NULL;

	system ("Color 30");
	do{
        system ("cls");
        printf("\t\t\t****************************************\n");
        printf("\t\t\t****************************************\n");
        printf("\t\t\t##                                    ##\n");
        printf("\t\t\t##      Realise par :                 ##\n");
        printf("\t\t\t##          * KABBAB Rachid           ##\n");
        printf("\t\t\t##      Ecole / Annee :               ##\n");
		printf("\t\t\t##   	      * ENSMR (Ex.ENIM) 2017  ##\n");
        printf("\t\t\t****************************************\n");
        printf("\t\t\t****************************************\n");
        printf("\n\n\n");
        
        printf("\t\t                  GESTION DU DICTIONNAIRE \n");
        printf("\t\t\t________________________________________\n");
        printf("\t\t\t| |                                    |\n");
        printf("\t\t\t|1|           Ajouter un mot           |\n");
        printf("\t\t\t| |                                    |\n");
        printf("\t\t\t========================================\n");
        printf("\t\t\t| |                                    |\n");
        printf("\t\t\t|2|          Chercher un mot           |\n");
        printf("\t\t\t| |                                    |\n");
        printf("\t\t\t========================================\n");
        printf("\t\t\t| |                                    |\n");
        printf("\t\t\t|3|        Lister tous les mots        |\n");
        printf("\t\t\t| |                                    |\n");
        printf("\t\t\t========================================\n");
        printf("\t\t\t| |                                    |\n");
        printf("\t\t\t|4|           Supprimer un mot         |\n");
        printf("\t\t\t| |                                    |\n");
        printf("\t\t\t========================================\n");
        printf("\t\t\t| |                                    |\n");
        printf("\t\t\t|5|       Enregistrer dictionnaire     |\n");
        printf("\t\t\t| |                                    |\n");
        printf("\t\t\t========================================\n");
        printf("\t\t\t| |                                    |\n");
        printf("\t\t\t|6|         Charger dictionnaire       |\n");
        printf("\t\t\t| |                                    |\n");
        printf("\t\t\t========================================\n");
        printf("\t\t\t| |                                    |\n");
        printf("\t\t\t|7|               Quitter              |\n");
        printf("\t\t\t| |                                    |\n");
        printf("\t\t\t========================================\n");
		printf("\n\r Veuillez choisir une option SVP ?  (1/2/3/4/5/6) : \n");
        choix=toupper(getch());
        switch(choix){
			case '1' : system ("cls");
			//system ("Color 35");
			           printf("\t\t\t________________________________________\n");
                       printf("\t\t\t||                                    ||\n");
                       printf("\t\t\t||           Ajouter un mot           ||\n");
                       printf("\t\t\t||                                    ||\n");
                       printf("\t\t\t========================================\n");
                       printf("\n\r Quel est le nom que vous voulez ajouter ?  \n\n");
                       
                       puts("Saisir le mot a ajouter :");
            gets(mot);
	        e=(dico*)malloc(sizeof(dico));
	        strcpy(e->mot,mot);
        	puts("Sa signification :");
            //getchar();
            gets(signi);
        	strcpy(e->sign,signi);
        	ajouterMot(racine,mot,signi);
        	ajouterlist(l,e);
                       printf("Le mot ajoute avec succes");
                       printf("\n\nAppuyer sur une touche pour revenir au menu\n");
                       getch();
                       break;

            case '2' : system ("cls");
                       printf("\t\t\t________________________________________\n");
                       printf("\t\t\t||                                    ||\n");
                       printf("\t\t\t||            Chercher un mot         ||\n");
                       printf("\t\t\t||                                    ||\n");
                       printf("\t\t\t========================================\n");
                       printf("Saisir le mot que vous voulez chercher ? ");
			           scanf("%s",&mot);
			           if(chercher(racine,mot)){
                                              puts(mot);
                                              printf("Le mot existe bien");
                                              }
                                              else{
                                                   printf("Ce mot n\'existe pas.\n");
                       }
			           printf("\nAppuyer sur une touche pour revenir au menu\n");
                       getch();
			           break;
            case '3' : system ("cls");
			           printf("\t\t\t________________________________________\n");
                       printf("\t\t\t||                                    ||\n");
                       printf("\t\t\t||         Lister tous les mots       ||\n");
                       printf("\t\t\t||                                    ||\n");
                       printf("\t\t\t========================================\n");           
                       afficher(l);
			           printf("\nAppuyer sur n\'importe quelle touche pour revenir au menu principal\n");
                       getch();
			           break;
            case '4' : system ("cls");
			                   printf("\t\t\t________________________________________\n");
                               printf("\t\t\t||                                    ||\n");
                               printf("\t\t\t||           Supprimer un mot         ||\n");
                               printf("\t\t\t||                                    ||\n");
                               printf("\t\t\t========================================\n");

                       printf("\n\r Quel mot voulez-vous supprimer ?  \n\n");
			           scanf("%s",&mot);
			           detruireDictionnaire(racine);
                       racine=creerDictionnaire();
                       supprimer(racine,l,mot);
			           printf("\n Appuyer sur n\'importe quelle touche pour revenir au menu principal\n");
                       getch();
			           break;
            case '5' : system ("cls");
			                   printf("\t\t\t________________________________________\n");
                               printf("\t\t\t||                                    ||\n");
                               printf("\t\t\t||      Enregistrer dictionnaire      ||\n");
                               printf("\t\t\t||                                    ||\n");
                               printf("\t\t\t========================================\n");
                               sauvegarderDictionnaire(l);
                               printf("Le dictionnaire a ete bien enregistre");
                               printf("\n Appuyer sur n\'importe quelle touche pour revenir au menu principal\n");
                       getch(); 
			           break;
			case '6' : system ("cls");
			                   printf("\t\t\t________________________________________\n");
                               printf("\t\t\t||                                    ||\n");
                               printf("\t\t\t||        Charger dictionnaire        ||\n");
                               printf("\t\t\t||                                    ||\n");
                               printf("\t\t\t========================================\n");
                               chargerDictionnaire(racine,l);
                               printf("Le dictionnaire a ete bien charge");
                               printf("\n Appuyer sur une touche pour revenir au menu\n");
                       getch(); 
			           break;
            case '7' : system ("cls");
			                   printf("\t\t\t________________________________________\n");
                               printf("\t\t\t||                                    ||\n");
                               printf("\t\t\t||                Quitter             ||\n");
                               printf("\t\t\t||                                    ||\n");
                               printf("\t\t\t========================================\n");
                               exit(0);
                               printf("Le dictionnaire a ete bien charge");
                               printf("\n Appuyer sur n\'importe quelle touche pour revenir au menu principal\n");
                       getch(); 
			           break;
			default:
                {
                    printf("numero de menu invalide\n");
                    Sleep(2000);
                }
			}
	}while(1==1);

}
                         
                         
                         

int main(){
    
    /*
    system ("color 30");
    lettre *racine;
	dico *l,*e,*a;
	char x[20],df[200];
	int i=1,k;
	racine=creerDictionnaire();
	l=(dico*)malloc(sizeof(dico));
	strcpy(l->mot,"null");
	strcpy(l->sign,"null");
	l->suiv=NULL;
	while(i!=0){
		printf("1 ajouter:\n2 chercher:\n3 afficher la list des mots:\n4 afficher le contenu:\n5 supprimer:\n6 sauvgarder:\n7 charger:\n8 quitter:\n");
		scanf("%d",&k);
		if(k==1){
			puts("Saisir le mot a ajouter :");
			getchar();
            gets(x);
	        e=(dico*)malloc(sizeof(dico));
	        strcpy(e->mot,x);
        	puts("Sa signification :");
            gets(df);
        	strcpy(e->sign,df);
        	ajouterMot(racine,x,df);
        	ajouterlist(l,e);
		}
		if(k==2){
			printf("Saisir le mot que vous voulez chercher ? ");
			scanf("%s",&x);
			if(chercher(racine,x))
			{
				puts(x);
			}
			else{
				printf("Ce mot n\'existe pas.\n");
			}
		}
		if(k==3){
			afficher(l);
		}
		if(k==5){
			printf("Quel mot voulez-vous supprimer ? ");
			scanf("%s",&x);
			//printf("\navant det\n");
			detruireDictionnaire(racine);
			//racine=NULL;
			//printf("affichage de la liste  : ");
			//afficher(l);
            racine=creerDictionnaire();
            //printf("\n apres det \n");
			supprimer(racine,l,x);
		}
		if(k==6){
              sauvegarderDictionnaire(l);
              printf("Le fichier a ete bien cree");   
             }
        if(k==7){
                 chargerDictionnaire(racine,l);
                 printf("Le dictionnaire a ete bien charge");
                 }
		if(k==8){
			i=0;
		}
	}
    getch();
    return 0;*/
    SMALL_RECT windowSize = {0, 0 , 77 , 47};
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
    menuPrincipal();
    }
