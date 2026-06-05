*This project has been created as part of the 42 curriculum by ksadayas.*

## Description

push_swap is a sorting algorithm project from the 42 curriculum.

The objective is to sort a stack of unique integers using only a limited set of operations and two stacks (`a` and `b`).

The program must output the sequence of operations required to sort the numbers in ascending order while using as few operations as possible.

---

## Rules

At the beginning:

- Stack `a` contains all integers.
- Stack `b` is empty.
- The first argument is the top of stack `a`.

Goal:

- Sort stack `a` in ascending order.
- Leave stack `b` empty.

---

## Available Operations

| Operation | Description |
|------------|------------|
| sa | swap first two elements of stack a |
| sb | swap first two elements of stack b |
| ss | sa and sb simultaneously |
| pa | push top element of b to a |
| pb | push top element of a to b |
| ra | rotate a |
| rb | rotate b |
| rr | ra and rb simultaneously |
| rra | reverse rotate a |
| rrb | reverse rotate b |
| rrr | rra and rrb simultaneously |

---

## Data Structure

The stacks are implemented using a doubly linked list.

```c
typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_stack
{
	t_node	*head;
	t_node	*tail;
	int		size;
}	t_stack;
```

### value

Stores the original integer.

### index

Stores the compressed rank used by radix sort.

Example:

```text
Original:
42 -3 100 7

Sorted:
-3 7 42 100

Indexes:
2 0 3 1
```

---

## Algorithm

This implementation uses **Binary Radix Sort**.

### Step 1: Index Compression

Input:

```text
42 -3 100 7
```

Sorted:

```text
-3 7 42 100
```

Indexes:

```text
2 0 3 1
```

The algorithm sorts indexes instead of original values.

---

### Step 2: Binary Processing

For each bit:

```text
if bit == 0
	pb
else
	ra
```

After all numbers are processed:

```text
pa until stack b is empty
```

Repeat for every bit.

---

## Compilation

Compile:

```bash
make
```

Recompile:

```bash
make re
```

Remove object files:

```bash
make clean
```

Remove everything:

```bash
make fclean
```

---

## Usage

```bash
./push_swap 2 1 3
```

Output:

```text
sa
```

Example:

```bash
./push_swap 3 2 1
```

Output:

```text
sa
rra
```

---

## Error Handling

The program prints:

```text
Error
```

to stderr when:

- duplicate numbers exist
- non-numeric arguments exist
- integer overflow occurs
- empty arguments are given

Examples:

```bash
./push_swap 1 2 a
```

```text
Error
```

```bash
./push_swap 1 2 2
```

```text
Error
```

```bash
./push_swap 2147483648
```

```text
Error
```

---

# Testing

## Checker Test

```bash
ARG="4 67 3 87 23"

./push_swap $ARG | ./checker_linux $ARG
```

Expected:

```text
OK
```

---

## Count Operations

```bash
ARG="4 67 3 87 23"

./push_swap $ARG | wc -l
```

Example:

```text
6
```

---

# Random Tests

## 100 Numbers

Generate:

```bash
ARG="$(shuf -i 1-10000 -n 100 | tr '\n' ' ')"
```

Count operations:

```bash
./push_swap $ARG | wc -l
```

Check correctness:

```bash
./push_swap $ARG | ./checker_linux $ARG
```

Both at once:

```bash
./push_swap $ARG | tee ops.txt | ./checker_linux $ARG

wc -l ops.txt
```

---

## 500 Numbers

Generate:

```bash
ARG="$(shuf -i 1-100000 -n 500 | tr '\n' ' ')"
```

Count:

```bash
./push_swap $ARG | wc -l
```

Check:

```bash
./push_swap $ARG | ./checker_linux $ARG
```

---

# Multiple Automated Tests

## 100 Random Tests

```bash
for i in {1..100}
do
	ARG="$(shuf -i 1-10000 -n 100 | tr '\n' ' ')"
	./push_swap $ARG | ./checker_linux $ARG
done
```

Expected:

```text
OK
OK
OK
...
```

---

## Average Operation Count

```bash
for i in {1..100}
do
	ARG="$(shuf -i 1-10000 -n 100 | tr '\n' ' ')"
	./push_swap $ARG | wc -l
done | awk '{sum += $1} END {print sum / NR}'
```

---

# Benchmarks

According to the subject:

| Input Size | Target |
|------------|---------|
| 100 numbers | < 700 operations |
| 500 numbers | < 5500 operations |

Typical radix-sort results:

| Input Size | Operations |
|------------|------------|
| 100 | ~1000-1100 |
| 500 | ~6500-7000 |

---

# Useful Debug Commands

Display generated numbers:

```bash
echo "$ARG"
```

Save operations:

```bash
./push_swap $ARG > ops.txt
```

Count operations:

```bash
wc -l ops.txt
```

Replay operations:

```bash
./checker_linux $ARG < ops.txt
```

---

# Project Structure

```text
.
├── Makefile
├── push_swap.h
├── main.c
├── parse_args.c
├── ft_split.c
├── stack_utils.c
├── stack_free.c
├── swap.c
├── push.c
├── rotate.c
├── reverse_rotate.c
├── sort_three.c
├── radix_sort.c
├── index.c
└── utils.c
```

---

# Norm Compliance

This project follows the 42 Norm.

Rules respected:

- No global variables
- Functions <= 25 lines
- Maximum 5 functions per file
- Memory properly freed
- No forbidden functions
- No relinking in Makefile

---

# AI Usage

AI was used for:

- understanding the subject
- discussing radix sort
- checking edge cases
- generating test commands

All code was reviewed, tested, and understood before use.

---

# Resources

- 42 Push Swap Subject
- Radix Sort Documentation
- Linked List Documentation
- Stack Data Structure
- Big-O Complexity Analysis
