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

    // TODO: Validate invariants — throw std::invalid_argument if:
    //   - id_ <= 0             ("FancyNameTag id must be positive")
    //   - company_ is empty    ("FancyNameTag company must not be empty")
    //   - bio_->name is empty  ("FancyNameTag bio name must not be empty")
    //   - bio_->title is empty ("FancyNameTag bio title must not be empty")
    //   - bio_->year <= 0      ("FancyNameTag bio year must be positive")

    // TODO: Log construction with std::cout showing id, company, bio contents, and heap address
    // Use shortAddr(this) for the stack address and shortAddr(bio_) for the heap address
    // Format: Constructor (STACK xxxxx): id=1, company="WSU", bio={...} (HEAP xxxxx)
}

// Destructor: cleans up the heap-allocated Bio
FancyNameTag::~FancyNameTag() {
    // TODO: Log the destructor call with std::cout
    // Use shortAddr(this) for the stack address
    // Check if bio_ is still valid (not nullptr from a move)
    //   - If valid: print bio contents and shortAddr(bio_), then delete bio_
    //   - If nullptr: print "(moved)" — this object was moved from
    // Remember: delete on nullptr is safe and does nothing

    // TODO: Free the heap memory with delete bio_
}

// Copy constructor: allocates NEW heap memory and copies the Bio data into it
// This is a deep copy - the new object has its own independent Bio
FancyNameTag::FancyNameTag(const FancyNameTag& other)
    // TODO: Initialize id_ from other.id_
    // TODO: Initialize company_ from other.company_
    // TODO: Initialize bio_ with a NEW Bio that copies other's Bio data
    //   Hint: bio_(new Bio(*other.bio_))
    //   The * dereferences the pointer: follows the address to get the actual
    //   Bio object on the heap. Without the *, we'd be passing a Bio* (an address)
    //   instead of a Bio (the object). Then new Bio(...) calls Bio's copy
    //   constructor with that object, allocating a new copy on the heap.
    : id_(0), company_(""), bio_(nullptr) {

    // TODO: Log the copy, showing the two different heap addresses
    // Use shortAddr(other.bio_) and shortAddr(bio_)
}

// Copy assignment operator: replaces this object's data with a deep copy of other
FancyNameTag& FancyNameTag::operator=(const FancyNameTag& other) {
    std::cout << "Copy Assignment Operator\n";
    // TODO: Self-assignment check: if (this != &other)
    //   Without this, "a = a" would delete our own Bio, then try to copy from
    //   the deleted Bio — undefined behavior!
    //
    //   Inside the if block:
    //   1. Delete the old Bio:     delete bio_;
    //   2. Copy the stack members: id_ = other.id_;  company_ = other.company_;
    //   3. Deep copy the Bio:      bio_ = new Bio(*other.bio_);
    //      (*other.bio_ dereferences the pointer — see copy constructor comment)

    // TODO: Return *this to support chaining (e.g. a = b = c)
    return *this;
}

// Move constructor: takes ownership of other's Bio pointer instead of copying
// This is much faster than copying because no heap allocation is needed
// noexcept: nothing here can throw (int copy, string move, pointer swap),
// and std::vector requires noexcept to use move instead of copy during reallocation.
FancyNameTag::FancyNameTag(FancyNameTag&& other) noexcept
    // TODO: Initialize id_ from other.id_ (ints are just copied — nothing to "steal")
    // TODO: Initialize company_ using std::move(other.company_) — steals the string's internal buffer
    // TODO: Initialize bio_ using std::exchange(other.bio_, nullptr)
    //   std::exchange returns the old value of other.bio_ and sets it to nullptr
    //   After this, other.bio_ is nullptr (safe to destruct, won't double-free)
    : id_(0), company_(""), bio_(nullptr) {

    // TODO: Log the move, showing we took the same heap address (no new allocation)
    // Use shortAddr(this) and shortAddr(bio_)
}

// Move assignment operator: replaces this object's data by stealing from other
// Also noexcept — same reason: no allocation, nothing that can throw.
FancyNameTag& FancyNameTag::operator=(FancyNameTag&& other) noexcept {
    std::cout << "Move Assignment Operator\n";
    // TODO: Self-assignment check: if (this != &other)
    //
    //   Inside the if block:
    //   1. Delete the old Bio:            delete bio_;
    //   2. Take the int:                  id_ = other.id_;
    //   3. Move the string:               company_ = std::move(other.company_);
    //   4. Exchange the bio pointer:       bio_ = std::exchange(other.bio_, nullptr);

    // TODO: Return *this to support chaining
    return *this;
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

// TODO: Implement the three getters below
// getId() returns by value (int is cheap to copy)
// getCompany() returns by const reference (avoids copying string)
// getBio() returns by const reference (dereferences the pointer with *bio_)

// Returns the id value
int FancyNameTag::getId() const { /* TODO */ return 0; }

// Returns a const reference to the company string
const std::string& FancyNameTag::getCompany() const { /* TODO */ static std::string empty; return empty; }

// Returns a const reference to the Bio object (dereferences the pointer)
const Bio& FancyNameTag::getBio() const { /* TODO */ return *bio_; }

// TODO: Implement the two setters below
// Each should validate the input, throw std::invalid_argument if invalid,
// then assign the new value to the private member

// Sets the id, enforcing the invariant that it must be positive
void FancyNameTag::setId(int id) {
    // TODO: Validate that id > 0, throw std::invalid_argument("FancyNameTag id must be positive") if not
    // TODO: Assign id to id_
}

// Sets the company name, enforcing the invariant that it must not be empty
void FancyNameTag::setCompany(const std::string& company) {
    // TODO: Validate that company is not empty, throw std::invalid_argument("FancyNameTag company must not be empty") if not
    // TODO: Assign company to company_
}
