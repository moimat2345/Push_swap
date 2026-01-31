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

### Vue d'ensemble de la stratégie de tri

Le programme utilise **deux stratégies différentes** selon la taille de l'entrée :

| Taille | Algorithme | Pourquoi |
|:------:|:-----------|:---------|
| 2-5 éléments | Mouvements optimaux codés en dur | Minimum d'opérations, pas de surcharge |
| >5 éléments | **Double Tri Radix** | Efficace pour les grands ensembles, utilise les deux piles simultanément |

---

<details open>
<summary><b>🔹 Double Tri Radix (pour >5 éléments)</b></summary>

Contrairement à un tri radix classique qui repousse simplement tout de B vers A après chaque passe de bit, cette implémentation utilise une approche **double radix** : **les deux piles sont activement triées en même temps** sur des positions de bits différentes.

#### Étape 1 — Normalisation par indices

Avant le tri, toutes les valeurs sont converties en indices commençant à 0 pour que le radix fonctionne sur une plage propre :

```c
// Entrée :  [42, -5, 100, 0, 7]
// Indices : [ 3,  0,   4, 1, 2]
```

L'algorithme trouve répétitivement la valeur minimum et lui assigne l'indice suivant.

#### Étape 2 — Calcul du nombre de bits

L'algorithme détermine combien de bits sont nécessaires pour représenter le plus grand indice :

```c
// 5 éléments → indices 0..4 → max = 4 → binaire 100 → 3 bits nécessaires
int bit_size = get_max_bits(size_a - 1);
```

#### Étape 3 — Double Radix : Trier A et B simultanément

Pour chaque position de bit (du bit 0 = LSB vers le haut) :

**Phase A** — Partitionner la pile A selon le bit courant :
```
Pour chaque élément au sommet de A :
  ┌─ bit est 0 → pb  (envoyer vers B)
  └─ bit est 1 → ra  (garder dans A, rotation vers le bas)
```

**Phase B** — Trier immédiatement la pile B sur le bit **suivant** (bit + 1) :
```
Pour chaque élément au sommet de B :
  ┌─ bit est 0 → rb  (garder dans B, rotation vers le bas)
  └─ bit est 1 → pa  (repousser vers A)
```

C'est la différence clé : au lieu de repousser aveuglément tout de B vers A, `radix_sort_b` trie activement B en utilisant le bit suivant, renvoyant les éléments vers A uniquement quand leur bit suivant est `1`.

#### Étape 4 — Optimisation de sortie anticipée

À chaque étape, l'algorithme vérifie `is_sorted()`. Si A est déjà trié et B est vide, il s'arrête immédiatement — évitant des opérations inutiles.

#### Exemple visuel

```
Indices en entrée : [2, 0, 3, 1]  →  binaire : [10, 00, 11, 01]

═══ Bit 0 (LSB) — Tri de A ═══
  2 (10) → bit=0 → pb     B: [2]        A: [0, 3, 1]
  0 (00) → bit=0 → pb     B: [0, 2]     A: [3, 1]
  3 (11) → bit=1 → ra     B: [0, 2]     A: [1, 3]
  1 (01) → bit=1 → ra     B: [0, 2]     A: [1, 3]  (déjà rotaté)

═══ Bit 1 — Tri de B (pendant que A garde son ordre) ═══
  0 (00) → bit=0 → rb     B: [2, 0]     A: [1, 3]
  2 (10) → bit=1 → pa     B: [0]        A: [2, 1, 3]

═══ Bit 1 — Tri de A ═══
  ... continue jusqu'à ce que ce soit trié

═══ Final : repousser le reste de B vers A ═══
```

#### Complexité

**O(n * k)** où k = nombre de bits nécessaires (log2(n)).
Le double radix réduit le nombre total d'opérations par rapport à un radix simple car B est trié pendant qu'il est vidé, au lieu d'être repoussé aveuglément.

</details>

---

<details>
<summary><b>🔹 Tri des Petites Piles (2-5 éléments)</b></summary>

Pour les petites entrées, l'algorithme utilise des **solutions optimales codées en dur** qui garantissent le minimum d'opérations :

#### 2 éléments
```
Simplement échanger (sa) si pas dans l'ordre.
```

#### 3 éléments — Arbre de décision
Les 6 permutations sont gérées avec au maximum 2 opérations :

```
[2,1,3] → sa
[3,2,1] → sa + rra
[3,1,2] → ra
[1,3,2] → sa + ra
[2,3,1] → rra
[1,2,3] → (déjà trié)
```

#### 4 éléments
1. Trouver la position de l'élément minimum
2. Le faire remonter au sommet de A (`ra` jusqu'à ce que le min soit en haut)
3. Le pousser vers B (`pb`)
4. Trier les 3 éléments restants (réutilise `sort_three`)
5. Le repousser (`pa`)

#### 5 éléments
Même logique que 4 éléments, mais avec une optimisation intelligente :
- Si le minimum est dans la **moitié haute** (position 0-2) → utiliser `ra` pour le remonter
- Si le minimum est dans la **moitié basse** (position 3-4) → utiliser `rra` (plus rapide, moins de mouvements)

Puis pousser vers B, trier les 4 restants (qui appelle le tri de 3 en interne), et repousser.

</details>

---

<details>
<summary><b>🔹 Normalisation par Indices</b></summary>

Avant le tri, les valeurs sont converties en indices pour une plage normalisée :

```c
// Entrée :  [42, -5, 100, 0, 7]
// Indices : [3,   0,   4, 1, 2]
```

L'algorithme trouve répétitivement la valeur minimum, lui assigne l'indice suivant (0, 1, 2...), et la marque comme `INT_MAX` pour qu'elle ne soit plus sélectionnée. Cela garantit que le tri radix fonctionne sur une plage propre de 0 à n-1 quelle que soit les valeurs originales.

</details>

---

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
| **Algorithme** | Double Tri Radix |
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
