#include "GamesLibrary.h"

/*  Nom : chargerAdherent();
    Finalité : Permettre de charger depuis un fichier binaire les adhérents enregistrés
    Description Générale : La fonction ouvre le fichier puis lit un premier chiffre qui indique le nombre de structure adhérent à lire.
    	Elle réalloue dans le cas où elle atteint la taille maximum du tableau.
    Elle lit ensuite chaque structure adhérent et renvoit par adresse la taille logique du tableau. 
*/

void chargerAdherent(Adherent *tadherent[], int *n, int *max)
{
	FILE *flot;
	int i=0;
	Adherent **aux;
	flot=fopen("adherent.bin","rb");
	if(flot==NULL)
		{
			puts("Problème ouverture de -adherent.bin-");
			exit(1);
		}
	fscanf(flot,"%d%*c",n);
	while(i<*n)
	{
		if(i==*max-1)
		{
			aux=(Adherent**)realloc(tadherent,5*sizeof(Adherent*));
			if(aux==NULL)
			{
				puts("Problème realloc");
				exit(1);
			}
			tadherent=aux;
			*max+=5;
			free(aux);
		}
		tadherent[i]=(Adherent*)malloc(sizeof(Adherent));
		if(tadherent[i]==NULL)
		{
			printf("Problème malloc\n");
			exit(1);
		}
		fread(tadherent[i],sizeof(Adherent), 1, flot);
		i++;
	}
	fclose(flot);
}

/*  Nom : chargerJeux();
    Finalité : Permettre de charger depuis un fichier de données les jeux enregistrés
    Description Générale : La fonction ouvre le fichier, lit grâce à lireJeu() et insère avec insertion()
*/

Liste chargerJeux(Liste l) 
{ 
	FILE *flot;
	Jeux b;
 	flot=fopen("jeux.don","r");
 	if(flot==NULL)
  	{
   		puts("Problème ouverture de -jeux.don-");
   		exit(1);
  	}
  	b=lireJeu(flot);
  	while(!feof(flot))
	{
		l=insertion(l,b);
		b=lireJeu(flot);
	}
	l=insertion(l,b);
 	return l;
 	fclose(flot);
}

/*  Nom : lireJeu();
    Finalité : Permettre de lire un jeu dans le fichier 
    Description Générale : Elle déclare une structure jeux dont elle remplie tous les champs avec les données lues grâce au flot puis retourne la structure
*/

Jeux lireJeu (FILE *flot)
{
	Jeux b;
	fscanf(flot,"%d\t",&b.emprunte);
 	fgets(b.nomj,30,flot);
	b.nomj[strlen(b.nomj)-1]='\0';
	fgets(b.enom,30,flot);
	b.enom[strlen(b.enom)-1]='\0';
	fgets(b.eprenom,30,flot);
	b.eprenom[strlen(b.eprenom)-1]='\0';
	fgets(b.type,30,flot);
	b.type[strlen(b.type)-1]='\0';
	fscanf(flot,"%d\t%d\n",&b.dEmprunt.j_now,&b.dEmprunt.j_exp);
	return b;
}

/*  Nom : enregistrerAdherent();
    Finalité : Permettre d'ajouter un adhérent 
    Description Générale : L'utilisateur rentre chaque champ qui compose une structure adhérent, si celui-ci existe la fonction propose de recommencer ou de 
    retourner au menu.
    Dans le cas contraire elle demande les derniers champs, initialise les valeurs de temps. Elle réalloue si la taille physique est atteinte puis insère 
    la structure dans le tableau à la fin. 
*/

void enregistrerAdherent (Adherent *tadherent[], int *n, int *max) 
{
	Adherent ad,**aux;
	int r=0,choix;
	while(r!=-1)
	{
		printf("Nom : ");
		fgets(ad.nom,30,stdin);
		ad.nom[strlen(ad.nom)-1]='\0';
		printf("Prénom : ");
		fgets(ad.prenom,30,stdin);
		ad.prenom[strlen(ad.prenom)-1]='\0';
		r=rech(tadherent,*n,ad.nom,ad.prenom);
		if(r!=-1)
		{
			puts("Utilisateur déja existant, tapez 1 pour recommencer, 20 pour retourner au menu");
			scanf("%d%*c", &choix);
			if(choix==20)
				return;
			continue;
		}
	}
	printf("Adresse : ");
	fgets(ad.adresse,100,stdin);
	ad.adresse[strlen(ad.adresse)-1]='\0';
	printf("Code Postal : ");
	scanf("%d%*c",&ad.cp);
	printf("Ville : ");
	fgets(ad.ville,30,stdin);
	ad.ville[strlen(ad.ville)-1]='\0';
	ad.nbemprunt=0;
	ad.d=setDayIns();
	ad.da=setDate();
	if(*n==*max-1)
	{
		aux=(Adherent**)realloc(tadherent,5*sizeof(Adherent*));
		if(aux==NULL)
		{
			puts("Problème realloc");
			exit(1);
		}
		tadherent=aux;
		(*max)+=5;
		free(aux);
	}
	tadherent[*n]=(Adherent*)malloc(sizeof(Adherent));
	if(tadherent[*n]==NULL)
	{
		puts("Problème de malloc");
		exit(1);
	}
	*tadherent[*n]=ad;
	(*n)++;
}

/*  Nom : afficher();
    Finalité : Permettre d'afficher tous les adhérents
    Description Générale : La fonction affiche tous les adhérents, compare la date d'emprunt à celle d'aujourd'hui et affiche en conséquence
*/

void afficher(Adherent *tadherent[], int n)
{
	int i;
	DateJour d;
	d=setDayIns();
	puts("-----------------------------");
	for(i=0;i<n;i++)
		if(d.j_now<tadherent[i]->d.j_exp)
		{	
			printf("Nom : %s\nPrénom : %s\nAdresse : %s\nCode Postal : %d\nVille : %s\nNombre d'emprunts en cours : %d\nDate d'inscription : %d/%02d/%d (Temps restant avant ré-inscription : %d jour(s))\n",tadherent[i]->nom,tadherent[i]->prenom,tadherent[i]->adresse,tadherent[i]->cp,tadherent[i]->ville,tadherent[i]->nbemprunt,tadherent[i]->da.j,tadherent[i]->da.m,tadherent[i]->da.a,tadherent[i]->d.j_exp-d.j_now);
			puts("-----------------------------");
		}
		else 
		{	
			printf("Nom : %s\nPrénom : %s\nAdresse : %s\nCode Postal : %d\nVille : %s\nNombre d'emprunts en cours : %d\nDate d'inscription : %d/%02d/%d (Attention ! Renouvellement d'inscription nécessaire !)\n",tadherent[i]->nom,tadherent[i]->prenom,tadherent[i]->adresse,tadherent[i]->cp,tadherent[i]->ville,tadherent[i]->nbemprunt,tadherent[i]->da.j,tadherent[i]->da.m,tadherent[i]->da.a);
			puts("-----------------------------");
		}
}

