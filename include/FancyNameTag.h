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
// Because it owns a raw pointer, we must implement the Rule of Five:
// destructor, copy constructor, copy assignment, move constructor, move assignment.
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

	// Destructor: frees the heap-allocated Bio (REQUIRED by Rule of Five)
    ~FancyNameTag();

    // Copy constructor: performs a deep copy of the Bio (REQUIRED by Rule of Five)
    FancyNameTag(const FancyNameTag& other);

    // Copy assignment operator: deep copies the Bio from another FancyNameTag (REQUIRED by Rule of Five)
    FancyNameTag& operator=(const FancyNameTag& other);

    // Move constructor: transfers ownership of the Bio pointer (REQUIRED by Rule of Five)
    FancyNameTag(FancyNameTag&& other) noexcept;

    // Move assignment operator: transfers ownership of the Bio pointer (REQUIRED by Rule of Five)
    FancyNameTag& operator=(FancyNameTag&& other) noexcept;

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
