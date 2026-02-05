// Include the FancyNameTag class declaration
#include "FancyNameTag.h"
// Include the short address utility for readable output
#include "AddrUtil.h"
// Include iomanip for std::setw and std::left (column alignment in print)
#include <iomanip>

// utility for std::exchange and std::move
#include <utility>

// Constructor: copies id and company by value, allocates a new Bio on the heap
FancyNameTag::FancyNameTag(int id, const std::string& company, const Bio& bio)
    : id_(id),
      company_(company),
      bio_(new Bio(bio)) {

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
    // In C++, 'this' is a pointer to the current object.
    // It plays the same role as 'self' in Python, but explicitly as a pointer.
    // We use it here only to show the stack address of this object so you can
    // see that copies and moves create different objects in memory.

    std::cout << "Constructor (STACK "
              << shortAddr(this)
              << "): id="
              << id_
              << ", company=\""
              << company_
              << "\", bio={"; bio_->print(); std::cout
              << "} (HEAP " << shortAddr(bio_)
              << ")\n";
}

// ============================================================================
// TODO 1: Destructor
// ============================================================================
// The destructor is called automatically when the object goes out of scope.
// Since we allocated bio_ on the heap with 'new', we must free it with 'delete'.
//
// Steps:
//   1. Print a message showing what's being destroyed (use the logging pattern below)
//   2. Check if bio_ is not nullptr before printing its contents
//   3. Delete bio_ (delete on nullptr is safe and does nothing)
//
// Logging pattern (copy this structure):
//   std::cout << "Destructor (STACK " << shortAddr(this) << "): id=" << id_ << ", bio=";
//   if (bio_) {
//       std::cout << "{"; bio_->print(); std::cout << "} (HEAP " << shortAddr(bio_) << ")";
//   } else {
//       std::cout << "(moved)";
//   }
//   std::cout << "\n";
// ============================================================================
FancyNameTag::~FancyNameTag() {
    // TODO: Implement the destructor
    // 1. Print the destructor message (use the logging pattern above)
    // 2. Delete bio_ to free the heap memory
}

// ============================================================================
// TODO 2: Copy Constructor
// ============================================================================
// The copy constructor creates a NEW object as a copy of an existing one.
// Since we own a raw pointer (bio_), we must perform a DEEP COPY:
//   - Allocate NEW heap memory for our own Bio
//   - Copy the data from other's Bio into our new Bio
//
// If we just copied the pointer (shallow copy), both objects would point to
// the SAME heap memory. When one is destroyed, the other has a dangling pointer!
// See images/shallow_copy_danger.png for why this is dangerous.
// See images/fancy_copy_constructor.png for how deep copy works.
//
// Syntax reminder:
//   - "other.bio_" is a pointer (Bio*)
//   - "*other.bio_" dereferences it to get the actual Bio object
//   - "new Bio(*other.bio_)" allocates a new Bio and copies the data into it
//
// Steps:
//   1. Initialize id_ from other.id_ (int copy)
//   2. Initialize company_ from other.company_ (string copy)
//   3. Initialize bio_ with: new Bio(*other.bio_)  <-- DEEP COPY
//   4. Print a message showing the copy (use the logging pattern below)
//
// Logging pattern (put this in the constructor body):
//   std::cout << "Copy Constructor (STACK " << shortAddr(this) << "): id=" << id_
//             << ", copied bio from HEAP " << shortAddr(other.bio_)
//             << " to HEAP " << shortAddr(bio_) << "\n";
// ============================================================================
FancyNameTag::FancyNameTag(const FancyNameTag& other)
    // TODO: Initialize id_ from other.id_
    // TODO: Initialize company_ from other.company_
    // TODO: Initialize bio_ with a deep copy: new Bio(*other.bio_)
{
    // TODO: Print the copy constructor message (use the logging pattern above)
}