/*  Nom : afficherAdherent();
    Finalité : Permettre d'afficher un adhérent
    Description Générale : La fonction affiche un adhérent selon le nom et prénom donnés par l'utilisateur, boucle à l'infini si celui-ci n'existe pas 
*/

void afficherAdherent(Adherent *tadherent[], int n)
{
		char nom[30], prenom[30];
		int r=-1,choix;
		while(r==-1)
		{
			printf("Nom de l'adhérent : ");
			fgets(nom,30,stdin);
			nom[strlen(nom)-1]='\0';
			printf("Prénom de l'adhérent : ");
			fgets(prenom,30,stdin);
			prenom[strlen(prenom)-1]='\0';
			r=rech(tadherent,n,nom,prenom);
			if(r==-1)
			{
				puts("Adhérent inexistant, tapez 1 pour recommencer, 20 pour retourner au menu");
				scanf("%d%*c", &choix);
				if(choix==20)
					return;
			}
		}
		printf("%s\n%s\n%s\n%d\n%s\n%d\n%d/%d/%d\n",tadherent[r]->nom,tadherent[r]->prenom,tadherent[r]->adresse,tadherent[r]->cp,tadherent[r]->ville,tadherent[r]->nbemprunt,tadherent[r]->da.j,tadherent[r]->da.m,tadherent[r]->da.a);
}

/*  Nom : sauvegarderAdherent();
    Finalité : Permettre de sauvegarder dans un fichier binaire tous les adhérents
    Description Générale : La fonction ouvre le fichier ou le créer si il n'existe pas. Puis ajoute autant de fois que nécessaire 
    (selon taille logique) les structures adhérents du tableau
*/

void sauvegarderAdherent (Adherent *tadherent[], int n)
{
	FILE *flot;
	int i;
	flot=fopen("adherent.bin","wb");
	if(flot==NULL)
	{
		puts("Problème de sauvegarde du fichier -adherent.bin-");
		exit(1);
	}
	fprintf(flot,"%d\n",n);
	for(i=0;i<n;i++)
		fwrite(*(tadherent+i),sizeof(Adherent),1,flot);
	fclose(flot);
}

/*  Nom : triDico();
    Finalité : Permettre de trier un tableau d'adhérents
    Description Générale : Fonction de tri dichotomique vue en cours et réadaptée
*/

void triDico (Adherent *tadherent[], int n)
{
	Adherent **R, **S;
	if(n<=1)
		return;
	R=(Adherent**)malloc((n/2)*sizeof(Adherent*));
	S=(Adherent**)malloc((n-n/2)*sizeof(Adherent*));
	if(R==NULL || S==NULL)
	{
		puts("Problème de malloc");
		exit(1);
	}
	copier(tadherent,0,n/2,R);
	copier(tadherent,n/2,n,S);
	triDico(R,n/2);
	triDico(S, n-n/2);
	fusion(R,n/2,S,n-n/2,tadherent);
	free(R);
	free(S);
}

/*  Nom : copier();
    Finalité : Permettre de un tableau R dans un tableau d'adhérent
    Description Générale : Fonction de copie relative au tri dichotomique vue en cours et réadaptée
*/

void copier (Adherent *t[], int i, int j, Adherent *R[])
{
	int k=0;
	while(i<j)
	{
		R[k]=t[i];
		i++;
		k++;
	}
}

/*  Nom : fusion();
    Finalité : Permettre de fusionner deux tableaux
    Description Générale : Fonction de fusion relative au tri dichotomique vue en cours et réadaptée
*/

void fusion (Adherent *R[], int n, Adherent *S[], int m, Adherent *T[])
{
	int i=0,j=0,k=0;
	while(i<n && j<m)
	{
		if(strcmp(R[i]->nom, S[j]->nom) <= 0)
		{
			T[k]=R[i];
			i++;
		}
		else
		{
			T[k]=S[j];
			j++;
		}
	k++;
	}
	while(i<n)
	{
		T[k]=R[i];
		i++;
		k++;
	}
	while(j<m)
	{
		T[k]=S[j];
		j++;
		k++;
	}
}

/*  Nom : setDayEmp();
    Finalité : Permettre de récupérer le nombre de jour de 1900 à aujourd'hui et la date d'expiration d'un emprunt depuis cette date
    Description Générale : La fonction récupère la structure tm de la librairie time.h puis utilise ses diverses fonctionnalités pour calculer le nombre de jour 
    de 1900 à aujourd'hui puis donne la date d'expiration d'un emprunt (+ 3 semaines*7 jours) et retourne la structure
*/

DateJour setDayEmp (void)
{
	DateJour d; 
    time_t now = time (NULL);  /* lire l'heure courante */
    struct tm tm_now = *localtime (&now); /* la convertir en heure locale */
    d.j_now=(tm_now.tm_year*365)+tm_now.tm_yday;
    d.j_exp=d.j_now+21;
    return d;
}

/*  Nom : setDayIns();
    Finalité : Permettre de récupérer le nombre de jour de 1900 à aujourd'hui et la date d'expiration d'une inscription depuis cette date
    Description Générale : La fonction récupère la structure tm de la librairie time.h puis utilise ses diverses fonctionnalités pour calculer le nombre de jour 
    de 1900 à aujourd'hui puis donne la date d'expiration d'une inscription (+ 365 jours) et retourne la structure
*/

DateJour setDayIns (void)
{
	DateJour d; 
    time_t now = time (NULL);  /* lire l'heure courante */
    struct tm tm_now = *localtime (&now); /* la convertir en heure locale */
    d.j_now=(tm_now.tm_year*365)+tm_now.tm_yday; /*tm_now.tm_year = nombre d'années depuis 1900 et tm_now.tm_yday = Nombre de jours depuis le début de cette année*/
    d.j_exp=d.j_now+365;
    return d;
}

/*  Nom : setDate();
    Finalité : Permettre de récupérer la date jj/mm/aaaa d'aujourd'hui
    Description Générale : La fonction récupère la structure tm de la librairie time.h puis utilise ses diverses fonctionnalités pour calculer l'année actuelle,
    le mois actuelle et le jour de la semaine et retourne la structure
*/

Date setDate (void)
{
	Date d; 
    time_t now = time (NULL);  /* lire l'heure courante */
    struct tm tm_now = *localtime (&now); /* la convertir en heure locale */
    d.j=tm_now.tm_mday;
    d.m=1+tm_now.tm_mon;
    d.a=1900+tm_now.tm_year;
    return d;
}

/*  Nom : rech();
    Finalité : Permettre de rechercher un nom/prenom dans un tableau tadherent
    Description Générale : La fonction récupère le nom et prenom en argument et compare élément par élément dans le tableau si ceux-ci correspondent. 
    Si non, elle retourne -1
*/

int rech (Adherent *tadherent[], int n, char nom[], char prenom[]) 
{
	int i=0;
	while(i<n)
	{
		if (strcmp(tadherent[i]->nom,nom)==0 && strcmp(tadherent[i]->prenom,prenom)==0)
			return i;
		i++;
	}
	return -1;
}

