// Include the NameTag class declaration
#include "NameTag.h"

// Constructor: initializes id_ and company_ using the member initializer list
NameTag::NameTag(int id, const std::string& company)
    : id_(id), company_(company) {
    // Validate invariants: id must be positive
    if (id_ <= 0) {
        throw std::invalid_argument("NameTag id must be positive");
    }
    // Validate invariants: company must not be empty
    if (company_.empty()) {
        throw std::invalid_argument("NameTag company must not be empty");
    }
    // Log which NameTag was constructed
    std::cout << "Constructor: id=" << id_ << ", company=\"" << company_ << "\"\n";
}

// Prints the NameTag data with a descriptive label
void NameTag::print(const std::string& label) const {
    std::cout << label << ": id=" << id_ << ", company=\"" << company_ << "\"\n";
}

// Returns the id value
int NameTag::getId() const { return id_; }

// Returns a const reference to the company string
const std::string& NameTag::getCompany() const { return company_; }
