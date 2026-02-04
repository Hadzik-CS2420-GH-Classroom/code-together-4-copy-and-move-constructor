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

    // TODO: Validate invariants — throw std::invalid_argument if:
    //   - id_ <= 0           ("NameTag id must be positive")
    //   - name_ is empty     ("NameTag name must not be empty")
    //   - company_ is empty  ("NameTag company must not be empty")

    // TODO: Log which NameTag was constructed using std::cout
    // Format: Constructor: id=1, name="Waldo", company="Weber State University"
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

// TODO: Implement the three getters below
// Each should return the corresponding private member
// getId() returns by value (int is cheap to copy)
// getName() and getCompany() return by const reference (avoids copying strings)

// Returns the id value
int NameTag::getId() const { /* TODO */ return 0; }

// Returns a const reference to the name string
const std::string& NameTag::getName() const { /* TODO */ static std::string empty; return empty; }

// Returns a const reference to the company string
const std::string& NameTag::getCompany() const { /* TODO */ static std::string empty; return empty; }

// TODO: Implement the three setters below
// Each should validate the input and throw std::invalid_argument if invalid,
// then assign the new value to the private member

// Sets the id, enforcing the invariant that it must be positive
void NameTag::setId(int id) {
    // TODO: Validate that id > 0, throw std::invalid_argument("NameTag id must be positive") if not
    // TODO: Assign id to id_
}

// Sets the name, enforcing the invariant that it must not be empty
void NameTag::setName(const std::string& name) {
    // TODO: Validate that name is not empty, throw std::invalid_argument("NameTag name must not be empty") if not
    // TODO: Assign name to name_
}

// Sets the company name, enforcing the invariant that it must not be empty
void NameTag::setCompany(const std::string& company) {
    // TODO: Validate that company is not empty, throw std::invalid_argument("NameTag company must not be empty") if not
    // TODO: Assign company to company_
}