/*  Nom : suppression();
    Finalité : Permettre de supprimer un adherent
    Description Générale : La fonction demande à l'utilisateur le nom et prenom à supprimer et appelle décalerAgauche pour supprimer si elle trouve cet adhérent 
    dans le tableau, sinon elle propose de recommencer ou de retourner au menu
*/

void suppression (Adherent *tadherent[],int *n)
{
	char nom[30], prenom[30];
	int r=-1,choix;
	while(r==-1)
	{
		printf("Nom de l'adhérent : ");
		fgets(nom,30,stdin);
		nom[strlen(nom)-1]='\0';
		printf("Prénom de l'adhérent : ");
		fgets(prenom,30,stdin);
		prenom[strlen(prenom)-1]='\0';
		r=rech(tadherent,*n,nom,prenom);
		if(r==-1)
		{
			puts("Adhérent inexistant, tapez 1 pour recommencer, 20 pour retourner au menu");
			scanf("%d%*c", &choix);
			if(choix==20)
				return;
		}
	}
	decalerAGauche(r,tadherent,n);
}

/*  Nom : decalerAGauche();
    Finalité : Permettre de supprimer un adherent par décalage à gauche
    Description Générale : La fonction reçoit en argument le tableau et l'indice de suppression. Elle part de la fin du tableau et 
    copie l'élement suivant dans l'élément précédant.
*/

void decalerAGauche(int i, Adherent *tadherent[], int *n)
{
	Adherent *aux;
	int j;
	aux=tadherent[i];
	for (j=i; j<*n; j++)
		tadherent[j]=tadherent[j+1];
	(*n)--;
	free(aux);
}

/*  Nom : listeVide();
    Finalité : Permettre de vider une liste
    Description Générale : La fonction renvoit NULL
*/

Liste listeVide (void)
{
	return NULL;
}

/*  Nom : tetenomj();
    Finalité : Permettre de retourner le nom de jeu en tête de la liste
    Description Générale : La fonction renvoit le nom de jeu en tête de la liste
*/

char* tetenomj (Liste l)
{
	if(vide(l))
	{
		puts("Opération interdite");
		exit(1);
	}
	return l->j.nomj;
}

/*  Nom : teteprenom();
    Finalité : Permettre de retourner le prenom en tête de la liste
    Description Générale : La fonction renvoit le prenom en tête de la liste
*/

char* teteprenom (Liste l)
{
	if(vide(l))
	{
		puts("Opération interdite");
		exit(1);
	}
	return l->j.eprenom;
}

/*  Nom : tetenom();
    Finalité : Permettre de retourner le nom en tête de la liste
    Description Générale : La fonction renvoit le nom en tête de la liste
*/

char* tetenom (Liste l)
{
	if(vide(l))
	{
		puts("Opération interdite");
		exit(1);
	}
	return l->j.enom;
}

/*  Nom : vide();
    Finalité : Permettre de savoir si une liste est vide
    Description Générale : La fonction renvoit vrai si la liste est vide, faux sinon
*/

Booleen vide (Liste l)
{
	if(l==NULL)
		return Vrai;
	return Faux;
}

/*  Nom : videGuest();
    Finalité : Permettre de savoir si une liste est vide
    Description Générale : La fonction renvoit vrai si la liste est vide, faux sinon
*/

Booleen videGuest (ListeGuest l)
{
	if(l==NULL)
		return Vrai;
	return Faux;
}

/*  Nom : insertionEnTete();
    Finalité : Permettre d'insérer une structure en tête
    Description Générale : La fonction alloue un maillon qu'elle remplit avec la structure passée en argument et mets l'adresse de la prochaine liste dans m->suiv
*/

Liste insertionEnTete (Liste l, Jeux b)
{
	Maillon *m;
	m=(Maillon*)malloc(sizeof(Maillon));
	if (m==NULL)
	{
		puts("Problème malloc");
		exit(1);
	}
	m->j=b;
	m->suiv=l;
	return m;
}

/*  Nom : insertion();
    Finalité : Permettre d'insérer dans l'ordre alphabétique
    Description Générale : La fonction contrôle si la liste est vide, si oui elle insère en tête
    	Puis si l'élément qu'on veut insérer est plus proche dans l'alphabet, si oui on l'insère
    	Si l'élément est déjà présent, on ne l'insère pas. 
    	Le tout en récursif pour parcourir toute la liste 
*/

Liste insertion (Liste l, Jeux b)
{
	if(vide(l))
		return insertionEnTete(l,b);
	if(strcmp(b.nomj,tetenomj(l))<0)
		return insertionEnTete(l,b);
	if (strcmp(b.nomj,tetenomj(l))==0)
		return l;
	l->suiv=insertion(l->suiv,b);
	return l;
}

/*  Nom : ajouterJeu();
    Finalité : Permettre d'ajouter un jeu
    Description Générale : La fonction propose une boucle infini tant que l'utilisateur ne saisit pas un jeu absent de la liste ou qu'il ne souhaite pas 
    revenir au menu. Sinon elle prend toutes les informations nécessaires à l'enregistrement et les insère grâce à la fonction insertion().
*/

Liste ajouterJeu (Liste l)
{
	Liste v;
	Jeux j;
	int choix=1;
	char nomj[30],type[30];
	while(choix==1)
	{
		printf("Nom du jeu : ");
		fgets(nomj,30,stdin);
		nomj[strlen(nomj)-1]='\0';
		v=rechl(l,nomj);
		if(!(vide(v)))
		{
			puts("Jeu déja présent, tapez 1 pour recommencer, 20 pour retourner au menu");
			scanf("%d%*c", &choix);
			if(choix==20)
				return;
			continue;
		}
		else
		{
			printf("Type de jeu : ");
			fgets(type,30,stdin);
			type[strlen(type)-1]='\0';
			j.emprunte=0;
			strcpy(j.nomj,nomj);
			strcpy(j.enom,"Non Renseigné");
			strcpy(j.eprenom,"Non Renseigné");
			strcpy(j.type,type);
			j.dEmprunt.j_now=0;
			j.dEmprunt.j_exp=0;
			l=insertion(l,j);
			choix=20;
		}
	}
	return l;
}

/*  Nom : ajoutEmprunt();
    Finalité : Permettre d'ajouter ou supprimer un emprunt selon la constante reçu dans la variable 'int a'
    Description Générale : Si la constante est 1, la fonction propose une boucle infini tant que l'utilisateur ne saisit pas un adhérent ou un jeu existant 
    et/ou dont l'inscription n'est plus valide.
    Elle contrôle également si l'adhérent n'a pas plus de 3 emprunts. Elle affiche en fonction des conditions un message d'erreur à l'utilisateur et 
    l'incite à recommencer l'opération. 
    Si la constante est 2, la fonction vérifie si l'adhérent tapé possède bien un emprunt à ce nom sinon affiche une erreur et incite à recommencer. 
*/

