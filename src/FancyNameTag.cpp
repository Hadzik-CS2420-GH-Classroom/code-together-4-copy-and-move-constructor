// Include the FancyNameTag class declaration
#include "FancyNameTag.h"

// utility for std::exchange and std::move
#include <utility>

// Constructor: copies id and company by value, allocates a new Bio on the heap
FancyNameTag::FancyNameTag(int id, const std::string& company, const Bio& bio)
    : id_(id), company_(company), bio_(new Bio(bio)) {
    // Validate invariants: id must be positive
    if (id_ <= 0) {
        throw std::invalid_argument("FancyNameTag id must be positive");
    }
    // Validate invariants: company must not be empty
    if (company_.empty()) {
        throw std::invalid_argument("FancyNameTag company must not be empty");
    }
    // Validate the Bio fields: name must not be empty
    if (bio_->name.empty()) {
        throw std::invalid_argument("FancyNameTag bio name must not be empty");
    }
    // Validate the Bio fields: title must not be empty
    if (bio_->title.empty()) {
        throw std::invalid_argument("FancyNameTag bio title must not be empty");
    }
    // Validate the Bio fields: year must be positive
    if (bio_->year <= 0) {
        throw std::invalid_argument("FancyNameTag bio year must be positive");
    }
    // Log construction with the Bio contents and its heap address
    std::cout << "Constructor: id=" << id_ << ", company=\"" << company_
              << "\", bio={"; bio_->print(); std::cout << "} at " << bio_ << "\n";
}

// Destructor: cleans up the heap-allocated Bio
FancyNameTag::~FancyNameTag() {
    std::cout << "Destructor: id=" << id_ << ", bio=";
    // Check if bio_ is still valid (not moved)
    if (bio_) {
        // Print the Bio contents and address before deleting
        std::cout << "{"; bio_->print(); std::cout << "} at " << bio_;
    } else {
        // This object was moved from, so bio_ is nullptr
        std::cout << "(moved)";
    }
    std::cout << "\n";
    // Free the heap memory (delete on nullptr is safe and does nothing)
    delete bio_;
}

// Copy constructor: allocates NEW heap memory and copies the Bio data into it
// This is a deep copy - the new object has its own independent Bio
FancyNameTag::FancyNameTag(const FancyNameTag& other)
    : id_(other.id_), company_(other.company_), bio_(new Bio(*other.bio_)) {
    // Log the copy, showing the two different heap addresses
    std::cout << "Copy Constructor: id=" << id_ << ", copied bio from "
              << other.bio_ << " to " << bio_ << "\n";
}

// Copy assignment operator: replaces this object's data with a deep copy of other
FancyNameTag& FancyNameTag::operator=(const FancyNameTag& other) {
    std::cout << "Copy Assignment Operator\n";
    // Self-assignment check: don't delete our own data if assigning to ourselves
    if (this != &other) {
        // Free the old Bio before replacing it
        delete bio_;
        // Copy the stack members
        id_ = other.id_;
        company_ = other.company_;
        // Allocate new heap memory and copy the Bio data (deep copy)
        bio_ = new Bio(*other.bio_);
    }
    // Return *this to support chaining (e.g. a = b = c)
    return *this;
}

// Move constructor: takes ownership of other's Bio pointer instead of copying
// This is much faster than copying because no heap allocation is needed
FancyNameTag::FancyNameTag(FancyNameTag&& other) noexcept
    : id_(other.id_),
      // std::move transfers ownership of the string's internal buffer
      company_(std::move(other.company_)),
      // std::exchange swaps other.bio_ with nullptr and returns the old value
      // After this, other.bio_ is nullptr (safe to destruct)
      bio_(std::exchange(other.bio_, nullptr)) {
    // Log the move, showing we took the same heap address (no new allocation)
    std::cout << "Move Constructor: id=" << id_ << ", took ownership of bio at "
              << bio_ << "\n";
}

// Move assignment operator: replaces this object's data by stealing from other
FancyNameTag& FancyNameTag::operator=(FancyNameTag&& other) noexcept {
    std::cout << "Move Assignment Operator\n";
    // Self-assignment check: don't delete our own data if moving to ourselves
    if (this != &other) {
        // Free the old Bio before replacing it
        delete bio_;
        // Take the stack members
        id_ = other.id_;
        // std::move transfers ownership of the string's internal buffer
        company_ = std::move(other.company_);
        // std::exchange swaps other.bio_ with nullptr and returns the old value
        bio_ = std::exchange(other.bio_, nullptr);
    }
    // Return *this to support chaining
    return *this;
}

// Prints all FancyNameTag data with a descriptive label
void FancyNameTag::print(const std::string& label) const {
    std::cout << label << ": id=" << id_ << ", company=\"" << company_ << "\", bio=";
    // Check if bio_ is still valid (not moved)
    if (bio_) {
        // Print the Bio contents and the heap address
        std::cout << "{"; bio_->print(); std::cout << "} (addr=" << bio_ << ")";
    } else {
        // This object was moved from, so bio_ is nullptr
        std::cout << "(moved)";
    }
    std::cout << "\n";
}

// Returns the id value
int FancyNameTag::getId() const { return id_; }

// Returns a const reference to the company string
const std::string& FancyNameTag::getCompany() const { return company_; }

// Returns a const reference to the Bio object (dereferences the pointer)
const Bio& FancyNameTag::getBio() const { return *bio_; }
