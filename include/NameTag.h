// Header guard - prevents this file from being included more than once
#pragma once

// iostream for std::cout in print()
#include <iostream>
// stdexcept for std::invalid_argument
#include <stdexcept>
// string for std::string members and parameters
#include <string>

// A simple class with only stack-allocated members.
// The compiler-generated copy and move constructors work correctly here
// because all members are trivially copyable/movable.
// We do NOT need to write custom copy/move for this class.
//
// This is a class (not a struct) because we enforce invariants:
//   - id_ must be positive
//   - name_ must not be empty
//   - company_ must not be empty
// The constructor validates these rules, and private access prevents
// outside code from breaking them. This is why we use a class instead
// of a struct - a struct would let anyone set invalid data directly.
class NameTag {
public:
    // Constructor: takes an id number, a person's name, and a company name
    NameTag(int id, const std::string& name, const std::string& company);

    // Prints the NameTag's data with a right-justified label and optional state on the right
    // Example: print("original", "unchanged") produces:
    //     original  STACK xxxxx  id=1  name="Alice"  company="WSU"  (unchanged)
    void print(const std::string& label, const std::string& state = "") const;

    // Returns the id by value (int is small/cheap to copy, no reference needed).
    // No need for "const int" here - the caller gets their own copy,
    // so they can't modify our private id_ no matter what.
    // The trailing "const" means this method promises not to modify the object,
    // which allows it to be called on const NameTag references/objects.
    int getId() const;
    // Returns the name by const reference to avoid copying the entire string.
    // "const std::string&" prevents the caller from modifying our private data.
    // The trailing "const" means this method promises not to modify the object.
    const std::string& getName() const;
    // Returns the company by const reference to avoid copying the entire string.
    // "const std::string&" prevents the caller from modifying our private data.
    // The trailing "const" means this method promises not to modify the object.
    const std::string& getCompany() const;

    // Sets the id after validating it is positive.
    // This is how we allow modification while still enforcing our invariants.
    void setId(int id);
    // Sets the name after validating it is not empty.
    // This is how we allow modification while still enforcing our invariants.
    void setName(const std::string& name);
    // Sets the company name after validating it is not empty.
    // This is how we allow modification while still enforcing our invariants.
    void setCompany(const std::string& company);

private:
    int id_;              // numeric identifier (stack-allocated)
    std::string name_;    // person's name (stack-allocated)
    std::string company_; // company name (stack-allocated)
};
