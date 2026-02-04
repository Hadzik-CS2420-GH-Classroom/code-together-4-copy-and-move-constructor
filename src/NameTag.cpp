// Include the NameTag class declaration
#include "NameTag.h"
// Include the short address utility for readable output
#include "AddrUtil.h"
// Include iomanip for std::setw and std::left (column alignment in print)
#include <iomanip>

// Constructor: initializes id_, name_, and company_ using the member initializer list
NameTag::NameTag(int id, const std::string& name, const std::string& company)
    : id_(id), 
      name_(name), 
      company_(company) {

    // Validate invariants: id must be positive
    if (id_ <= 0) {
        throw std::invalid_argument("NameTag id must be positive");
    }
    // Validate invariants: name must not be empty
    if (name_.empty()) {
        throw std::invalid_argument("NameTag name must not be empty");
    }
    // Validate invariants: company must not be empty
    if (company_.empty()) {
        throw std::invalid_argument("NameTag company must not be empty");
    }
    // Log which NameTag was constructed
    std::cout << "Constructor: id=" 
              << id_ 
              << ", name=\"" 
              << name_
              << "\", company=\"" 
              << company_ 
              << "\"\n";
}

// Prints the NameTag data with a descriptive label and optional state hint
// Uses fixed-width columns so consecutive prints line up for easy comparison
// "this" is the address of the object itself on the stack
void NameTag::print(const std::string& label, const std::string& state) const {
    // Column 1: label right-justified to 18 characters (fits longest variable name)
    std::cout << std::right 
              << std::setw(18) 
              << label

    // Column 2: stack address (always 5 hex chars from shortAddr)
              
              << "  STACK " 
              << shortAddr(this)

    // Column 3: id padded to 6 characters (fits "id=XX" with spacing)

              << "  id=" 
              << std::left 
              << std::setw(6) 
              << id_
    
    // Column 4: name padded to 12 characters

              << "name=" 
              << std::setw(12) 
              << ("\"" + name_ + "\"")

    // Column 5: company

              << "company=\"" 
              << company_ 
              << "\"";

    // Optional state hint on the right (e.g., "(unchanged)", "(modified)")
    if (!state.empty()) {
        std::cout << "  (" 
                  << state << ")";
    }
    std::cout << "\n";
}

// Returns the id value
int NameTag::getId() const { return id_; }

// Returns a const reference to the name string
const std::string& NameTag::getName() const { return name_; }

// Returns a const reference to the company string
const std::string& NameTag::getCompany() const { return company_; }

// Sets the id, enforcing the invariant that it must be positive
void NameTag::setId(int id) {
    // Validate before modifying — this is the advantage of using a setter
    // instead of making id_ public
    if (id <= 0) {
        throw std::invalid_argument("NameTag id must be positive");
    }
    id_ = id;
}

// Sets the name, enforcing the invariant that it must not be empty
void NameTag::setName(const std::string& name) {
    // Validate before modifying — this is the advantage of using a setter
    // instead of making name_ public
    if (name.empty()) {
        throw std::invalid_argument("NameTag name must not be empty");
    }
    name_ = name;
}

// Sets the company name, enforcing the invariant that it must not be empty
void NameTag::setCompany(const std::string& company) {
    // Validate before modifying — this is the advantage of using a setter
    // instead of making company_ public
    if (company.empty()) {
        throw std::invalid_argument("NameTag company must not be empty");
    }
    company_ = company;
}
