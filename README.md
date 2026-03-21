# 🔐 Password Manager (C++)

> ⚠️ Projet en cours de développement
---

## 📌 Fonctionnalités

- 🔑 Authentification utilisateur (login)
- 👤 Gestion de comptes utilisateurs
- 📁 Stockage des données par utilisateur
- 🗂️ Organisation des fichiers en JSON
- 🔐 Base pour chiffrement / hash des mots de passe (à venir)
- 🖥️ Interface en ligne de commande CLI (provisoire)

---

## ⚙️ Compilation

### avec `Make`
```bash
make
```

Vous pouvez trouver le build dans le dossier **build**
execution
```bash
./build/main
```


Optionelle:

### Avec `g++` :

```bash
g++ main.cpp src/*.cpp -o main
```

Execution :

```bash
./main
```

Compilation + execution :

```bash
g++ main.cpp src/*.cpp -o main && ./main
```
