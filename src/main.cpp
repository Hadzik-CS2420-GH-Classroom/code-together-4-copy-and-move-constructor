// Include the FancyNameTag class (which also brings in Bio)
#include "FancyNameTag.h"
#include "NameTag.h"


#include <iostream>
#include <utility>

// Helper function that returns a FancyNameTag by value.
// Returning by value may trigger the move constructor.
FancyNameTag createFancyNameTag(int id, const std::string& company, const Bio& bio) {
    // Construct a local FancyNameTag
    FancyNameTag tag(id, company, bio);
    // Returning a local variable by value may invoke the move constructor
    return tag;
}

int main() {
    // -------------------------------------------------------
    // Part 1: NameTag (stack-only members, default copy/move)
    // The compiler generates correct copy/move for us.
    // -------------------------------------------------------
    std::cout << "========================================\n";
    std::cout << " Part 1: NameTag (default copy/move)\n";
    std::cout << "========================================\n\n";

    // --- Construct a NameTag ---
    std::cout << "--- Construct ---\n";
    // Create original with id=1 and company="Acme Corp"
    NameTag original(1, "Acme Corp");
    // Print original to see its initial state
    original.print("original");

    // --- Default Copy Constructor ---
    std::cout << "\n--- Default Copy Constructor ---\n";
    // Create copied as a copy of original using the compiler-generated copy constructor
    NameTag copied(original);
    // Print copied to verify it has the same values as original
    copied.print("copied");
    // Print original to verify it was not modified by the copy
    original.print("original (unchanged)");

    // --- Default Copy Assignment ---
    std::cout << "\n--- Default Copy Assignment ---\n";
    // Create assigned with different valid values (will be overwritten by assignment)
    NameTag assigned(99, "Placeholder Inc");
    // Use the compiler-generated copy assignment operator to copy original into assigned
    assigned = original;
    // Print assigned to verify it now matches original
    assigned.print("assigned");
    // Print original to verify it was not modified
    original.print("original (unchanged)");

    // --- Default Move Constructor ---
    std::cout << "\n--- Default Move Constructor ---\n";
    // std::move casts original to an rvalue reference, enabling the move constructor
    NameTag moved(std::move(original));
    // Print moved to verify it received original's values
    moved.print("moved");
    // Print original: for stack-only types, move is just a copy, so original still has its values
    original.print("original (still valid, same values)");
    // Note: Move transfers resources when possible. After moving, the source object is valid but unspecified.
	// The value may or may not be the same as before the move.

    // -------------------------------------------------------
    // Part 2: FancyNameTag (heap resource, custom copy/move)
    // We must implement the Rule of Five because bio_ is a raw pointer.
    // -------------------------------------------------------
    std::cout << "\n========================================\n";
    std::cout << " Part 2: FancyNameTag (custom copy/move)\n";
    std::cout << "========================================\n\n";

    // --- Construct a FancyNameTag ---
    std::cout << "--- Construct ---\n";
    // Create original with a Bio struct using aggregate initialization
    FancyNameTag fOriginal(1, "Acme Corp", {"Alice", "Engineer", "R&D", 2021});
    // Print fOriginal to see its initial state and heap address
    fOriginal.print("fOriginal");

    // --- Copy Constructor (deep copy) ---
    std::cout << "\n--- Copy Constructor (deep copy) ---\n";
    // Create fCopied as a deep copy of fOriginal - a NEW Bio is allocated on the heap
    FancyNameTag fCopied(fOriginal);
    // Print fCopied to verify it has the same data but a DIFFERENT heap address
    fCopied.print("fCopied");
    // Print fOriginal to verify it was not modified by the copy
    fOriginal.print("fOriginal (unchanged)");

    // --- Copy Assignment ---
    std::cout << "\n--- Copy Assignment ---\n";
    // Create fAssigned with its own data
    FancyNameTag fAssigned(2, "Globex", {"Bob", "Manager", "Sales", 2019});
    // Copy assignment: fAssigned's old Bio is deleted, a new one is allocated with fOriginal's data
    fAssigned = fOriginal;
    // Print fAssigned to verify it now matches fOriginal but has its own heap address
    fAssigned.print("fAssigned");

    // --- Move Constructor (transfer ownership) ---
    std::cout << "\n--- Move Constructor (transfer ownership) ---\n";
    // std::move casts fOriginal to an rvalue reference, enabling the move constructor
    // The move constructor steals fOriginal's Bio pointer instead of allocating new memory
    FancyNameTag fMoved(std::move(fOriginal));
    // Print fMoved to verify it has fOriginal's data at the SAME heap address
    fMoved.print("fMoved");
    // Print fOriginal to verify its bio_ is now nullptr (it was moved from)
    fOriginal.print("fOriginal (after move)");

    // --- Move Assignment ---
    std::cout << "\n--- Move Assignment ---\n";
    // Create fMoveAssigned with its own data
    FancyNameTag fMoveAssigned(3, "Initech", {"Charlie", "Director", "Engineering", 2018});
    // Move assignment: fMoveAssigned's old Bio is deleted, then it steals fMoved's Bio pointer
    fMoveAssigned = std::move(fMoved);
    // Print fMoveAssigned to verify it took fMoved's data
    fMoveAssigned.print("fMoveAssigned");
    // Print fMoved to verify its bio_ is now nullptr
    fMoved.print("fMoved (after move)");

    // --- Move from Function Return ---
    std::cout << "\n--- Move from Function Return ---\n";
    // The function creates a local FancyNameTag and returns it by value.
    // The compiler may use move construction or copy elision (NRVO) here.
    FancyNameTag fFromFunc = createFancyNameTag(4, "Umbrella", {"Diana", "Researcher", "Lab", 2023});
    // Print fFromFunc to see the result
    fFromFunc.print("fFromFunc");

    // All local variables are destroyed in reverse order when main() returns
    std::cout << "\n--- Destructors ---\n";
    return 0;
}
