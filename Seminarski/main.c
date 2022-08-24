//Igor Vukovic NRT-36/19

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 80
#define BR_POKUSAJA 5


struct REC{char rec[MAX+1],uneta_rec[MAX+1],uneto_slovo,pom[MAX+1];};
typedef enum {Citanje,Memorija,Otvaranje}Greska;

char *greske[]={ "\nProblem sa citanjem imena!!!\n", "\nProblem sa dodelom memorije!!!\n", 
				"\nProblem sa otvaranjem datoteke!!!\n"};

void greska_ispis(Greska);
void ispis_slova(char niz_slova[MAX+1], int brojac);
main()
{
	FILE *fptr;
	int i=0,brojac=0,RedniBrTrazReci,pokusaj=0,pozicija,ima,pogodjeno=0;
	char Da[3][3]={"Da","da","DA"},pom_odg[2],Ne[3][3]={"Ne","ne","NE"},uneta_rec[BR_POKUSAJA][MAX+1],opet[2],niz_slova[MAX+1];
	struct REC *prec;

	prec=(struct REC *)malloc(sizeof(struct REC));
	if(prec==NULL)
		greska_ispis(Memorija);
	if((fptr=fopen("biblioteka.txt", "r"))==NULL)
		greska_ispis(Otvaranje);

	printf("\t\t\tIGRA VESANJA\n\n");
	printf("Zadatak:\nPogodite zadato ime. Koristi se mala slova ,engleska abeceda osim (Q,W,Y,X).\n");
	printf("Imate 5 pokusaja da pogodite rec.\n\n");
		do
		{
		srand(time(NULL)); //R-1
		RedniBrTrazReci=rand() % 322 + 1;

		while(i<RedniBrTrazReci)
		{
			fscanf(fptr,"%s",prec->rec);   //R-2
			i++;
		}
		if(fscanf(fptr,"%s",prec->rec)==NULL)
			greska_ispis(Citanje);
		
		for(i=0;i<strlen(prec->rec);i++) //R-3
		{
			if(i==0)
				strcpy(prec->pom,"_ ");
			else
				strcat(prec->pom,"_ ");
		}
		printf("\t\t%s\n", prec->pom);

		do //R-4
		{
			printf("Preostali broj pokusaja je %d \n", BR_POKUSAJA-pokusaj);
			printf("Zelite li da pogodite celo ime? (Da/Ne)\n");
			scanf("%s",&pom_odg);
			fflush(stdin);
				if(strcmp(pom_odg,Da[0])==0 || strcmp(pom_odg,Da[1])==0 || strcmp(pom_odg,Da[2])==0)
				{
					printf("Unesite ime:\n");
					scanf("%s", prec->uneta_rec);
					if(strcmp(prec->uneta_rec,prec->rec)==0)
					{
						pokusaj++;
						printf("Cestitamo, pogodili ste ime iz %d pokusaja.\n",pokusaj);
						pogodjeno=1;
						break;
					}
					else
					{
						printf("Niste pogodili ime.\n");  //R-6
						strcpy(uneta_rec[pokusaj],prec->uneta_rec);
						printf("Uneli ste imena:");
						for(i=0;i<=pokusaj;i++)
							printf(" %s ", uneta_rec[i]);
						printf("\n");
						pokusaj++;
					}
						printf("%s",prec->pom);
						printf("\n");
				}
				else if(strcmp(pom_odg,Ne[0])==0 || strcmp(pom_odg,Ne[1])==0 || strcmp(pom_odg,Ne[2])==0)
				{
					printf("Unesite slovo:\n");//R-7
					scanf("%c",&prec->uneto_slovo);
					pokusaj++;
					prec->uneto_slovo=toupper(prec->uneto_slovo);
					getchar();
					if(prec->uneto_slovo<'A' || prec->uneto_slovo>'Z' || prec->uneto_slovo=='Q' || prec->uneto_slovo=='W'
						|| prec->uneto_slovo=='Y' || prec->uneto_slovo=='X')
						printf("Niste uneli dobar karakter.\n");
					else
					{	
						if(prec->uneto_slovo==toupper(prec->uneto_slovo))
							prec->uneto_slovo=tolower(prec->uneto_slovo);
						ima=0;
						for(i=0;i<strlen(prec->rec);i++)
						{
							if(prec->rec[i]==prec->uneto_slovo)
							{
								ima=1;
								pozicija=i;
								prec->pom[pozicija*2]=prec->uneto_slovo;
								pogodjeno=1;
								pokusaj--;
							}
						}
						niz_slova[brojac]=prec->uneto_slovo;
						brojac++;
						if(ima==0)
						{
							printf("Ime ne sadrzi uneti karakter.\n");
							pogodjeno=0;
						}
						printf("%s",prec->pom);
						printf("\n");
						ispis_slova(niz_slova,brojac); //R-5
					}
				}
				else 
				{
					printf("Niste uneli dobar odgovor.\n");
				}
		}while(pokusaj<BR_POKUSAJA);
		if(pokusaj==BR_POKUSAJA) //R-6
			printf("Niste pogodili ime.\n Zadato ime je \"%s\"\n", prec->rec);
		printf("Da li zelite opet da igrate? (Da/Ne)\n");  
		scanf("%s", &opet);
		if(strcmp(Ne[0],opet)==0 || strcmp(Ne[1],opet)==0 || strcmp(Ne[2],opet)==0) //R-7
			exit(1);
		pokusaj=0;
	}while(opet!=Ne[0] || opet!=Ne[1] || opet!=Ne[2]);
}


void greska_ispis(Greska poruka) //R-8
{
	fprintf(stderr, greske[poruka]);
	exit(1);
}
void ispis_slova(char niz_slova[MAX+1], int brojac) //R-5
{
	int i;
	printf("Uneta slova: ");
	for(i=0;i<brojac;i++)
		printf("%c ", niz_slova[i]);
	printf("\n");
}

//R-1 Generator za brojeve
//R-2 Pretraga imena zadate preko generatora
//R-3 Zamena slova za _
//R-4 Petlja koja radi zadatak
//R-5 Funkcija za ispis slova
//R-6 Provera broja pokusaja
//R-7 Proverava za ponovnu igru
//R-8 Ispis greske