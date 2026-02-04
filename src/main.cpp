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

    // Create original with id=1, name="Waldo", and company="Weber State University"

    NameTag original(1, "Waldo", "Weber State University");

    // Print original to see its initial state

    original.print("original");

    // --- Default Copy Constructor ---

    std::cout << "\n--- Default Copy Constructor ---\n";

    // Create copied as a copy of original using the compiler-generated copy constructor

    NameTag copied(original);

    // Print original first to verify it was not modified by the copy

    original.print("original", "unchanged");

    // Print copied to verify it has the same values as original

    copied.print("copied");

    // --- Modify the copy to prove independence ---

    std::cout << "\n--- Modify Copy (prove independence) ---\n";

    // Change the copy's id, name, and company to prove this is a separate object

    copied.setId(2);
    copied.setName("Scott");
    copied.setCompany("The School of Computing");

    // Print original first — it should still have id=1, name="Waldo", company="Weber State University"

    original.print("original", "still unchanged");

    // Print copied — it should now have id=2, name="Scott", company="The School of Computing"

    copied.print("copied", "modified");

    // --- Default Copy Assignment ---
    // See images/default_copy_assignment.png for a visual diagram.
    //
    // Copy ASSIGNMENT differs from copy CONSTRUCTOR:
    //   - Copy constructor: creates a NEW object as a copy     -> NameTag b(a);
    //   - Copy assignment:  overwrites an EXISTING object       -> b = a;
    // The key difference is that assignment must deal with the object's old data first.
    //
    // Real-world scenario: Scott already has a badge from "The School of Computing",
    // but he transfers to Waldo's department. Instead of creating a new badge,
    // we overwrite Scott's existing badge with Waldo's data. That's assignment.

    std::cout << "\n--- Default Copy Assignment ---\n";

    // "copied" is Scott (id=2) from the prove independence section above
    // Print copied BEFORE assignment to see Scott's current data

    copied.print("copied", "before");

    // Print original to see the source data we're copying from (Waldo)

    original.print("original", "source");

    // Use the compiler-generated copy assignment operator to overwrite copied with original's data
    // Scott's badge now gets Waldo's credentials — same as creating a fresh copy, but on an existing object

    copied = original;

    // Print original first to verify it was not modified by the assignment

    std::cout << "\n";
    original.print("original", "unchanged");

    // Print copied to verify it was overwritten with Waldo's data

    copied.print("copied", "after");

    // --- Default Move Constructor ---
    // See images/default_move.png for a visual diagram of what happens during a move.
    //
    // When would you use a move instead of a copy?
    //   - When the source object is temporary or about to be destroyed
    //   - When you're transferring ownership (e.g., returning from a function)
    //   - When copying is expensive (large strings, heap data) and you don't need the original anymore
    // For NameTag (stack-only), move and copy behave the same — the compiler just copies each member.
    // The real benefit of move shows up in Part 2 (FancyNameTag) where it avoids a heap allocation.

    std::cout << "\n--- Default Move Constructor ---\n";

    // Print original BEFORE the move so we can compare before and after

    original.print("original", "before move");

    // std::move casts original to an rvalue reference, enabling the move constructor

    NameTag moved(std::move(original));

    // Print original AFTER the move — the source is now in a "valid but unspecified" state.
    // Notice what happened to each member:
    //   - id_ (int): still has its value. Primitive types are just copied — there's
    //     nothing to "steal," so the original keeps its value.
    //   - name_ and company_ (std::string): likely empty now. std::string stores its
    //     characters on the heap internally. Moving a string transfers (steals) that
    //     heap buffer to the new string, leaving the source empty.
    // This is why move matters: it avoids copying heap data by transferring ownership.

    original.print("original", "after move");

    // Print moved to verify it received original's values

    moved.print("moved");

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

    FancyNameTag fOriginal(1, "Weber State University", {"Scott", "Professor", "Computer Science", 2010});

    // Print fOriginal to see its initial state and heap address

    fOriginal.print("fOriginal");

    // --- Copy Constructor (deep copy) ---

    std::cout << "\n--- Copy Constructor (deep copy) ---\n";

    // Create fCopied as a deep copy of fOriginal - a NEW Bio is allocated on the heap

    FancyNameTag fCopied(fOriginal);

    // Print fOriginal first to verify it was not modified by the copy

    fOriginal.print("fOriginal", "unchanged");

    // Print fCopied to verify it has the same data but a DIFFERENT heap address

    fCopied.print("fCopied");

    // --- Modify the copy to prove independence ---

    std::cout << "\n--- Modify Copy (prove independence) ---\n";

    // Change the copy's id using the setter to give it a unique identifier

    fCopied.setId(2);

    // Print fOriginal first — it should still have id=1

    fOriginal.print("fOriginal", "still unchanged");

    // Print fCopied — it should now have id=2
    // Notice the heap address is still the same as before (we only changed id, not bio)

    fCopied.print("fCopied", "modified");

    // --- Copy Assignment ---
    // Copy ASSIGNMENT differs from copy CONSTRUCTOR:
    //   - Copy constructor: creates a NEW object as a copy     -> FancyNameTag b(a);
    //   - Copy assignment:  overwrites an EXISTING object       -> b = a;
    // For FancyNameTag, assignment must DELETE the old Bio before allocating a new one.
    // This is critical: if we didn't delete the old Bio, we'd leak heap memory.

    std::cout << "\n--- Copy Assignment ---\n";

    // Create fAssigned with its own different data

    FancyNameTag fAssigned(2, "The School of Computing", {"Pat", "Advisor", "Student Services", 2008});

    // Print fAssigned BEFORE assignment to see its original data and heap address

    fAssigned.print("fAssigned", "before");

    // Print fOriginal to see the source data we're copying from

    fOriginal.print("fOriginal", "source");

    // Copy assignment: fAssigned's old Bio is deleted, a new one is allocated with fOriginal's data

    fAssigned = fOriginal;

    // Print fOriginal first to verify it was not modified

    fOriginal.print("fOriginal", "unchanged");

    // Print fAssigned to verify its data was overwritten — notice a NEW heap address

    fAssigned.print("fAssigned", "after");

    // --- Move Constructor (transfer ownership) ---

    std::cout << "\n--- Move Constructor (transfer ownership) ---\n";

    // std::move casts fOriginal to an rvalue reference, enabling the move constructor
    // 
    // The move constructor steals fOriginal's Bio pointer instead of allocating new memory

    FancyNameTag fMoved(std::move(fOriginal));

    // Print fOriginal first to verify its bio_ is now nullptr (it was moved from)

    fOriginal.print("fOriginal", "after move");

    // Print fMoved to verify it has fOriginal's data at the SAME heap address

    fMoved.print("fMoved");

    // --- Move Assignment ---

    std::cout << "\n--- Move Assignment ---\n";

    // Create fMoveAssigned with its own data

    FancyNameTag fMoveAssigned(3, "Computer Science Program", {"Charlie", "Lecturer", "Software Engineering", 2018});

    // Move assignment: fMoveAssigned's old Bio is deleted, then it steals fMoved's Bio pointer

    fMoveAssigned = std::move(fMoved);

    // Print fMoved first to verify its bio_ is now nullptr

    fMoved.print("fMoved", "after move");

    // Print fMoveAssigned to verify it took fMoved's data

    fMoveAssigned.print("fMoveAssigned");

    // --- Move from Function Return ---

    std::cout << "\n--- Move from Function Return ---\n";

    // The function creates a local FancyNameTag and returns it by value.
    // 
    // The compiler may use move construction or copy elision (NRVO) here.

    FancyNameTag fFromFunc = createFancyNameTag(4, "Weber State University", {"Diana", "Research Assistant", "Data Science", 2023});
    
    // Print fFromFunc to see the result

    fFromFunc.print("fFromFunc");

    // All local variables are destroyed in reverse order when main() returns

    std::cout << "\n--- Destructors ---\n";
     
    return 0;
}
