  # ProjetSNSensi — Réseau social simple en C

  ## Description

  ProjetSNSensi est un mini-réseau social écrit en C.  
  Il permet de :
  - créer des comptes utilisateurs (ID, nom, mot de passe),
  - publier du texte,
  - gérer des relations : amis et abonnements,
  - afficher une timeline triée par date,
  - sauvegarder et charger toutes les données.

  Ce projet illustre :
  - les arbres binaires de recherche (ABR),
  - les listes chaînées,
  - la gestion mémoire,
  - les fichiers binaires et texte,
  - la création d’une interface console.

  ---

  ## Structure du projet
/
│ main.c – code source principal
│ utilisateur.bin – sauvegarde binaire des utilisateurs et publications
│ relations.txt – sauvegarde texte des relations

---

## Prérequis

- gcc / clang / MSVC  
- Standard C  
- Windows si utilisation de getch()

---

## Compilation

### Sous Linux / MinGW
gcc main.c -o ProjetSNSensi  
./ProjetSNSensi

### Sous Windows
gcc main.c -o ProjetSNSensi.exe  
ProjetSNSensi.exe

---

## Fonctionnalités

- Création de compte  
- Connexion (ID + mot de passe)  
- Publications  
- Gestion des amis et des abonnements  
- Timeline triée (amis + abonnements)  
- Sauvegarde à la fermeture  
- Chargement automatique au démarrage  

---

## Sauvegarde des données

- utilisateur.bin : sauvegarde binaire (ID, nom, mot de passe, publications)
- relations.txt : sauvegarde texte au format :
  ```
  id_source id_cible type
  ```
  type = 1 (ami), 2 (abonnement)

---

## Auteur

Wajih Haggui  Youssef Ghorbel  Mohammed Haythem Sebai

---

