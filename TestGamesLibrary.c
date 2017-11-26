#include "GamesLibrary.h"

int main (void) 
{
	int n=0, max=10, choix,i=0,maxx=10,nbAprem;
	Adherent **adherent;
	ApremGuest **aprem;
	Liste j;
	j=listeVide();
	adherent=(Adherent**)malloc(10*sizeof(Adherent*));
	if(adherent==NULL)
	{
		puts("Problème malloc **adherent");
		exit(1);
	}
	aprem=(ApremGuest**)malloc(10*sizeof(ApremGuest*));
	if(aprem==NULL)
	{
		puts("Problème malloc **aprem");
		exit(1);
	}
	chargerAdherent(adherent, &n,&max);
	triDico(adherent,n);
	j=chargerJeux(j);
	nbAprem=chargerAprem(aprem,&maxx);
	controleDate(aprem,&nbAprem);
	triDicoAprem(aprem,nbAprem);
	puts("-----------------------------");
	puts("\tMENU LUDOTÈQUE\t");
	puts("-----------------------------");
	printf("ADHÉRENTS\n\t1) Enregistrer un adhérent\n\t2) Afficher les adhérents\n\t3) Afficher un adhérent\n\t4) Supprimer un adhérent\n\t5) Renouveller une inscription\nEMPRUNTS\n\t6) Ajouter un emprunt\n\t7) Supprimer un emprunt\n\t8) Consulter la liste des jeux\n\t9) Ajouter un jeu\n\t10) Consulter les emprunts d'un adhérent\n\t11) Consulter les retards d'emprunts\nAPRÈS-MIDI\n\t12) Ajouter un après-midi thématique\n\t13) Supprimer un après-midi thématique\n\t14) Ajouter un participant à un après-midi thématique\n\t15) Supprimer un participant à un après-midi thématique\n\t16) Consulter les participants d'un après-midi thématique\n\t17) Consulter tous les après-midis à venir\nAUTRES\n\t20) Quitter en sauvegardant\n");
	puts("-----------------------------");
	scanf("%d%*c", &choix);
	while(choix!=20)
	{
		if(choix<0 || choix>20)
			puts("Choix incorrect, recommencez.");
		switch(choix)
		{
			case 1 : enregistrerAdherent(adherent,&n,&max);triDico(adherent,n);break;
			case 2 : afficher(adherent,n);break;
			case 3 : afficherAdherent(adherent,n);break;
			case 4 : suppression(adherent,&n);break;
			case 5 : renouvellement(adherent,n);break;
			case 6 : j=ajoutEmprunt(j,adherent,n,1);break;
			case 7 : j=ajoutEmprunt(j,adherent,n,2);break;
			case 8 : afficherListe(j);break;
			case 9 : j=ajouterJeu(j);break;
			case 10 : afficherEmprunt(j,adherent,n);break;
			case 11: afficherRetards(j);break;
			case 12: ajoutAprem(aprem,&nbAprem,&maxx);triDicoAprem(aprem,nbAprem);break;
			case 13: supprAprem(aprem,&nbAprem);break;
			case 14: ajoutGuest(aprem,adherent,n,1);break;
			case 15: ajoutGuest(aprem,adherent,n,2);break;
			case 16: affichAprem(aprem,&nbAprem);break;
			case 17: affichAllAprem(aprem,&nbAprem);break;
		}
		printf("\n-----------------------------\n");
		printf("ADHÉRENTS\n\t1) Enregistrer un adhérent\n\t2) Afficher les adhérents\n\t3) Afficher un adhérent\n\t4) Supprimer un adhérent\n\t5) Renouveller une inscription\nEMPRUNTS\n\t6) Ajouter un emprunt\n\t7) Supprimer un emprunt\n\t8) Consulter la liste des jeux\n\t9) Ajouter un jeu\n\t10) Consulter les emprunts d'un adhérent\n\t11) Consulter les retards d'emprunts\nAPRÈS-MIDI\n\t12) Ajouter un après-midi thématique\n\t13) Supprimer un après-midi thématique\n\t14) Ajouter un participant à un après-midi thématique\n\t15) Supprimer un participant à un après-midi thématique\n\t16) Consulter les participants d'un après-midi thématique\n\t17) Consulter tous les après-midis à venir\nAUTRES\n\t20) Quitter en sauvegardant\n");
		puts("-----------------------------");
		scanf("%d%*c", &choix);
	}
	sauvegarderAdherent(adherent,n);
	sauvegarderJeux(j);
	sauvegarderAprem(aprem,nbAprem);
	return 0;
}