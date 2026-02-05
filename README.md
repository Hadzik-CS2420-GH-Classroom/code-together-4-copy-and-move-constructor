# Code Together 4 — Copy and Move Constructors

## Overview

In this activity we will build two classes — `NameTag` and `FancyNameTag` — to explore how C++ handles **copying** and **moving** objects. Along the way we will see why the compiler-generated defaults work for stack-only classes but break when a class owns heap memory.

We will also introduce **structs**, compare them to classes, and practice **constructor validation** (invariants).

> **Note:** We focus on constructors in this activity. Assignment operators are deleted to keep things simple. In modern C++, you'd use `std::unique_ptr<Bio>` instead of `Bio*` and get correct behavior automatically — we'll cover that in the next Code Together.

## What You Will Practice

- Understanding the difference between **copy constructor** and **move constructor**
- Using `std::move` and rvalue references (`&&`) to transfer ownership
- Implementing a **destructor**, **copy constructor**, and **move constructor** for a heap-owning class
- Recognizing when a **deep copy** is required vs. when the default (shallow) copy works
- Using `struct` for simple data holders vs. `class` for encapsulated types
- Validating invariants in constructors and setters
- Observing **stack vs. heap** memory addresses in output

## Project Structure

```
├── CMakeLists.txt              # Build configuration (C++20)
├── include/
│   ├── AddrUtil.h              # Inline helper — shortened memory addresses
│   ├── Bio.h                   # Struct declaration (plain data holder)
│   ├── FancyNameTag.h          # Class declaration — owns a heap Bio*
│   └── NameTag.h               # Class declaration — stack-only members (default copy/move)
├── src/
│   ├── Bio.cpp                 # Bio print() implementation
│   ├── FancyNameTag.cpp        # Destructor, copy constructor, move constructor
│   ├── NameTag.cpp             # Constructor, print, getters/setters
│   └── main.cpp                # Demo driver — follow the TODOs
├── images/                     # Reference diagrams (PNG)
│   ├── default_copy_constructor.png
│   ├── default_move.png
│   ├── fancy_copy_constructor.png
│   └── shallow_copy_danger.png
└── tests/
    └── copy_move_test.cpp      # Google Test autograding tests
```

## Instructions

1. Clone this repository and open it in your IDE.
2. Look through the source files — each `// TODO:` comment tells you exactly what to write.
3. Start with the **headers** (`include/`) — read the declarations and comments to understand the API.
4. Move to the **source files** (`src/`) — implement each constructor and method.
5. Finish with `src/main.cpp` — follow the TODOs to create objects, copy them, move them, and observe the output.
6. Use the **PNG diagrams** in `images/` as visual references (they are also referenced in `main.cpp` comments).
7. Build and run to verify your output.
8. Push your changes — the autograder will run automatically and score your work out of **40 points**.


## Grading Breakdown (40 points)

| Category | Points |
|---|---|
| Build Check | 2 |
| Bio Struct (members + print) | 4 |
| NameTag Constructor (id, name) | 4 |
| NameTag Default Copy Constructor (id, name) | 4 |
| FancyNameTag Constructor (id, company) | 4 |
| FancyNameTag Destructor (no crash) | 2 |
| FancyNameTag Copy Constructor (id, company, deep copy Bio) | 6 |
| FancyNameTag Move Constructor (id, company, Bio transfer) | 8 |
| Copy Independence (modifying copy doesn't affect original) | 2 |
| Setter Validation (setId rejects 0, setCompany rejects empty) | 4 |