Liste ajoutEmprunt (Liste l, Adherent *tadherent[], int n, int a)
{
	char nom[30], prenom[30], nomj[30];
	int r=-1,choix;
	DateJour d;
	Liste v;
	while(r==-1 || vide(v))
	{
		printf("Nom de l'adhérent : ");
		fgets(nom,30,stdin);
		nom[strlen(nom)-1]='\0';
		printf("Prénom de l'adhérent : ");
		fgets(prenom,30,stdin);
		prenom[strlen(prenom)-1]='\0';
		r=rech(tadherent,n,nom,prenom);
		d=setDayIns();
		if(r!=-1 && d.j_now>tadherent[r]->d.j_exp)
		{
			puts("Renouvellement d'inscription nécessaire avant de pouvoir ré-emprunter");
			return l;
		}
		printf("Nom du jeu : ");
		fgets(nomj,30,stdin);
		nomj[strlen(nomj)-1]='\0';
		v=rechl(l,nomj);
		if(r==-1)
		{
			puts("Adhérent inexistant, tapez 1 pour recommencer, 20 pour retourner au menu");
			scanf("%d%*c", &choix);
			if(choix==20)
				return l;
			continue;
		}
		else if(vide(v))
		{
			puts("Jeu inexistant, tapez 1 pour recommencer, 20 pour retourner au menu");
			scanf("%d%*c", &choix);
			if(choix==20)
				return l;
			continue;
		}
		else if(tadherent[r]->nbemprunt<3 && v->j.emprunte==0 && a==1)
		{
			strcpy(v->j.enom,nom);
			strcpy(v->j.eprenom,prenom);
			v->j.emprunte=1;
			(tadherent[r]->nbemprunt)++;
			v->j.dEmprunt=setDayEmp();
		}
		else if(strcmp(v->j.enom,nom)!=0 && strcmp(v->j.eprenom,prenom)!=0 && a==2)
		{
			puts("Aucun emprunt à ce nom, tapez 1 pour recommencer, 20 pour retourner au menu");
			scanf("%d%*c", &choix);
			if(choix==20)
				return l;
			r=-1;
			continue;
		}
		else if(tadherent[r]->nbemprunt>0 && v->j.emprunte==1 && a==2)
		{
			strcpy(v->j.enom,"Non Renseigné");
			strcpy(v->j.eprenom,"Non Renseigné");
			v->j.emprunte=0;
			v->j.dEmprunt.j_now=0;
			v->j.dEmprunt.j_exp=0;
			(tadherent[r]->nbemprunt)--;
		}
		if(tadherent[r]->nbemprunt==2)
		{
			puts("Nombre maximum d'emprunts atteint pour cet adhérent");
			return;
		}
	}
	return l;
}

/*  Nom : rechl();
    Finalité : Permettre de rechercher dans une liste un nom de jeu 
    Description Générale : La fonction recherche en récursif la liste contenant le nom de jeu passé en argument. 
*/

Liste rechl (Liste l, char nomj[])
{
	if(vide(l))
		return NULL;
	if(strcmp(tetenomj(l),nomj)==0)
		return l;
	return rechl(l->suiv,nomj);
}

/*  Nom : supt();
    Finalité : Permettre de supprimer une liste 
    Description Générale : La fonction vérifie que la liste n'est pas vide, puis affecte l'adresse de la liste suivante dans le maillon et libère l'espace mémoire.
*/

Liste supt (Liste l)
{
	Maillon *m;
	if(vide(l))
	{
		puts("Opération interdite");
		exit(1);
	}
	m=l;
	l=l->suiv;
	free(m);
	return l;
}

/*  Nom : suppressionl();
    Finalité : Permettre de rechercher la liste à supprimer
    Description Générale : La fonction recherche récursivement la liste correspondant au nom de jeu passé en argument et appelle supt().
*/

Liste suppressionl (Liste l, char nomj[])
{
	if(vide(l))
		return l;
	if(strcmp(nomj,tetenomj(l))<0)
		return l;
	if (strcmp(nomj,tetenomj(l))==0)
		return supt(l);
	l->suiv=suppressionl(l->suiv,nomj);
	return l;
}

/*  Nom : afficherEmprunt();
    Finalité : Permettre de rechercher les emprunts en cours d'un adhérent.
    Description Générale : La fonction demande à l'utilisateur d'entrer l'adhérent recherché et propose une boucle infini si celui-ci n'existe pas.
    Si elle trouve un utilisateur elle affiche aucun emprunt si aucun emprunt n'est en cours, sinon affiche les emprunts en donnant la date de retour maximale
    ou depuis quand celui-ci est en retard.
*/

void afficherEmprunt (Liste l, Adherent  *tadherent[], int n)
{
	int r=-1,i,choix;
	Liste v;
	DateJour d;
	char nom[30],prenom[30];
	while(r==-1)
	{
		printf("Nom de l'adhérent : ");
		fgets(nom,30,stdin);
		nom[strlen(nom)-1]='\0';
		printf("Prénom de l'adhérent : ");
		fgets(prenom,30,stdin);
		prenom[strlen(prenom)-1]='\0';
		r=rech(tadherent,n,nom,prenom);
		if(r!=-1)
		{
			printf("Emprunts en cours pour %s %s :\n",nom,prenom);
			for(i=0;i<tadherent[r]->nbemprunt;i++)
			{
				v=rechEmprunteur(l,nom,prenom);
				if(vide(v))
				{
					puts("Aucun emprunt en cours");
					return;
				}
				l=v->suiv;
				d=setDayEmp();
				if((d.j_now)>(v->j.dEmprunt.j_exp))
					printf("\t-%s (Délai d'emprunt expiré)\n",v->j.nomj);
				else 
					printf("\t-%s (A rendre dans %d jours !)\n",v->j.nomj,((v->j.dEmprunt.j_exp)-(v->j.dEmprunt.j_now)));
			}
		}
		else
		{
			puts("Adhérent inexistant, tapez 1 pour recommencer, 20 pour retourner au menu");
			scanf("%d%*c", &choix);
			if(choix==20)
				return;
		}
	}
}

/*  Nom : rechEmprunteur();
    Finalité : Permettre de rechercher dans la liste d'emprunt un adhérent.
    Description Générale : La fonction recherche récursivement la liste correspondant au nom de l'adhérent passé en argument pour obtenir le nom du jeu emprunté.
*/

Liste rechEmprunteur (Liste l, char nom[],char prenom[])
{
	if(vide(l))
		return NULL;
	if(strcmp(tetenom(l),nom)==0 && strcmp(teteprenom(l),prenom)==0)
		return l;
	return rechEmprunteur(l->suiv,nom,prenom);
}

/*  Nom : afficherListe();
    Finalité : Permettre d'afficher tous les jeux enregistrés
    Description Générale : La fonction affiche récursivement tous les jeux présent dans la liste. 
*/

