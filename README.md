<div align="center">
  <img src="https://raw.githubusercontent.com/ayogun/42-project-badges/main/covers/cover-push_swap.png" alt="push_swap" />
</div>

# push_swap - Sorting Algorithm with Two Stacks

The `push_swap` project challenges you to sort a stack of integers using a limited set of operations and **two stacks**. The goal is to find the most efficient sequence of moves. This project is an excellent introduction to **algorithmic complexity** and **sorting strategies**.

## Status
<div align="center">

![42 Bangkok](https://img.shields.io/badge/42-Bangkok-000000?style=for-the-badge&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=for-the-badge)

<br>

### 🌍 Language / Langue

[![Français](https://img.shields.io/badge/🇫🇷_Lire_en_Français-blue?style=for-the-badge&logoColor=white)](README.fr.md)

</div>

---

## Overview

The goal is to sort a list of integers on **stack A** using a set of predefined operations, with the help of an auxiliary **stack B**. The program must output the shortest possible sequence of operations. This exercise deepens understanding of sorting algorithms, data structures, and optimization.

## Useful Resources

- [Notion's Oceano - push_swap](https://suspectedoceano.notion.site/push-swap-c1fc4b3dfe8844aa8b5e84a12c1f4e04)
- [Push_swap Tester Francinette](https://github.com/xicodomingues/francinette)
- [Push_swap Visualizer](https://github.com/o-reo/push_swap_visualizer)

---

## 📋 Mandatory Part

<table>
  <tr>
    <th>Program name</th>
    <td>push_swap</td>
  </tr>
  <tr>
    <th>Turn in files</th>
    <td>Makefile, *.h, *.c</td>
  </tr>
  <tr>
    <th>Makefile</th>
    <td>Yes</td>
  </tr>
  <tr>
    <th>External functs.</th>
    <td>read, write, malloc, free, exit, ft_printf</td>
  </tr>
  <tr>
    <th>Libft authorized</th>
    <td>Yes</td>
  </tr>
  <tr>
    <th>Description</th>
    <td>Sort integers using two stacks and a limited set of operations.</td>
  </tr>
</table>

### Important Rules
- Global variables are forbidden.
- Subfunctions should be defined as `static`.
- All .c files must compile with the flags `-Wall -Wextra -Werror`.
- The program receives integers as arguments and must print the sorting instructions on stdout.

---

## 📂 Project Structure

```
Push_swap/
├── 📄 Makefile                  # Compilation → push_swap
├── 📄 include/
│   ├── push_swap.h              # Header (prototypes + includes)
│   └── 📁 my_lib/              # Custom libft library
│       ├── Makefile
│       ├── include/libft.h
│       └── src/                 # 60+ utility files
│
└── 📁 src/                     # Main source files (9 files)
    ├── main.c                   # Entry point + orchestration
    ├── stack_init.c             # Stack initialization + index conversion
    ├── input_validation.c       # Argument parsing + validation
    ├── input_special.c          # Special input handling
    ├── sort_small.c             # Sorting for 2-5 elements
    ├── sort_radix.c             # Radix sort for larger sets
    ├── operations_stack_a.c     # sa, ra, rra, pa
    ├── operations_stack_b.c     # rb, pb
    └── utils.c                  # Helpers (free, is_sorted)
```

---

## 🎯 Available Operations

The program uses two stacks (**A** and **B**) and the following operations:

<details open>
<summary><b>Click to see operations</b></summary>

| Operation | Description | Example |
|:---------:|:------------|:--------|
| **sa** | Swap the first 2 elements of stack A | `[3,1,2]` → `[1,3,2]` |
| **pa** | Push top of B onto A | A gets B's top element |
| **pb** | Push top of A onto B | B gets A's top element |
| **ra** | Rotate A up (first becomes last) | `[1,2,3]` → `[2,3,1]` |
| **rb** | Rotate B up (first becomes last) | `[1,2,3]` → `[2,3,1]` |
| **rra** | Reverse rotate A (last becomes first) | `[1,2,3]` → `[3,1,2]` |

</details>

---

## 🛠️ Compilation and Usage

### Compile the Program

```bash
# Compile
make

# Clean object files
make clean

# Clean everything
make fclean

# Recompile completely
make re
```

### Run push_swap

```bash
# With separate arguments
./push_swap 4 67 3 87 23

# With a quoted string
./push_swap "4 67 3 87 23"

# Check number of operations
./push_swap 4 67 3 87 23 | wc -l

# Combine with checker (if available)
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker $ARG
```

---

## 💡 Implementation Highlights

<details>
<summary><b>🔹 Radix Sort (for >5 elements)</b></summary>

For larger inputs, the algorithm uses a **binary radix sort** based on bit manipulation:

1. Convert all values to their sorted indices (0 to n-1)
2. For each bit position (LSB to MSB):
   - If the bit is `0` → push to stack B (`pb`)
   - If the bit is `1` → rotate stack A (`ra`)
3. Push everything back from B to A
4. Repeat for the next bit

```c
// Simplified radix sort logic
for each bit position:
    for each element in A:
        if (element >> bit) & 1 == 0
            pb();   // bit is 0 → send to B
        else
            ra();   // bit is 1 → keep in A
    push all B back to A
```

**Complexity**: O(n * k) where k = number of bits needed.

</details>

<details>
<summary><b>🔹 Small Stack Optimization (2-5 elements)</b></summary>

For small inputs, hardcoded optimal solutions are used:

```
2 elements → 1 operation max (sa)
3 elements → 2 operations max (decision tree)
4 elements → push min to B, sort 3, push back
5 elements → push min to B, sort 4 recursively
```

</details>

<details>
<summary><b>🔹 Index Normalization</b></summary>

Before sorting, values are converted to indices for a normalized range:

```c
// Input:  [42, -5, 100, 0, 7]
// Indices: [3,  0,   4, 1, 2]
```

This simplifies the radix sort since we only work with values 0 to n-1.

</details>

<details>
<summary><b>🔹 Input Validation</b></summary>

The program validates all inputs rigorously:
- Integer overflow detection (using `long long`)
- Duplicate checking
- Format validation (digits and signs only)
- Range validation (INT_MIN to INT_MAX)

</details>

---

## ⚠️ Limitations

This implementation **does not include**:

- ❌ Bonus `checker` program
- ❌ Combined operations (`ss`, `rr`, `rrr`)
- ❌ `sb` and `rrb` operations

---

## 📊 Statistics

<div align="center">

| Metric | Value |
|:------:|:-----:|
| **Source files** | 9 .c |
| **Lines (project)** | ~745 |
| **Lines (with libft)** | ~2,838 |
| **Operations** | 6 |
| **Algorithm** | Radix Sort |
| **Bonus** | No |

</div>

---

## 🚨 Disclaimer

**🇬🇧 This project has an educational purpose and you should under no circumstances copy and paste.**
**Cheat is bad. Don't cheat.**

**🇫🇷 Ce projet a un but éducatif et vous ne devez en aucun cas faire du copier-coller.**
**Tricher c'est mal. Ne trichez pas.**

---

<div align="center">

**Made with ❤️ for 42 Bangkok**

[![Back to top](https://img.shields.io/badge/⬆-Back_to_top-red?style=for-the-badge)](#push_swap---sorting-algorithm-with-two-stacks)

</div>
