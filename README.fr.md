<div align="center">
  <img src="https://raw.githubusercontent.com/ayogun/42-project-badges/main/covers/cover-push_swap.png" alt="push_swap" />
</div>

# push_swap - Algorithme de Tri avec Deux Piles

Le projet `push_swap` consiste à trier une pile d'entiers en utilisant un ensemble limité d'opérations et **deux piles**. L'objectif est de trouver la séquence de mouvements la plus efficace. Ce projet est une excellente introduction à la **complexité algorithmique** et aux **stratégies de tri**.

## Statut
<div align="center">

![42 Bangkok](https://img.shields.io/badge/42-Bangkok-000000?style=for-the-badge&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=for-the-badge)

<br>

### 🌍 Language / Langue

[![English](https://img.shields.io/badge/🇬🇧_Read_in_English-red?style=for-the-badge&logoColor=white)](README.md)

</div>

---

## Vue d'ensemble

L'objectif est de trier une liste d'entiers sur la **pile A** en utilisant un ensemble d'opérations prédéfinies, avec l'aide d'une **pile B** auxiliaire. Le programme doit afficher la séquence d'opérations la plus courte possible. Cet exercice approfondit la compréhension des algorithmes de tri, des structures de données et de l'optimisation.

## Ressources utiles

- [Notion's Oceano - push_swap](https://suspectedoceano.notion.site/push-swap-c1fc4b3dfe8844aa8b5e84a12c1f4e04)
- [Push_swap Tester Francinette](https://github.com/xicodomingues/francinette)
- [Push_swap Visualizer](https://github.com/o-reo/push_swap_visualizer)

---

## 📋 Partie Obligatoire

<table>
  <tr>
    <th>Nom du programme</th>
    <td>push_swap</td>
  </tr>
  <tr>
    <th>Fichiers à rendre</th>
    <td>Makefile, *.h, *.c</td>
  </tr>
  <tr>
    <th>Makefile</th>
    <td>Oui</td>
  </tr>
  <tr>
    <th>Fonctions externes</th>
    <td>read, write, malloc, free, exit, ft_printf</td>
  </tr>
  <tr>
    <th>Libft autorisée</th>
    <td>Oui</td>
  </tr>
  <tr>
    <th>Description</th>
    <td>Trier des entiers en utilisant deux piles et un ensemble limité d'opérations.</td>
  </tr>
</table>

### Règles importantes
- Les variables globales sont interdites.
- Les sous-fonctions doivent être définies comme `static`.
- Tous les fichiers .c doivent compiler avec les flags `-Wall -Wextra -Werror`.
- Le programme reçoit des entiers en arguments et doit afficher les instructions de tri sur stdout.

---

## 📂 Structure du Projet

```
Push_swap/
├── 📄 Makefile                  # Compilation → push_swap
├── 📄 include/
│   ├── push_swap.h              # Header (prototypes + includes)
│   └── 📁 my_lib/              # Bibliothèque libft personnalisée
│       ├── Makefile
│       ├── include/libft.h
│       └── src/                 # 60+ fichiers utilitaires
│
└── 📁 src/                     # Fichiers sources principaux (9 fichiers)
    ├── main.c                   # Point d'entrée + orchestration
    ├── stack_init.c             # Initialisation des piles + conversion d'indices
    ├── input_validation.c       # Parsing + validation des arguments
    ├── input_special.c          # Gestion des entrées spéciales
    ├── sort_small.c             # Tri pour 2-5 éléments
    ├── sort_radix.c             # Tri radix pour les grands ensembles
    ├── operations_stack_a.c     # sa, ra, rra, pa
    ├── operations_stack_b.c     # rb, pb
    └── utils.c                  # Utilitaires (free, is_sorted)
```

---

## 🎯 Opérations Disponibles

Le programme utilise deux piles (**A** et **B**) et les opérations suivantes :

<details open>
<summary><b>Cliquez pour voir les opérations</b></summary>

| Opération | Description | Exemple |
|:---------:|:------------|:--------|
| **sa** | Échange les 2 premiers éléments de la pile A | `[3,1,2]` → `[1,3,2]` |
| **pa** | Pousse le sommet de B sur A | A reçoit le sommet de B |
| **pb** | Pousse le sommet de A sur B | B reçoit le sommet de A |
| **ra** | Rotation de A vers le haut (le premier devient dernier) | `[1,2,3]` → `[2,3,1]` |
| **rb** | Rotation de B vers le haut (le premier devient dernier) | `[1,2,3]` → `[2,3,1]` |
| **rra** | Rotation inverse de A (le dernier devient premier) | `[1,2,3]` → `[3,1,2]` |

</details>

---

## 🛠️ Compilation et Utilisation

### Compiler le programme

```bash
# Compiler
make

# Nettoyer les fichiers objets
make clean

# Tout nettoyer
make fclean

# Recompiler complètement
make re
```

### Exécuter push_swap

```bash
# Avec des arguments séparés
./push_swap 4 67 3 87 23

# Avec une chaîne entre guillemets
./push_swap "4 67 3 87 23"

# Vérifier le nombre d'opérations
./push_swap 4 67 3 87 23 | wc -l

# Combiner avec checker (si disponible)
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker $ARG
```

---

## 💡 Points Clés de l'Implémentation

<details>
<summary><b>🔹 Tri Radix (pour >5 éléments)</b></summary>

Pour les entrées plus grandes, l'algorithme utilise un **tri radix binaire** basé sur la manipulation de bits :

1. Convertir toutes les valeurs en indices triés (0 à n-1)
2. Pour chaque position de bit (LSB vers MSB) :
   - Si le bit est `0` → pousser vers la pile B (`pb`)
   - Si le bit est `1` → rotation de la pile A (`ra`)
3. Repousser tout de B vers A
4. Répéter pour le bit suivant

```c
// Logique simplifiée du tri radix
pour chaque position de bit:
    pour chaque élément dans A:
        si (element >> bit) & 1 == 0
            pb();   // bit est 0 → envoyer vers B
        sinon
            ra();   // bit est 1 → garder dans A
    repousser tout B vers A
```

**Complexité** : O(n * k) où k = nombre de bits nécessaires.

</details>

<details>
<summary><b>🔹 Optimisation Petites Piles (2-5 éléments)</b></summary>

Pour les petites entrées, des solutions optimales codées en dur sont utilisées :

```
2 éléments → 1 opération max (sa)
3 éléments → 2 opérations max (arbre de décision)
4 éléments → pousser le min vers B, trier 3, repousser
5 éléments → pousser le min vers B, trier 4 récursivement
```

</details>

<details>
<summary><b>🔹 Normalisation par Indices</b></summary>

Avant le tri, les valeurs sont converties en indices pour une plage normalisée :

```c
// Entrée :  [42, -5, 100, 0, 7]
// Indices : [3,   0,   4, 1, 2]
```

Cela simplifie le tri radix car on travaille uniquement avec des valeurs de 0 à n-1.

</details>

<details>
<summary><b>🔹 Validation des Entrées</b></summary>

Le programme valide rigoureusement toutes les entrées :
- Détection de dépassement d'entier (via `long long`)
- Vérification des doublons
- Validation du format (chiffres et signes uniquement)
- Validation de la plage (INT_MIN à INT_MAX)

</details>

---

## ⚠️ Limitations

Cette implémentation **n'inclut pas** :

- ❌ Programme bonus `checker`
- ❌ Opérations combinées (`ss`, `rr`, `rrr`)
- ❌ Opérations `sb` et `rrb`

---

## 📊 Statistiques

<div align="center">

| Métrique | Valeur |
|:--------:|:------:|
| **Fichiers sources** | 9 .c |
| **Lignes (projet)** | ~745 |
| **Lignes (avec libft)** | ~2 838 |
| **Opérations** | 6 |
| **Algorithme** | Tri Radix |
| **Bonus** | Non |

</div>

---

## 🚨 Avertissement

**🇫🇷 Ce projet a un but éducatif et vous ne devez en aucun cas faire du copier-coller.**
**Tricher c'est mal. Ne trichez pas.**

**🇬🇧 This project has an educational purpose and you should under no circumstances copy and paste.**
**Cheat is bad. Don't cheat.**

---

<div align="center">

**Made with ❤️ for 42 Bangkok**

[![Retour en haut](https://img.shields.io/badge/⬆-Retour_en_haut-blue?style=for-the-badge)](#push_swap---algorithme-de-tri-avec-deux-piles)

</div>