void afficherListe (Liste l)
{
	if(vide(l)==Vrai)
		return;
	puts("-----------------------------");
	printf("Jeu : %s\nNom de l'emprunteur : %s\nPrénom de l'emprunteur : %s\nType : %s\n",l->j.nomj,l->j.enom,l->j.eprenom,l->j.type);
	puts("-----------------------------");
	afficherListe(l->suiv);
}

/*  Nom : sauvegarderJeux();
    Finalité : Permettre de sauvegarder dans un fichier .don les jeux en appelant la fonction SaveJeux().
    Description Générale : La fonction ouvre le fichier ou le crée si inexistant, et appelle la fonction SaveJeux().
*/

void sauvegarderJeux(Liste l)
{
	FILE *flot;
	flot=fopen("jeux.don","w");
	if(flot==NULL)
	{
		puts("Problème de sauvegarde du fichier -jeux.don-");
		exit(1);
	}
	SaveJeux(flot,l);
	fclose(flot);
}

/*  Nom : SaveJeux();
    Finalité : Permettre de sauvegarder dans un fichier .don les jeux récursivement.
    Description Générale : La fonction reçoit le flot en argument qui lui permet de sauvegarder un à un les jeux présent dans la liste récursivement.
*/

void SaveJeux(FILE *flot, Liste l)
{
	if(vide(l))
  		return;
 	fprintf(flot,"%d\t%s\n%s\n%s\n%s\n%d\t%d\n",l->j.emprunte,l->j.nomj,l->j.enom,l->j.eprenom,l->j.type,l->j.dEmprunt.j_now,l->j.dEmprunt.j_exp);
 	SaveJeux(flot,l->suiv);
}

/*  Nom : renouvellement();
    Finalité : Permettre de renouveller un abonnement.
    Description Générale : La fonction demande un nom d'adhérent et boucle à l'infini si celui-ci n'existe pas, sinon elle compare la date 
    d'aujourd'hui et la date d'expiration de l'abonnement. Si il est expiré, elle réactualise la variable j_now et la date d'expiration j-exp.
    Si l'abonnement n'est pas encore expiré, elle affiche "Renouvellement d'inscription non-nécessaire".
*/

void renouvellement(Adherent *tadherent[], int n)
{
	int r=-1, choix;
	DateJour d;
	Date da;
	char nom[30],prenom[30];
	d=setDayIns();
	da=setDate();
	while(r==-1)
	{
		printf("Nom de l'adhérent : ");
		fgets(nom,30,stdin);
		nom[strlen(nom)-1]='\0';
		printf("Prénom de l'adhérent : ");
		fgets(prenom,30,stdin);
		prenom[strlen(prenom)-1]='\0';
		r=rech(tadherent,n,nom,prenom);
		if(r==-1)
		{	puts("Adhérent inexistant, tapez 1 pour recommencer, 20 pour retourner au menu");
			scanf("%d%*c", &choix);
			if(choix==20)
				return;
			continue;
		}
		else if(!(d.j_now>tadherent[r]->d.j_exp))
		{
			puts("Renouvellement d'inscription non-nécessaire");
			return;
		}
		else
		{
			tadherent[r]->d=d;
			tadherent[r]->da=da;
		}
	}
}

/*  Nom : rechRetard();
    Finalité : Permettre de rechercher les emprunts en retard. 
    Description Générale : La fonction récupère la date du jour grâce à la fonction setDayEmp(), elle parcourt la liste passée en argument pour comparer la date 
    d'expiration des emprunts et si celui-ci est en retard elle retourne la liste.
*/

Liste rechRetard (Liste l)
{
	DateJour da;
	da=setDayEmp();
	if(vide(l))
		return NULL;
	if((da.j_now)>(l->j.dEmprunt.j_exp) && (l->j.dEmprunt.j_exp)!=0)
		return l;
	return rechRetard(l->suiv);
}

/*  Nom : afficherRetards();
    Finalité : Permettre d'afficher les emprunteurs en retard, l'emprunt en retard et depuis quand. 
    Description Générale : La fonction recherche les emprunts en retard, si la liste est vide, elle affiche "Aucun emprunteur en retard", sinon elle affiche 
    le nom prénom de l'adhérent en retard, le jeu en retard et depuis quand. Pour éviter que la fonction affiche toujours la même chose en boucle, l devient l->suiv 
    et la fonction recommence le processus.
*/

void afficherRetards (Liste l)
{
	DateJour da;
	da=setDayEmp();
	puts("Emprunteurs en retard :");
	l=rechRetard(l);
	if(vide(l))
		puts("Aucun emprunteur en retard");
	while(!(vide(l)))
	{
		printf("%s %s en retard pour rendre %s (%d jours de retard)\n",l->j.enom,l->j.eprenom,l->j.nomj,(da.j_now)-(l->j.dEmprunt.j_exp));
		l=l->suiv;
		l=rechRetard(l);
	}
}

/*  Nom : listeVideGuest();
    Finalité : Permettre de vider une listeGuest 
    Description Générale : La fonction renvoit NULL.
*/

ListeGuest listeVideGuest (void)
{
	return NULL;
}

/*  Nom : chargerAprem();
    Finalité : Permettre de charger en mémoire les après-midi thématiques.
    Description Générale : La fonction ouvre le fichier .don "aprem.don" puis lit une après-midi thématique grâce à lireAprem(). Tant que la fonction feof() n'échoue
    pas à la lecture, elle ajoute l'après-midi au tableau taprem, et réalloue si celui-ci est plein tout en augmentant la taille logique n. Elle retourne la taille 
    logique.
*/

int chargerAprem (ApremGuest *taprem[], int *maxx)
{
	FILE *flot;
	ApremGuest **aux,a;
	int i=0;
 	flot=fopen("aprem.don","r");
 	if(flot==NULL)
  	{
   		puts("Problème ouverture de -aprem.don-");
   		exit(1);
  	}
  	a=lireAprem(flot);
  	while(!feof(flot))
	{
		if(i==(*maxx-1))
		{
			aux=(ApremGuest**)realloc(taprem,5*sizeof(ApremGuest*));
			if(aux==NULL)
			{
				puts("Problème realloc");
				exit(1);
			}
			taprem=aux;
			*maxx+=5;
			free(aux);
		}
		taprem[i]=(ApremGuest*)malloc(sizeof(ApremGuest));
		*taprem[i]=a;
		i++;
		a=lireAprem(flot);
	}
 	fclose(flot);
 	return i;
}

/*  Nom : lireAprem();
    Finalité : Permettre de lire un après-midi thématique.
    Description Générale : La fonction lit un thème, un nb de places, un horaire et le compteur de participants déjà inscrit à cette après-midi. Elle vide la 
    liste ag.g puis autant qu'il y a de participants, lit un nom et un prenom qu'elle insère dans une liste grâce à insertionGuest().
    Enfin elle retourne la structure lue. 
*/

