#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>

typedef struct Utilisateur Utilisateur;
typedef struct relation relation;
typedef struct noeudtimeline noeudtimeline;
typedef struct filetimeline filetimeline;
typedef struct publication publication;

struct publication{
  char texte[1000];
  int temps;
  char auteur[100];
  publication* next;
};

struct noeudtimeline {
    char texte[1000];
    char auteur[20];
    noeudtimeline* next;
};

struct filetimeline {
    noeudtimeline* tete;
    noeudtimeline* queue;
};

struct Utilisateur{
    int ID;
    char Nom[20];
    char motdepasse[10];
    filetimeline timeline;
    publication* publications;
    relation* ami;
    relation* abonnement;
    Utilisateur *left;
    Utilisateur *right;
};

struct relation{
  Utilisateur* personne;
  relation* next;
};

int inputID(char* msg) {
    char ID[9]; 
    int i = 0;
    char ch;
    printf("%s",msg);
    while (1) {
        ch = getch();
        if (ch == '\r') {
            if (i == 0) {
                printf("\nEntrez au moins un chiffre.\n");
                printf("%s",msg);
                continue;
            }
            break;
        }
        if (ch == '\b') {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
            continue;
        }
        if (!isdigit((unsigned char)ch)) {
            continue;
        }
        if (i >= 8) {
            continue;
        }
        ID[i++] = ch;
        printf("%c", ch);
    }
    ID[i] = '\0';
    printf("\n");
    return atoi(ID);
}

void inputNom(char *Nom, int maxlong) {
    int i = 0;
    char ch;
    printf("Enter votre nom d'utilisateur (max %d chars): ", maxlong - 1);
    while (1) {
        ch = getch();
        if (ch == '\r') {
            break;
        }
        if (ch == '\b') {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
            continue;
        }
        if (i >= maxlong - 1) {
            continue;
        }
        Nom[i++] = ch;
        printf("%c", ch);
    }
    Nom[i] = '\0';
    printf("\n");
}

void inputPass(char *pass, int maxlong) {
    int i = 0;
    char c;
    while ((c = getch()) != '\r' && i < maxlong - 1) {
        if (c == '\b' && i > 0) {
            printf("\b \b");
            i--;
        }
        else if (c != '\b') {
            pass[i++] = c;
            printf("*");
        }
    }
    pass[i] = '\0';
    printf("\n");
}

Utilisateur* recherche(Utilisateur *racine, int ID) {
    if (racine == NULL)
        return NULL;

    if (ID == racine->ID)
        return racine;

    if (ID < racine->ID)
        return recherche(racine->left, ID);
    else
        return recherche(racine->right, ID);
}

Utilisateur* creerUtilisateur(Utilisateur* racine){
    Utilisateur* node = (Utilisateur*)malloc(sizeof(Utilisateur));
    int ID;
    do{
        ID=inputID("Entrez un ID:");
        if (recherche(racine,ID)==NULL) break;
        printf("ID déjà existant. Veuillez réessayer.\n");
    }while(1);
    char Nom[20];
    inputNom(Nom,20);
    strcpy(node->Nom, Nom);
    char pass1[15], pass2[15];
    do {
        printf("Entrez un mot de passe : ");
        inputPass(pass1, 15);
        if (strlen(pass1) < 8) {
            printf("Le mot de passe doit contenir au moins 8 caractères.\n");
            continue;
        }
        printf("Confirmez le mot de passe : ");
        inputPass(pass2, 15);
        if (strcmp(pass1, pass2) != 0) {
            printf("Les mots de passe ne correspondent pas. Réessayez.\n");
        }
    } while (strcmp(pass1, pass2) != 0);
    strcpy(node->motdepasse, pass1);
    node->publications = NULL;
    node->ami = NULL;
    node->abonnement = NULL;
    node->ID = ID;
    node->left = node->right = NULL;
    node->timeline.tete = node->timeline.queue = NULL;
    printf("Compte créé avec succès !\n");
    return node;
}
Utilisateur* insert(Utilisateur* racine, Utilisateur* x) {
    if (racine == NULL)
        return x;
    if (x->ID < racine->ID)
        racine->left = insert(racine->left, x);
    else if (x->ID > racine->ID)
        racine->right = insert(racine->right, x);
    return racine;
}

Utilisateur* trouverMin(Utilisateur* racine) {
    while (racine->left != NULL) racine = racine->left;
    return racine;
}

