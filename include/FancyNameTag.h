// Header guard - prevents this file from being included more than once
#pragma once

// Include the Bio struct since we store a pointer to one
#include "Bio.h"

// iostream for std::cout in print()
#include <iostream>
// stdexcept for std::invalid_argument
#include <stdexcept>
// string for std::string members and parameters
#include <string>

// Same idea as NameTag, but with a heap-allocated Bio.
// Because it owns a raw pointer, we must implement at minimum:
//   - Destructor: to free the heap memory
//   - Copy constructor: to perform a deep copy (avoid shallow copy danger)
//   - Move constructor: to efficiently transfer ownership
//
// We delete the copy and move assignment operators to keep this example simple.
// In modern C++, you'd use std::unique_ptr<Bio> instead of Bio* and get all
// this behavior automatically — we'll cover that in the next Code Together.
//
// Like NameTag, this is a class because we enforce invariants:
//   - id_ must be positive
//   - company_ must not be empty
//   - bio_ must point to a valid Bio (name and title must not be empty, year > 0)
// The constructor validates all of these. Private access ensures no outside
// code can set id_ to -1 or point bio_ at garbage memory.
// Compare this to Bio (a struct): Bio has no invariants, so anyone can
// set its fields to whatever they want - and that's fine for a plain data holder.
class FancyNameTag {
public:
    // Constructor: creates a new Bio on the heap from the given bio

    FancyNameTag(int id, const std::string& company, const Bio& bio);

	// Destructor: frees the heap-allocated Bio

    ~FancyNameTag();

    // Copy constructor: performs a deep copy of the Bio

    FancyNameTag(const FancyNameTag& other);

    // Move constructor: transfers ownership of the Bio pointer
    
    // The && means "rvalue reference." An rvalue is a temporary value with no
    // permanent address — something you can read from but not assign to.
    // Examples: the literal 42 or the result of (x + 3).
    // std::move() casts an lvalue (a named variable) into an rvalue reference,
    // which tells the compiler: "I'm done with this object, steal its resources."
    
    // noexcept is a promise that this function will never throw an exception.
    // Why it matters: std::vector will REFUSE to use your move constructor unless
    // it's noexcept. When a vector grows, it must relocate elements to a bigger
    // buffer. If a move throws halfway through, some elements are already gutted
    // (moved-from) — the old buffer is ruined and there's no way to roll back.
    // So vector plays it safe: noexcept move = fast (steal pointers), no noexcept
    // = falls back to copy (slow but safe, originals are still intact if it throws).
    // Our move just copies an int, moves a string, and swaps a pointer — nothing
    // that can throw — so marking it noexcept is both accurate and necessary.

    FancyNameTag(FancyNameTag&& other) noexcept;

    // Delete copy and move assignment operators — we're keeping this example simple.
    // If you need to reassign a FancyNameTag, create a new one instead.
    // (In real code, you'd use std::unique_ptr<Bio> which handles this automatically.)

    FancyNameTag& operator=(const FancyNameTag& other) = delete;
    FancyNameTag& operator=(FancyNameTag&& other) = delete;

    // Prints all FancyNameTag data with a right-justified label and optional state on the right
    // Example: print("fOriginal", "unchanged") produces:
    //     fOriginal  STACK xxxxx  id=1  company="WSU"  bio={...} HEAP xxxxx  (unchanged)
    void print(const std::string& label, const std::string& state = "") const;

    // Returns the id by value (int is small/cheap to copy, no reference needed).
    // No need for "const int" here - the caller gets their own copy,
    // so they can't modify our private id_ no matter what.
    // The trailing "const" means this method promises not to modify the object,
    // which allows it to be called on const FancyNameTag references/objects.

    int getId() const;

    // Returns the company by const reference to avoid copying the entire string.
    // "const std::string&" prevents the caller from modifying our private data.

    const std::string& getCompany() const;

    // Returns the Bio by const reference to avoid copying the entire struct.

    const Bio& getBio() const;

    // Sets the id after validating it is positive.
    // This is how we allow modification while still enforcing our invariants.

    void setId(int id);
    // Sets the company name after validating it is not empty.
    // This is how we allow modification while still enforcing our invariants.

    void setCompany(const std::string& company);

private:
    int id_;            // numeric identifier (stack-allocated)
    std::string company_; // company name (stack-allocated)
    Bio* bio_;          // pointer to a Bio on the heap (requires manual management)
};
