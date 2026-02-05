# Code Together 4: Copy and Move Constructors

This activity explores **copy constructors** and **move constructors** in C++. You'll implement both for a class that manages a heap-allocated resource (`Bio*`), understanding when each is called and why.

## Learning Objectives

- Understand why classes with raw pointers need custom copy/move constructors
- Implement a **deep copy** in a copy constructor
- Implement efficient **ownership transfer** in a move constructor
- Recognize the difference between copy and move semantics
- Preview: Assignment operators are deleted here; we'll cover `std::unique_ptr` next

## The Scenario

We have two classes:
- **`NameTag`**: Simple class with stack-only members (`int`, `std::string`). The compiler-generated copy/move work correctly.
- **`FancyNameTag`**: Has a raw pointer (`Bio*`) to heap memory. We must write custom copy/move constructors to handle it correctly.

## What You'll Implement

In `FancyNameTag.cpp`, complete these functions:

1. **Destructor** (`~FancyNameTag`) - Free the heap-allocated `Bio`
2. **Copy Constructor** - Allocate NEW heap memory and copy the `Bio` data (deep copy)
3. **Move Constructor** - Transfer ownership of the `Bio` pointer (no allocation needed)

## Key Concepts

### Deep Copy vs Shallow Copy
- **Shallow copy**: Copies the pointer value → both objects point to the SAME heap memory (DANGEROUS!)
- **Deep copy**: Allocates NEW heap memory and copies the data → each object owns its own copy (SAFE)

### Move Semantics
- Move "steals" the resource instead of copying it
- Much faster when you don't need the original anymore
- The source object is left in a "valid but unspecified" state

### Why Delete Assignment Operators?
We've deleted the copy and move assignment operators (`= delete`) to keep this example focused on constructors. In real code, you'd either:
1. Implement them (full Rule of Five), or
2. Use `std::unique_ptr<Bio>` which handles everything automatically — we'll cover that next!

## Grading (40 points)

| Category | Points |
|----------|--------|
| Build Check | 2 |
| Bio Struct | 4 |
| NameTag Constructor | 4 |
| NameTag Copy Constructor | 4 |
| FancyNameTag Constructor | 4 |
| FancyNameTag Destructor | 2 |
| FancyNameTag Copy Constructor | 6 |
| FancyNameTag Move Constructor | 8 |
| Copy Independence | 2 |
| Setter Validation | 4 |

## Building and Running

```bash
# Configure
cmake -B build -S .

# Build
cmake --build build

# Run the demo
./build/main

# Run the tests
./build/tests
```

## Files to Modify

- `src/FancyNameTag.cpp` - Implement the destructor, copy constructor, and move constructor

## Files to Review (DO NOT MODIFY)

- `include/Bio.h` - Simple struct with no pointers (default copy/move work fine)
- `include/NameTag.h` - Class with stack-only members (default copy/move work fine)
- `include/FancyNameTag.h` - Class declaration showing what you need to implement
- `src/main.cpp` - Demo showing copy/move behavior
- `tests/copy_move_test.cpp` - Tests that verify your implementations