ApremGuest lireAprem (FILE *flot)
{
	ApremGuest ag;
	int cpt,i;
	char nom[30],prenom[30];
 	fgets(ag.a.theme,30,flot);
	ag.a.theme[strlen(ag.a.theme)-1]='\0';
	fscanf(flot,"%d\n",&ag.a.nbP);
	fscanf(flot,"%s\n",ag.a.horaire);
	fscanf(flot,"%d/%d/%d\n",&ag.a.d.j,&ag.a.d.m,&ag.a.d.a);
	fscanf(flot,"%d\n",&cpt);
	ag.g=listeVideGuest();
	for(i=0;i<cpt;i++)
	{	
		fgets(nom,30,flot);
		nom[strlen(nom)-1]='\0';
		fgets(prenom,30,flot);
		prenom[strlen(prenom)-1]='\0';	
		ag.g=insertionGuest(ag.g,nom,prenom);
	}
	return ag;
}

/*  Nom : tetenomGuest();
    Finalité : Permettre retourner le nom d'une liste.
    Description Générale : La fonction renvoit le nom présent dans la liste.
*/

char* tetenomGuest (ListeGuest l)
{
	if(videGuest(l))
	{
		puts("Opération interdite");
		exit(1);
	}
	return l->nom;
}

/*  Nom : insertionGuest();
    Finalité : Permettre d'insérer un nom et un prénom en tête d'un liste 
    Description Générale : La fonction effectue les contrôles nécessaires pour insérer dans l'ordre alphabétique un nom et prénom donnés.
*/

ListeGuest insertionGuest (ListeGuest l, char nom[], char prenom[])
{
	if(videGuest(l))
		return insertionEnTeteGuest(l,nom,prenom);
	if(strcmp(nom,tetenomGuest(l))<0)
		return insertionEnTeteGuest(l,nom,prenom);
	if (strcmp(nom,tetenomGuest(l))==0)
		return l;
	l->suiv=insertionGuest(l->suiv,nom,prenom);
	return l;
}

/*  Nom : insertionEnTeteGuest();
    Finalité : Permettre d'insérer un nom et un prénom en tête d'un liste 
    Description Générale : La fonction insère dans la liste grâce à un maillon le nom et prénom passés en argument et ajuste l'adresse du maillon suivant.
*/

ListeGuest insertionEnTeteGuest (ListeGuest l, char nom[], char prenom[])
{
	MaillonGuest *m;
	m=(MaillonGuest*)malloc(sizeof(MaillonGuest));
	if (m==NULL)
	{
		puts("Problème malloc");
		exit(1);
	}
	strcpy(m->nom,nom);
	strcpy(m->prenom,prenom);
	m->suiv=l;
	return m;
}

/*  Nom : longueur();
    Finalité : Permettre de connaître la longueur d'une liste. 
    Description Générale : Le test d'arrêt renvoit 0 si c'est la fin de la liste, ajoute 1 sinon jusqu'à la fin. 
*/

int longueur (ListeGuest l)
{
	if(videGuest(l))
		return 0;
	return 1+longueur(l->suiv);
}

/*  Nom : ajoutAprem();
    Finalité : Permettre d'ajouter une après-midi thématique
    Description Générale : La fonction demande le thème, le nb de places et l'horaire à l'utilisateur. Si elle existe déjà et que le nombre de places est le même, 
    elle affiche "Après-midi déja existante", en revanche elle met à jour le nombre de places si celui-ci est différent. 
    Sinon elle demande la date voulue et insère dans le tableau taprem les informations données tout en augmentant la taille logique. 
    Si le tableau est plein, elle realloue. 
*/

void ajoutAprem (ApremGuest *taprem[], int *n, int *maxx)
{	
	ApremGuest ag,**aux;
	int res=1,choix,i;
	while(res==1)
	{
		printf("Thème de l'après-midi : ");
		fgets(ag.a.theme,30,stdin);
		ag.a.theme[strlen(ag.a.theme)-1]='\0';
		printf("Nombre de places : ");
		scanf("%d%*c",&ag.a.nbP);
		printf("Horaire de l'après-midi (Ex : '14h30') : ");
		scanf("%s%*c",ag.a.horaire);
		i=rechDico(taprem,*n,ag.a.theme,ag.a.horaire,&res);
		if(res==1)
		{
			if(ag.a.nbP!=taprem[i]->a.nbP)
			{	
				taprem[i]->a.nbP=ag.a.nbP;
				printf("Nombre de places mis à jour pour l'après-midi '%s'\n",ag.a.theme);
				return;
			}
			else
				puts("Après-midi déja existante, tapez 1 pour recommencer, 20 pour retourner au menu");
				scanf("%d%*c", &choix);
				if(choix==20)
					return;
				continue;
		}
	}
	printf("Jour du mois (1-31) : ");
	scanf("%d%*c",&ag.a.d.j);
	printf("Mois de l'année (01-12) : ");
	scanf("%d%*c",&ag.a.d.m);
	printf("Année (2XXX) : ");
	scanf("%d%*c",&ag.a.d.a);
	if(*n==*maxx-1)
	{
		aux=(ApremGuest**)realloc(taprem,5*sizeof(ApremGuest*));
		if(aux==NULL)
		{
			puts("Problème realloc");
			exit(1);
		}
		taprem=aux;
		(*maxx)+=5;
		free(aux);
	}
	taprem[*n]=(ApremGuest*)malloc(sizeof(ApremGuest));
	if(taprem[*n]==NULL)
	{
		puts("Problème malloc");
		exit(1);
	}
	*taprem[*n]=ag;
	taprem[*n]->g=listeVideGuest();
	(*n)++;
}

/*  Nom : controleDate();
    Finalité : Permettre de contrôler les dates d'un après-midi thématique et de le supprimer si expiré.  
    Description Générale : La fonction teste tous les après-midi thématiques du tableau, si la date est expirée, elle le supprime. 
*/

void controleDate (ApremGuest *taprem[], int *n)
{
	int i;
	Date d;
	d=setDate();
	for(i=0;i<*n;i++)
		if ((((taprem[i]->a.d.a)-(d.a))<0) || (((taprem[i]->a.d.a)-(d.a))==0 && ((taprem[i]->a.d.m)-(d.m))<0) || (((taprem[i]->a.d.a)-(d.a))==0 && ((taprem[i]->a.d.m)-(d.m))==0 && ((taprem[i]->a.d.j)-(d.j))<0))
		{	
			decalerAGaucheAprem(i,taprem,n);
			i=0;
		}
}

/*  Nom : supprAprem();
    Finalité : Permettre de supprimer un après-midi thématique. 
    Description Générale : La fonction demande le thème et l'horaire de l'après-midi thématique, renvoit inexistant si elle n'existe pas.
    Puis appelle decalerAGaucheAprem()
*/

