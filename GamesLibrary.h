#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
	int j_now;
	int j_exp;
}DateJour;

typedef struct
{
	int j;
	int m;
	int a;
}Date;

typedef struct
{
	char nom[30];
	char prenom[30];
	char adresse[100];
	int cp;
	char ville[30];
	int nbemprunt;
	DateJour d;
	Date da;
}Adherent;

typedef enum {Faux,Vrai}Booleen;

typedef struct
{
	int emprunte;
	char nomj[30];
	char enom[30];
	char eprenom[30];
	char type[30];
	DateJour dEmprunt;
}Jeux;

typedef struct maillon
{	
	Jeux j;
	struct maillon *suiv;
}Maillon, *Liste;

typedef struct maillon2
{	
	char nom[30];
	char prenom[30];
	struct maillon2 *suiv;
}MaillonGuest, *ListeGuest;

typedef struct
{	
	char theme[30];
	int nbP;
	char horaire[7];
	Date d;
}Aprem;

typedef struct
{	
	Aprem a;
	ListeGuest g;
}ApremGuest;


/*	MAIN	*/
int main (void);

/*	ADHERENTS	*/
void chargerAdherent(Adherent *tadherent[], int *n, int *max);
void enregistrerAdherent (Adherent *tadherent[], int *n, int *max);
void afficherAdherent(Adherent *tadherent[], int n);
void afficher(Adherent *tadherent[], int n);
void triDico (Adherent *tadherent[], int n);
void copier (Adherent *t[], int i, int j, Adherent *R[]);
void fusion (Adherent *R[], int n, Adherent *S[], int m, Adherent *T[]);
int rech (Adherent *tadherent[], int n, char nom[], char prenom[]);
void suppression (Adherent *tadherent[],int *n);
void decalerAGauche(int i,Adherent *tadherent[], int *n);
void sauvegarderAdherent (Adherent *tadherent[], int n);

/*	FONCTIONS JEUX/EMPRUNTS	*/
Liste chargerJeux(Liste l);
Jeux lireJeu (FILE *flot);
Liste insertionEnTete (Liste l, Jeux b);
Liste ajoutEmprunt (Liste l, Adherent *tadherent[], int n, int a);
Liste insertion (Liste l, Jeux b);
Liste supt (Liste l);
Liste suppressionl (Liste l, char nomj[]);
void afficherListe (Liste l);
void afficherEmprunt (Liste l, Adherent  *tadherent[], int n);
void SaveJeux(FILE *flot, Liste l);
Liste ajouterJeu (Liste l);
void sauvegarderJeux(Liste l);

/*	FONCTION CONTROLE TEMPS	*/
DateJour setDayEmp (void);
DateJour setDayIns (void);
Date setDate (void);
void controleDate (ApremGuest *taprem[], int *n);
Liste rechRetard (Liste l);
void afficherRetards (Liste l);
void renouvellement(Adherent *tadherent[], int n);

/*	FONCTIONS CHECK DE LISTES	*/
Liste listeVide (void);
char* tetenomj (Liste l);
char* tetenom(Liste l);
char* teteprenom (Liste l);
Booleen vide (Liste l);
Booleen videGuest (ListeGuest l);
Liste rechl (Liste l, char nomj[]);
Liste rechEmprunteur (Liste l, char nom[],char prenom[]);
char* tetenomGuest (ListeGuest l);
int longueur (ListeGuest l);
ListeGuest listeVideGuest (void);

/*	FONCTIONS APRÈS-MIDI	*/
ListeGuest insertionEnTeteGuest (ListeGuest l, char nom[], char prenom[]);
ListeGuest insertionGuest (ListeGuest l, char nom[], char prenom[]);
int chargerAprem (ApremGuest *taprem[], int *maxx);
ApremGuest lireAprem (FILE *flot);
void affichAprem (ApremGuest *taprem[], int *n);
void triDicoAprem (ApremGuest *taprem[], int n);
void copierAprem (ApremGuest *t[], int i, int j, ApremGuest *R[]);
void fusionAprem (ApremGuest *R[], int n, ApremGuest *S[], int m, ApremGuest *T[]);
void ajoutAprem(ApremGuest *taprem[], int *n, int *maxx);
void supprAprem (ApremGuest *taprem[], int *n);
void decalerAGaucheAprem(int i, ApremGuest *taprem[], int *n);
void ajoutGuest (ApremGuest *taprem[], Adherent *tadherent[], int n, int a);
void affichAllAprem (ApremGuest *taprem[], int *n);
void sauvegarderAprem (ApremGuest *taprem[], int n);
ListeGuest rechGuest (ListeGuest l, char nom[], char prenom[]);
ListeGuest suptGuest (ListeGuest l);
ListeGuest suppressionGuest (ListeGuest l, char nom[], char prenom[]);
int rechDico(ApremGuest *taprem[], int nb, char theme[], char horaire[], int *res);