// ============================================================================
// TODO 3: Move Constructor
// ============================================================================
// The move constructor TRANSFERS ownership of resources from a temporary object.
// Instead of allocating new memory and copying, we "steal" the other's pointer.
// This is much faster because no heap allocation is needed!
//
// After the move, "other" is left in a "valid but unspecified" state.
// We set other.bio_ to nullptr so its destructor won't delete our Bio.
//
// Key tools:
//   - std::move(other.company_): transfers the string's internal buffer
//   - std::exchange(other.bio_, nullptr): returns other.bio_ and sets it to nullptr
//
// The "noexcept" keyword is a promise that this function will never throw.
// This is important because std::vector will REFUSE to use move unless it's noexcept.
// (If a move threw mid-reallocation, the vector would be in an unrecoverable state.)
//
// Steps:
//   1. Initialize id_ from other.id_ (int copy - primitives have nothing to "steal")
//   2. Initialize company_ with: std::move(other.company_)  <-- transfers the string
//   3. Initialize bio_ with: std::exchange(other.bio_, nullptr)  <-- steals the pointer
//   4. Print a message showing the move (use the logging pattern below)
//
// Logging pattern (put this in the constructor body):
//   std::cout << "Move Constructor (STACK " << shortAddr(this) << "): id=" << id_
//             << ", took ownership of bio at HEAP " << shortAddr(bio_) << "\n";
// ============================================================================
FancyNameTag::FancyNameTag(FancyNameTag&& other) noexcept
    // TODO: Initialize id_ from other.id_
    // TODO: Initialize company_ with std::move(other.company_)
    // TODO: Initialize bio_ with std::exchange(other.bio_, nullptr)
{
    // TODO: Print the move constructor message (use the logging pattern above)
}

// Note: Copy and move assignment operators are deleted in the header.
// This keeps the example focused on construction. In practice, you'd either:
//   1. Implement them (full Rule of Five), or
//   2. Use std::unique_ptr<Bio> which handles everything automatically

// Prints all FancyNameTag data with a descriptive label and optional state hint
// Uses fixed-width columns so consecutive prints line up for easy comparison
// "this" is the address of the object itself on the stack
// "bio_" is the address of the Bio on the heap
// When you copy: "this" is different AND "bio_" is different (new heap allocation)
// When you move: "this" is different BUT "bio_" is the SAME (pointer was transferred)
void FancyNameTag::print(const std::string& label, const std::string& state) const {
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

    // Column 4: company padded to 30 characters

              << "company="
              << std::setw(30)
              << ("\"" + company_ + "\"")

    // Column 5: bio contents and heap address

              << "bio=";

    // Check if bio_ is still valid (not moved)

    if (bio_) {
        // Print the Bio contents and the heap address
        std::cout << "{";
        bio_->print();
        std::cout << "} HEAP "
                  << shortAddr(bio_);
    } else {
        // This object was moved from, so bio_ is nullptr
        std::cout << "(moved)";
    }
    // Optional state hint on the right (e.g., "(unchanged)", "(modified)")
    if (!state.empty()) {
        std::cout << "  ("
                  << state
                  << ")";
    }
    std::cout << "\n";
}

// Returns the id value
int FancyNameTag::getId() const { return id_; }

// Returns a const reference to the company string
const std::string& FancyNameTag::getCompany() const { return company_; }

// Returns a const reference to the Bio object (dereferences the pointer)
const Bio& FancyNameTag::getBio() const { return *bio_; }

// Sets the id, enforcing the invariant that it must be positive
void FancyNameTag::setId(int id) {
    // Validate before modifying — this is the advantage of using a setter
    // instead of making id_ public
    if (id <= 0) {
        throw std::invalid_argument("FancyNameTag id must be positive");
    }
    id_ = id;
}

// Sets the company name, enforcing the invariant that it must not be empty
void FancyNameTag::setCompany(const std::string& company) {
    // Validate before modifying — this is the advantage of using a setter
    // instead of making company_ public
    if (company.empty()) {
        throw std::invalid_argument("FancyNameTag company must not be empty");
    }
    company_ = company;
}
