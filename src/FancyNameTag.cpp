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

// Destructor: cleans up the heap-allocated Bio
FancyNameTag::~FancyNameTag() {
    std::cout << "Destructor (STACK " 
              << shortAddr(this) 
              << "): id=" 
              << id_ 
              << ", bio=";

    // Check if bio_ is still valid (not moved)
    if (bio_) {
        // Print the Bio contents and address before deleting
        std::cout << "{"; 
        bio_->print(); 
        std::cout << "} (HEAP " 
                  << shortAddr(bio_) 
                  << ")";
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
    : id_(other.id_), 
      company_(other.company_), 
      // *other.bio_ dereferences the pointer: follows the address to get the
      // actual Bio object on the heap. Without the *, we'd be passing a Bio*
      // (an address) instead of a Bio (the object). Then new Bio(...) calls
      // Bio's copy constructor with that object, allocating a new copy on the heap.
      bio_(new Bio(*other.bio_)) {

        // Log the copy, showing the two different heap addresses
        std::cout << "Copy Constructor (STACK " 
                  << shortAddr(this) 
                  << "): id=" 
                  << id_
                  << ", copied bio from HEAP " 
                  << shortAddr(other.bio_)
                  << " to HEAP " << shortAddr(bio_) 
                  << "\n";
}

// Note: Copy and move assignment operators are deleted in the header.
// This keeps the example focused on construction. In practice, you'd either:
//   1. Implement them (full Rule of Five), or
//   2. Use std::unique_ptr<Bio> which handles everything automatically

// Move constructor: takes ownership of other's Bio pointer instead of copying
// This is much faster than copying because no heap allocation is needed
// noexcept: nothing here can throw (int copy, string move, pointer swap),
// and std::vector requires noexcept to use move instead of copy during reallocation.
FancyNameTag::FancyNameTag(FancyNameTag&& other) noexcept
    : id_(other.id_),
      // std::move transfers ownership of the string's internal buffer
      company_(std::move(other.company_)),
      // std::exchange swaps other.bio_ with nullptr and returns the old value
      // After this, other.bio_ is nullptr (safe to destruct)
      bio_(std::exchange(other.bio_, nullptr)) {
    // Log the move, showing we took the same heap address (no new allocation)
    std::cout << "Move Constructor (STACK " 
              << shortAddr(this) 
              << "): id=" 
              << id_
              << ", took ownership of bio at HEAP " 
              << shortAddr(bio_) 
              << "\n";
}

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