void supprAprem (ApremGuest *taprem[], int *n)
{
	char theme[30],horaire[7];
	int res=0,choix,i;
	while(res==0)
	{
		printf("Thème de l'après-midi : ");
		fgets(theme,30,stdin);
		theme[strlen(theme)-1]='\0';
		printf("Horaire de l'après-midi (Ex : '14h30') : ");
		scanf("%s%*c",horaire);
		i=rechDico(taprem,*n,theme,horaire,&res);
		if(res==0)
		{
			puts("Après-midi inexistante ou horaire incorrect, tapez 1 pour recommencer, 20 pour retourner au menu");
			scanf("%d%*c", &choix);
			if(choix==20)
				return;
		}
	}
	decalerAGaucheAprem(i,taprem,n);
}

/*  Nom : decalerAGaucheAprem();
    Finalité : Permettre de supprimer un après-midi par décalage à gauche
    Description Générale : La fonction reçoit en argument le tableau et l'indice de suppression. Elle part de la fin du tableau et 
    copie l'élement suivant dans l'élément précédant.
*/

void decalerAGaucheAprem (int i, ApremGuest *taprem[], int *n)
{
	ApremGuest *aux;
	int j;
	aux=taprem[i];
	for (j=i; j<*n; j++)
		taprem[j]=taprem[j+1];
	(*n)--;
	free(aux);
}

/*  Nom : ajoutGuest();
    Finalité : Permettre d'ajouter/supprimer un participant à un après-midi thématique selon la constante 'int a'.
    Description Générale : La fonction boucle à l'infini tant que l'utilisateur ne rentre pas un après-midi existant ou que celui-ci ne souhaite pas retourner au menu.
    Sinon elle demande le nom et prénom d'adhérent souhaité et vérifie qu'il existe dans le tableau tadherent.
    Si la constante est 1, elle l'ajoute dans le tableau, si elle est égale à 2, elle le supprime. Elle vérifie également que l'inscription de l'adhérent est encore
    valide et propose de renouveller l'inscription si elle ne l'est plus.
	Si la liste de participants est égale au nombre de place, elle affiche que l'après-midi est complète.
*/

void ajoutGuest (ApremGuest *taprem[], Adherent *tadherent[], int n, int a)
{
	int r=-1,choix,res=0,i;
	char nom[30], prenom[30], theme[30], horaire[7];
	DateJour da;
	ListeGuest v;
	da=setDayIns();
	while(r==-1 || res==0)
	{	
		printf("Thème de l'après-midi : ");
		fgets(theme,30,stdin);
		theme[strlen(theme)-1]='\0';
		printf("Horaire de l'après-midi (Ex : '14h30') : ");
		scanf("%s%*c",horaire);
		i=rechDico(taprem,n,theme,horaire,&res);
		if(res==0)
		{
			puts("Après-midi inexistante ou horaire incorrect, tapez 1 pour recommencer, 20 pour retourner au menu");
			scanf("%d%*c", &choix);
			if(choix==20)
				return;
			continue;
		}
		printf("Nom de l'adhérent : ");
		fgets(nom,30,stdin);
		nom[strlen(nom)-1]='\0';
		printf("Prénom de l'adhérent : ");
		fgets(prenom,30,stdin);
		prenom[strlen(prenom)-1]='\0';
		v=rechGuest(taprem[i]->g,nom,prenom);
		if(a==1)	
		{	
			if(!(videGuest(v)))
			{
				puts("Adhérent déjà inscrit à cette après-midi");
				return;
			}
			r=rech(tadherent,n,nom,prenom);
			if(r==-1)
			{
				puts("Adhérent inexistant, tapez 1 pour recommencer, 20 pour retourner au menu");
				scanf("%d%*c", &choix);
				if(choix==20)
					return;
				continue;
			}
			else if((tadherent[r]->d.j_exp)<(da.j_now))
			{
				printf("Renouvellement nécessaire de l'adhérent %s %s, tapez 1 pour recommencer, 2 pour renouveller l'inscription, 20 pour retourner au menu\n",tadherent[r]->nom,tadherent[r]->prenom);
				scanf("%d%*c", &choix);
				if(choix==20)
					return;
				if(choix==2)
				{	
					renouvellement(tadherent,n);
					return;
				}
			}
			else if(longueur(taprem[i]->g)<=taprem[i]->a.nbP)
				taprem[i]->g=insertionGuest(taprem[i]->g,nom,prenom);
			else
				puts("Après-midi thématique complète");
		}
		else
		{
			if(videGuest(v))
			{
				puts("Adhérent non-inscrit à cette après-midi, tapez 1 pour recommencer, 20 pour retourner au menu");
				scanf("%d%*c", &choix);
				if(choix==20)
					return;
				continue;
			}
			r=rech(tadherent,n,nom,prenom);
			if(r==-1)
			{
				puts("Adhérent inexistant, tapez 1 pour recommencer, 20 pour retourner au menu");
				scanf("%d%*c", &choix);
				if(choix==20)
					return;
				continue;
			}
			else
				taprem[i]->g=suppressionGuest(taprem[i]->g,nom,prenom);
		}
	}
}

/*  Nom : rechGuest();
    Finalité : Permettre de rechercher dans une liste un participant. 
    Description Générale : La fonction recherche en récursif la liste contenant le nom et prénom de participant passés en argument. 
*/

ListeGuest rechGuest (ListeGuest l, char nom[], char prenom[])
{
	if(videGuest(l))
		return NULL;
	if((strcmp(l->nom,nom)==0) && (strcmp(l->prenom,prenom)==0))
		return l;
	return rechGuest(l->suiv,nom,prenom);
}

/*  Nom : suptGuest();
    Finalité : Permettre de supprimer une liste de participants.
    Description Générale : La fonction vérifie que la liste n'est pas vide, puis affecte l'adresse de la liste suivante dans le maillon et libère l'espace mémoire.
*/

ListeGuest suptGuest (ListeGuest l)
{
	MaillonGuest *m;
	if(l==NULL)
	{
		puts("Opération interdite");
		exit(1);
	}
	m=l;
	l=l->suiv;
	free(m);
	return l;
}

/*  Nom : suppressionGuest();
    Finalité : Permettre de rechercher la liste à supprimer
    Description Générale : La fonction recherche récursivement la liste correspondant au nom et prénom d'adhérent passés en argument et appelle supt().
*/

ListeGuest suppressionGuest (ListeGuest l, char nom[], char prenom[])
{
	if(videGuest(l))
		return l;
	if(strcmp(nom,l->nom)<0)
		return l;
	if ((strcmp(nom,l->nom)==0) && (strcmp(prenom,l->prenom)==0) )
		return suptGuest(l);
	l->suiv=suppressionGuest(l->suiv,nom,prenom);
	return l;
}

/*  Nom : affichAprem();
    Finalité : Permettre d'afficher un après-midi thématique et ses participants.
    Description Générale : La fonction demande un thème et un horaire, si ceux-ci ne sont pas trouvés, elle affiche une erreur et invite à recommencer ou à retourner 
    au menu. Dans le cas contraire, elle affiche le nom de l'après-midi et ses participants un à un en parcourant la liste. 
*/

