# projetSNSensi

## 📄 Description  
`projetSNSensi` est un projet écrit en langage C dont l’objectif est de gérer un petit système de type réseau social.  
Le programme permet de charger des relations depuis un fichier texte, de manipuler des utilisateurs, et d’enregistrer certaines informations dans un fichier binaire pour assurer la persistance des données.

Ce projet sert de base pour comprendre :  
- la gestion de fichiers texte et binaires en C ;  
- les structures chaînées / relations entre éléments ;  
- une interface console simple pour manipuler les données.

---

## 📁 Contenu du dépôt  
```
main.c             — Code source principal du programme  
main.exe           — Exécutable compilé (Windows)  
relations.txt      — Fichier texte contenant les relations initiales  
utilisateur.bin    — Fichier binaire avec les données utilisateurs  
README.md          — Documentation du projet  
```

---

## ✅ Fonctionnalités  
- Lecture des relations depuis `relations.txt`.  
- Création et gestion de structures représentant les utilisateurs.  
- Enregistrement et lecture des données utilisateurs dans un fichier binaire (`utilisateur.bin`).  
- Interface console simple pour interagir avec les données chargées.  

---

## 🚀 Compilation et exécution

### 🔧 Prérequis  
- Un compilateur C (GCC recommandé).  
- Un terminal/PowerShell/Invite de commande.

### 💻 Compilation  
```bash
gcc main.c -o projetSNSensi
```

### ▶️ Exécution  
```bash
./projetSNSensi      # Linux / macOS
```
ou  
```bash
main.exe             # Windows
```

## 📂 Description des fichiers  

### **relations.txt**  
Contient les relations initiales à charger.  
Format : une relation par ligne.

### **utilisateur.bin**  
Fichier binaire servant à sauvegarder les informations persistantes sur les utilisateurs.

### **main.c**  
Contient l’ensemble de la logique :  
- lecture des fichiers ;  
- création/gestion de structures ;  
- interactions avec l’utilisateur ;  
- manipulation des relations.

---

## 👤 Auteur  
Projet développé par **Wajih Haggui,Mohammed Haythem Sebai,Youssef Ghorbel**.
