// Include the Bio struct declaration
#include "Bio.h"

// Prints all Bio fields in a comma-separated format
void Bio::print() const {
    // Output each field separated by commas
    std::cout << name << ", " << title << ", " << department << ", " << year;
}