void affichAprem (ApremGuest *taprem[], int *n)
{
	int i,res=0,choix;
	char theme[30],horaire[7];
	controleDate(taprem,n);
	while(res==0)
	{	
		printf("Thème de l'après-midi : ");
		fgets(theme,30,stdin);
		theme[strlen(theme)-1]='\0';
		printf("Horaire de l'après-midi : ");
		scanf("%s",horaire);
		i=rechDico(taprem,*n,theme,horaire,&res);
		if(res==1)
		{
			puts("-----------------------------");
			printf("Thème : %s\nNombre de places : %d\nHoraire : %s\nDate : %d/%02d/%d\n",taprem[i]->a.theme,taprem[i]->a.nbP,taprem[i]->a.horaire,taprem[i]->a.d.j,taprem[i]->a.d.m,taprem[i]->a.d.a);
			if(!(videGuest(taprem[i]->g)))
			{	
				puts("Participants :");
				while(!(taprem[i]->g==NULL))
				{
					printf("\t- %s %s\n",taprem[i]->g->nom,taprem[i]->g->prenom);
					taprem[i]->g=taprem[i]->g->suiv;
				}
				puts("-----------------------------");
			}
			else
			{	
				puts("Participants : Aucun");
				puts("-----------------------------");
			}
		}
		else
		{
			puts("Aucune après-midi sur ce thème ou horaire incorrect, tapez 1 pour recommencer, 20 pour retourner au menu");
			scanf("%d%*c", &choix);
			if(choix==20)
				return;
		}
	}
}

/*  Nom : affichAllAprem();
    Finalité : Permettre d'afficher tous les après-midi thématiques à venir.
    Description Générale : La fonction appelle d'abord controleDate() pour ne pas afficher d'après-midi expirés puis elle les affiche un à un en parcourant 
    le tableau.
*/

void affichAllAprem (ApremGuest *taprem[], int *n)
{
	int i;
	controleDate(taprem,n);
	puts("-----------------------------");
	puts("APRÈS-MIDI THÉMATIQUES A VENIR");
	puts("-----------------------------\n");
	printf("\tTHÈME :\t\tPLACES :\tHORAIRE :\tDATE :\n");
	puts("\t------------\t------------\t------------\t------------");
	for(i=0;i<*n;i++)
		printf("\t%s\t\t%d\t\t%s\t\t%d/%02d/%d\n",taprem[i]->a.theme,taprem[i]->a.nbP,taprem[i]->a.horaire,taprem[i]->a.d.j,taprem[i]->a.d.m,taprem[i]->a.d.a);
	puts("\t------------\t------------\t------------\t------------");
}

/*  Nom : rechDico();
    Finalité : Permettre de faire une recherche dicotomique.
    Description Générale : Fonction dicotomique vue en cours et réadapatée. 
*/

int rechDico (ApremGuest *taprem[], int nb, char theme[], char horaire[], int *res)
{
	int inf=0, sup=nb-1, m;
	while(inf<=sup)
	{
		m=(inf+sup)/2;
		if ((strcmp(theme, taprem[m]->a.theme)==0) && (strcmp(horaire, taprem[m]->a.horaire)==0))
		{
			*res=1;
			return m;
		}
		if (strcmp(theme, taprem[m]->a.theme)<0)
			sup=m-1;
		else
			inf=m+1;
		if (strcmp(theme, taprem[m]->a.theme)==0)
		{
			if (strcmp(horaire, taprem[m]->a.horaire)<0)
				sup=m-1;
			else
				inf=m+1;
		}
	}
	*res=0;
	return inf;
}

/*  Nom : triDicoAprem();
    Finalité : Permettre de faire un tri dicotomique.
    Description Générale : Fonction de tri dicotomique vue en cours et réadapatée. 
*/

void triDicoAprem (ApremGuest *taprem[], int n)
{
	ApremGuest **R, **S;
	if(n<=1)
		return;
	R=(ApremGuest**)malloc((n/2)*sizeof(ApremGuest*));
	S=(ApremGuest**)malloc((n-n/2)*sizeof(ApremGuest*));
	if(R==NULL || S==NULL)
	{
		puts("Problème malloc");
		exit(1);
	}
	copierAprem(taprem,0,n/2,R);
	copierAprem(taprem,n/2,n,S);
	triDicoAprem(R,n/2);
	triDicoAprem(S, n-n/2);
	fusionAprem(R,n/2,S,n-n/2,taprem);
	free(R);
	free(S);
}

/*  Nom : copierAprem();
    Finalité : Permettre de copier un tableau dans un autre pour le tri dicotomique.
    Description Générale : Fonction de copie pour le tri dicotomique vue en cours et réadapatée. 
*/

void copierAprem (ApremGuest *t[], int i, int j, ApremGuest *R[])
{
	int k=0;
	while(i<j)
	{
		R[k]=t[i];
		i++;
		k++;
	}
}

/*  Nom : fusionAprem();
    Finalité : Permettre de fusionner deux tableau pour le tri dicotomique.
    Description Générale : Fonction de fusion pour le tri dicotomique vue en cours et réadapatée. 
*/

void fusionAprem (ApremGuest *R[], int n, ApremGuest *S[], int m, ApremGuest *T[])
{
	int i=0,j=0,k=0;
	while(i<n && j<m)
	{
		if(strcmp(R[i]->a.theme, S[j]->a.theme) <= 0)
		{
			T[k]=R[i];
			i++;
		}
		else
		{
			T[k]=S[j];
			j++;
		}
	k++;
	}
	while(i<n)
	{
		T[k]=R[i];
		i++;
		k++;
	}
	while(j<m)
	{
		T[k]=S[j];
		j++;
		k++;
	}
}

/*  Nom : sauvegarderAprem();
    Finalité : Permettre de sauvegarder le tableau taprem.
    Description Générale : La fonction ouvre ou crée un fichier aprem.don où elle sauvegarde tous les après-midi thématiques, puis fprint la longueur de la liste 
    chaînée et sauvegarde chaque adhérent jusqu'à la fin de la liste.  
*/

void sauvegarderAprem (ApremGuest *taprem[], int n)
{
	FILE *flot;
	int i,lg;
	flot=fopen("aprem.don","w");
	if(flot==NULL)
	{
		puts("PB sauvegarde du fichier -aprem.don-");
		exit(1);
	}
	for(i=0;i<n;i++)
	{
		fprintf(flot,"%s\n%d\n%s\n%d/%d/%d\n",taprem[i]->a.theme,taprem[i]->a.nbP,taprem[i]->a.horaire,taprem[i]->a.d.j,taprem[i]->a.d.m,taprem[i]->a.d.a);
		lg=longueur(taprem[i]->g);
		fprintf(flot,"%d\n",lg);
		while(!(taprem[i]->g==NULL))
		{
			fprintf(flot,"%s\n%s\n",taprem[i]->g->nom,taprem[i]->g->prenom);
			taprem[i]->g=taprem[i]->g->suiv;
		}
	}
	fclose(flot);
}