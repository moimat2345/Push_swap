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

### Sorting Strategy Overview

The program uses **two different strategies** depending on the input size:

| Input size | Algorithm | Why |
|:----------:|:----------|:----|
| 2-5 elements | Hardcoded optimal moves | Minimal operations, no overhead |
| >5 elements | **Double Radix Sort** | Efficient for larger sets, uses both stacks simultaneously |

---

<details open>
<summary><b>🔹 Double Radix Sort (for >5 elements)</b></summary>

Unlike a classic radix sort that simply pushes everything back from B to A after each bit pass, this implementation uses a **double radix** approach: **both stacks are actively sorted at the same time** on different bit positions.

#### Step 1 — Index Normalization

Before sorting, all values are converted to 0-based indices so the radix sort works on a clean range:

```c
// Input:   [42, -5, 100, 0, 7]
// Indices: [ 3,  0,   4, 1, 2]
```

This is done by repeatedly finding the minimum value and assigning it the next index.

#### Step 2 — Calculate the number of bits

The algorithm determines how many bits are needed to represent the largest index:

```c
// 5 elements → indices 0..4 → max = 4 → binary 100 → 3 bits needed
int bit_size = get_max_bits(size_a - 1);
```

#### Step 3 — Double Radix: Sort A and B simultaneously

For each bit position (from bit 0 = LSB upward):

**Phase A** — Partition stack A based on the current bit:
```
For each element at the top of A:
  ┌─ bit is 0 → pb  (push to B)
  └─ bit is 1 → ra  (keep in A, rotate to bottom)
```

**Phase B** — Immediately sort stack B on the **next** bit (bit + 1):
```
For each element at the top of B:
  ┌─ bit is 0 → rb  (keep in B, rotate to bottom)
  └─ bit is 1 → pa  (push back to A)
```

This is the key difference: instead of blindly pushing everything from B back to A, `radix_sort_b` actively sorts B using the next bit, sending elements back to A only when their next bit is `1`.

#### Step 4 — Early exit optimization

At every step, the algorithm checks `is_sorted()`. If A is already sorted and B is empty, it stops immediately — avoiding unnecessary operations.

#### Visual Example

```
Input indices: [2, 0, 3, 1]  →  binary: [10, 00, 11, 01]

═══ Bit 0 (LSB) — Sort A ═══
  2 (10) → bit=0 → pb     B: [2]        A: [0, 3, 1]
  0 (00) → bit=0 → pb     B: [0, 2]     A: [3, 1]
  3 (11) → bit=1 → ra     B: [0, 2]     A: [1, 3]
  1 (01) → bit=1 → ra     B: [0, 2]     A: [1, 3]  (already rotated)

═══ Bit 1 — Sort B (while A keeps its order) ═══
  0 (00) → bit=0 → rb     B: [2, 0]     A: [1, 3]
  2 (10) → bit=1 → pa     B: [0]        A: [2, 1, 3]

═══ Bit 1 — Sort A ═══
  ... continues until sorted

═══ Final: push remaining B to A ═══
```

#### Complexity

**O(n * k)** where k = number of bits needed (log2(n)).
The double radix reduces the total number of operations compared to a standard single-pass radix because B is sorted while being emptied, rather than being dumped back blindly.

</details>

---

<details>
<summary><b>🔹 Small Stack Sorting (2-5 elements)</b></summary>

For small inputs, the algorithm uses **hardcoded optimal solutions** that guarantee the minimum number of operations:

#### 2 elements
```
Simply swap (sa) if not in order.
```

#### 3 elements — Decision tree
All 6 permutations are handled with at most 2 operations:

```
[2,1,3] → sa
[3,2,1] → sa + rra
[3,1,2] → ra
[1,3,2] → sa + ra
[2,3,1] → rra
[1,2,3] → (already sorted)
```

#### 4 elements
1. Find the minimum element's position
2. Rotate it to the top of A (`ra` until min is on top)
3. Push it to B (`pb`)
4. Sort the remaining 3 elements (reuses `sort_three`)
5. Push it back (`pa`)

#### 5 elements
Same logic as 4 elements, but with a smart optimization:
- If the minimum is in the **top half** (position 0-2) → use `ra` to bring it up
- If the minimum is in the **bottom half** (position 3-4) → use `rra` (faster, fewer moves)

Then push to B, sort the remaining 4 (which calls sort 3 inside), and push back.

</details>

---

<details>
<summary><b>🔹 Index Normalization</b></summary>

Before sorting, values are converted to indices for a normalized range:

```c
// Input:  [42, -5, 100, 0, 7]
// Indices: [3,  0,   4, 1, 2]
```

The algorithm repeatedly finds the minimum value, assigns it the next index (0, 1, 2...), and marks it as `INT_MAX` so it won't be picked again. This ensures the radix sort works on a clean 0 to n-1 range regardless of the original values.

</details>

---

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
| **Algorithm** | Double Radix Sort |
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