Utilisateur* supprimer(Utilisateur* racine, int ID) {
    if (racine == NULL) return NULL;

    if (ID < racine->ID)
        racine->left = supprimer(racine->left, ID);
    else if (ID > racine->ID)
        racine->right = supprimer(racine->right, ID);
    else {
        if (racine->left == NULL) {
            Utilisateur* temp = racine->right;
            free(racine);
            return temp;
        } else if (racine->right == NULL) {
            Utilisateur* temp = racine->left;
            free(racine);
            return temp;
        } else {
            Utilisateur* temp = trouverMin(racine->right);
            racine->ID = temp->ID;
            strcpy(racine->Nom, temp->Nom);
            racine->right = supprimer(racine->right, temp->ID);
        }
    }
    return racine;
}

bool estabonne(Utilisateur* x, Utilisateur* y){
    relation* abonnement=x->abonnement;
    while (abonnement != NULL){
        if (abonnement->personne==y){
            return true;
        }
        abonnement=abonnement->next;
    }
    return false;
}

bool estami(Utilisateur* x,Utilisateur* y){
    relation* ami=x->ami;
    while (ami != NULL){
        if (ami->personne==y){
            return true;
        }
        ami=ami->next;
    }
    return false;
}

void suppami(Utilisateur* x,Utilisateur* y){
    if (!x || !y || x->ami == NULL) return;
    relation* temp = x->ami;
    relation* prev = NULL;
    while (temp) {
        if (temp->personne == y) {
            if (prev == NULL) x->ami = temp->next;
            else prev->next = temp->next;
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void ajoutabonnement(Utilisateur* x,Utilisateur* y){
    relation* abonnement=x->abonnement;
    relation* nouveauabonnement=malloc(sizeof(relation));
    nouveauabonnement->next=abonnement;
    nouveauabonnement->personne=y;
    x->abonnement=nouveauabonnement;
    return;
}

void desabonner(Utilisateur* x, Utilisateur* y){
    relation* abx=x->abonnement;
    bool succes=false;
    if (abx->personne==y){
        x->abonnement=abx->next;
        free(abx);
        succes=true;
    }else{
        while (abx->next!=NULL){
            if (abx->next->personne==y){
                relation* temp=abx->next;
                abx->next=temp->next;
                free(temp);
                succes=true;
                break;
            }
            abx=abx->next;
        }
    }
    if (succes){
        if(estami(x,y)){
            suppami(x,y);
            suppami(y,x);
        }
        printf("Vous vous êtes désabonné(e) de %s.\n",y->Nom);
    }else printf("Aucun abonnement trouvé pour %s.\n",y->Nom);
    return;
}

void ajoutami(Utilisateur* x,Utilisateur* y){
    relation* amix=x->ami;
    relation* amiy=y->ami;
    relation* Nouveauamix= malloc(sizeof(relation));
    relation* Nouveauamiy= malloc(sizeof(relation));
    Nouveauamix->personne=y;
    Nouveauamiy->personne=x;
    Nouveauamix->next=amix;
    Nouveauamiy->next=amiy;
    x->ami=Nouveauamix;
    y->ami=Nouveauamiy;
    return;
}

void abonner(Utilisateur* racine,Utilisateur* x,int ID){
  Utilisateur* y=recherche(racine,ID);
  if (y==NULL){
    printf("ID non existant\n");
    printf("ID invalide. Veuillez saisir à nouveau l'ID (ou 0 pour quitter) : ");
    scanf("%d",&ID);
    if (ID!=0) abonner(racine,x,ID);
    else return;
  }
  if (estabonne(x,y)) printf("Tu es déjà abonné(e) à %s\n", y->Nom);
  else if (estabonne(y,x)){
    ajoutami(x,y);
    ajoutabonnement(x,y);
    printf("Vous êtes maintenant ami avec %s!\n",y->Nom);
  }
  else{
    ajoutabonnement(x,y);
    printf("Vous êtes maintenant abonné(e) avec %s!\n",y->Nom);
  }
  return;
}

publication* creerpub(char* contenu, char* auteur){
    publication* pub = malloc(sizeof(publication));
    strcpy(pub->texte, contenu);
    strcpy(pub->auteur, auteur);
    pub->temps = time(NULL);
    pub->next = NULL;
    return pub;
}

void inputPub(char *pub, int maxlong) {
    int i = 0;
    char ch;
    int entrenbre = 0;
    printf("Entrez votre publication: \n");
    while (1) {
        ch = getch();
        if (ch == '\r') {
            entrenbre++;
            if (entrenbre == 2) break;
            if (i < maxlong - 1) {
                pub[i++] = '\n';
                printf("\n");
            } else {
                printf("\a");
            }
            continue;
        } else {
            entrenbre = 0;
        }
        if (ch == '\b') {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
            continue;
        }
        if (i >= maxlong - 1) {
            continue;
        }
        pub[i++] = ch;
        printf("%c", ch);
    }
    pub[i] = '\0';
    printf("\nVotre publication a été publiée !\n");
}

void ajoutpub(Utilisateur* x){
    char contenu[1000];
    inputPub(contenu,1000);
    publication* pub = creerpub(contenu, x->Nom);
    pub->next = x->publications;
    x->publications = pub;
}

void viderTimeline(Utilisateur *x) {
    if (x == NULL) return;
    if (x->timeline.tete == NULL) return;
    noeudtimeline *temp = x->timeline.tete;
    noeudtimeline *next;
    while (temp != NULL) {
        next = temp->next;
        free(temp);
        temp = next;
    }
    x->timeline.tete = x->timeline.queue = NULL;
}

void ajoutTimeline(Utilisateur* x,publication* p){
    noeudtimeline* n=malloc(sizeof(noeudtimeline));
    strncpy(n->texte, p->texte, sizeof(n->texte)-1);
    n->texte[sizeof(n->texte)-1] = '\0';
    strncpy(n->auteur, p->auteur, sizeof(n->auteur)-1);
    n->auteur[sizeof(n->auteur)-1] = '\0';
    n->next = NULL;
    if (x->timeline.queue == NULL) {
        x->timeline.tete = x->timeline.queue = n;
    } else {
        x->timeline.queue->next = n;
        x->timeline.queue = n;
    }
}

int comparerPub(const void *a, const void *b) {
    publication *pa = *(publication**)a;
    publication *pb = *(publication**)b;
    return pb->temps - pa->temps;
}

void actualiserTimeline(Utilisateur *x) {
    if (x->timeline.tete!=NULL) viderTimeline(x);
    int nbre=0;
    relation *rel=x->abonnement;
    publication* p;
    while (rel) {
        p=rel->personne->publications;
        while (p) { 
            nbre++; 
            p=p->next; 
        }
        rel=rel->next;
    }
    if (nbre==0) return;
    publication **pubarray = malloc(nbre * sizeof(publication*));
    int i=0;
    rel=x->abonnement;
    while (rel) {
        p=rel->personne->publications;
        while (p){ 
            pubarray[i++]=p; 
            p=p->next;
        }
        rel=rel->next;
    }
    qsort(pubarray, nbre, sizeof(publication*), comparerPub);
    int limit=(nbre < 100) ? nbre : 100;
    for (int i=0;i<limit;i++){
        ajoutTimeline(x,pubarray[i]);
    }
    free(pubarray);
}

void afficherTimeline(filetimeline t){
    if (t.tete==NULL){
        printf("Aucune publication à afficher.\n");
        return;
    }
    printf("\n----- Timeline -----\n");
    noeudtimeline* temp=t.tete;
    while (temp) {
        printf("Auteur : %s\n", temp->auteur);
        printf("%s\n", temp->texte);
        printf("------------------------------\n");
        temp = temp->next;
    }
}

void afficherPub(publication* p){
    if (p==NULL){
        printf("Aucune publication à afficher.\n");
        return;
    }
    printf("\n----- Vos publications -----\n");
    publication* temp=p;
    int i=1;
    while(temp){
        printf("%d. %s\n",i,temp->texte);
        i++;
        temp=temp->next;
    }
}

void afficherAmi(relation* ami){
    if (ami==NULL){
        printf("Vous n'avez aucun ami :(\n");
        return;
    }
    printf("\n----- Vos amis -----\n");
    relation* temp=ami;
    int i=1;
    while(temp){
        printf("%d. %s (ID: %d)\n",i,temp->personne->Nom,temp->personne->ID);
        i++;
        temp=temp->next;
    }
}

void afficherAbonnements(Utilisateur* x) {
    if (x->abonnement == NULL) {
        printf("Vous n'avez aucun abonnement.\n");
        return;
    }
    printf("\n----- Vos abonnements -----\n");
    relation* temp = x->abonnement;
    int i = 1;
    while (temp) {
        printf("%d. %s (ID: %d)\n", i, temp->personne->Nom, temp->personne->ID);
        temp = temp->next;
        i++;
    }
}

Utilisateur* connection(Utilisateur* racine){
    Utilisateur* x = NULL;
    do{
        int ID=inputID("Entrez un ID : ");
        x=recherche(racine,ID);
        if (x!=NULL){
            break;
        }
        printf("ID non trouvé. Veuillez réessayer.\n");
    }while (1);
    char pass[15];
    do{
        printf("Mot de passe : ");
        inputPass(pass,15);
        if(strcmp(x->motdepasse,pass) == 0){
            break;
        }
        printf("Mot de passe incorrect, veuillez réessayer.\n");
    }while (1);
    return x;
}

void abonnerMenu(Utilisateur* x, Utilisateur* racine) {
    int ID=inputID("Entrez l'ID de l'utilisateur à abonner (ou 0 pour annuler) : ");
    if (ID == 0) return;
    Utilisateur* y = recherche(racine, ID);
    if (y == NULL) {
        printf("ID non existant. Veuillez réessayer.\n");
        return;
    }
    if (x == y) {
        printf("Vous ne pouvez pas vous abonner à vous-même.\n");
        return;
    }
    abonner(racine, x, ID);
}

void desabonnerMenu(Utilisateur* x) {
    if (x->abonnement==NULL && x->ami==NULL) {
        printf("Vous n'avez aucun abonnement.\n");
        return;
    }
    printf("----- Vos abonnements -----\n");
    relation* temp=x->abonnement;
    int i=1;
    while (temp) {
        printf("%d. %s (ID: %d)\n", i, temp->personne->Nom, temp->personne->ID);
        temp=temp->next;
        i++;
    }

    int ID=inputID("Entrez l'ID de l'utilisateur à désabonner (ou 0 pour annuler) : ");
    if (ID==0) return;
    temp=x->abonnement;
    while (temp) {
        if (temp->personne->ID==ID) {
            desabonner(x, temp->personne);
            return;
        }
        temp = temp->next;
    }
    printf("Aucun abonnement trouvé avec cet ID.\n");
}

void attendreRetour(void) {
    printf("Appuyez sur Entrée pour continuer...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar(); // wait
}

void menuUtilisateur(Utilisateur* x,Utilisateur* racine) {
    int choix;
    do {
        printf("\n----- Menu Utilisateur: %s -----\n", x->Nom);
        printf("1. Afficher vos publications\n");
        printf("2. Ajouter une publication\n");
        printf("3. Afficher vos amis\n");
        printf("4. Afficher vos abonnements\n");
        printf("5. Abonner à un utilisateur\n");
        printf("6. Désabonner d'un utilisateur\n");
        printf("7. Afficher votre timeline\n");
        printf("0. Déconnexion\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch(choix) {
            case 1:
                afficherPub(x->publications);
                attendreRetour();
                break;
            case 2:
                ajoutpub(x);
                attendreRetour();
                break;
            case 3:
                afficherAmi(x->ami);
                attendreRetour();
                break;
            case 4:
                afficherAbonnements(x);
                attendreRetour();
                break;
            case 5:
                abonnerMenu(x,racine);
                attendreRetour();
                break;
            case 6:
                desabonnerMenu(x);
                attendreRetour();
                break;
            case 7:
                actualiserTimeline(x);
                afficherTimeline(x->timeline);
                attendreRetour();
                break;
            case 0:
                printf("Déconnexion réussie.\n");
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    } while (choix != 0);
}

int countPub(publication* p){
    int res=0;
    while (p){
        res++;
        p=p->next;
    }
    return res;
}

void sauvegarderUtilisateur(FILE* f, Utilisateur* racine) {
    if (!racine) return;
    fwrite(&racine->ID,sizeof(int),1,f);
    fwrite(racine->Nom,sizeof(char),20,f);
    fwrite(racine->motdepasse,sizeof(char),10,f);
    int nbrepub=countPub(racine->publications);
    fwrite(&nbrepub,sizeof(int),1,f);
    publication* p=racine->publications;
    while (p){
        fwrite(p->texte,sizeof(char),1000,f);
        fwrite(&p->temps,sizeof(int),1,f);
        p=p->next;
    }
    sauvegarderUtilisateur(f, racine->left);
    sauvegarderUtilisateur(f, racine->right);
}

void sauvegarderRelation(FILE* f,Utilisateur* racine){
    if (!racine) return;
    relation *r=racine->ami;
    while (r) {
        fprintf(f,"%d %d 1\n",racine->ID,r->personne->ID);
        r=r->next;
    }
    r=racine->abonnement;
    while (r) {
        fprintf(f,"%d %d 2\n",racine->ID,r->personne->ID);
        r=r->next;
    }
    sauvegarderRelation(f,racine->left);
    sauvegarderRelation(f,racine->right);
}

void chargerRelations(Utilisateur *racine) {
    FILE *f = fopen("relations.txt", "r");
    if (!f) return;
    int id1, id2, type;
    while (fscanf(f, "%d %d %d", &id1, &id2, &type) == 3) {
        Utilisateur *p1=recherche(racine, id1);
        Utilisateur *p2=recherche(racine, id2);
        if (!p1 || !p2) continue;
        if (type==1) {
            ajoutami(p1, p2);
        } else if (type == 2) {
            ajoutabonnement(p1, p2);
        }
    }
    fclose(f);
}

Utilisateur* chargerUtilisateurs() {
    FILE *f=fopen("utilisateur.bin","rb");
    Utilisateur* racine=NULL;
    while (1) {
        Utilisateur temp;
        if (fread(&temp.ID, sizeof(int), 1, f)!=1)
            break;
        fread(temp.Nom, sizeof(char),20,f);
        temp.Nom[19]='\0';
        fread(temp.motdepasse,sizeof(char),10,f);
        temp.motdepasse[9]='\0';
        int nbrepub=0;
        fread(&nbrepub,sizeof(int),1,f);
        temp.publications=NULL;
        publication* dernier=NULL;
        for (int i=0; i<nbrepub;i++) {
            publication* p=malloc(sizeof(publication));
            fread(p->texte,sizeof(char),1000,f);
            p->texte[999]='\0';
            fread(&p->temps,sizeof(int),1,f);
            p->next=NULL;
            strcpy(p->auteur,temp.Nom);
            if (temp.publications==NULL) {
                temp.publications=dernier=p;
            } else {
                dernier->next = p;
                dernier=p;
            }
        }
        Utilisateur* nouv = malloc(sizeof(Utilisateur));
        *nouv = temp;
        nouv->left = NULL;
        nouv->right = NULL;
        nouv->abonnement = NULL;
        nouv->ami = NULL;
        nouv->timeline.tete = NULL;
        nouv->timeline.queue = NULL;
        racine = insert(racine, nouv);
    }
    fclose(f);
    return racine;
}

void libererPublications(publication* p) {
    while (p) {
        publication* tmp = p;
        p = p->next;
        free(tmp);
    }
}

void libererRelations(relation* r) {
    while (r) {
        relation* tmp = r;
        r = r->next;
        free(tmp);
    }
}

void libererABR(Utilisateur* root) {
    if (!root) return;
    libererABR(root->left);
    libererABR(root->right);
    viderTimeline(root);
    libererPublications(root->publications);
    libererRelations(root->ami);
    libererRelations(root->abonnement);
    free(root);
}

int main()
{
    Utilisateur* racine=chargerUtilisateurs();
    int choix ;
    do {
        printf("\n----- Menu Principale -----\n");
        printf("1. Se connecter \n");
        printf("2. S'inscrire \n");
        printf("0. Quitter \n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);
        switch (choix){
            case 1:{
                Utilisateur* x=connection(racine);
                menuUtilisateur(x,racine);
                attendreRetour();
                break;
            }
            case 2 :{
                Utilisateur* u=creerUtilisateur(racine);
                racine=insert(racine,u);
                attendreRetour();
                break;
            }
            case 0:{
                printf("Deconnexion...");
                FILE* f=fopen("utilisateur.bin","wb");
                sauvegarderUtilisateur(f,racine);
                fclose(f);
                f=fopen("relations.txt","w");
                sauvegarderRelation(f,racine);
                fclose(f);
                break;
            }
            default:{
                printf("Choix invalide, veuillez réessayer.\n");
                break;
            }
        }
    }while(choix !=0);
    libererABR(racine);
}