// Include the FancyNameTag class (which also brings in Bio)
#include "FancyNameTag.h"
#include "NameTag.h"


#include <iostream>
#include <utility>

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

    // --- Default Move Constructor ---
    // See images/default_move.png for a visual diagram of what happens during a move.
    //
    // When would you use a move instead of a copy?
    //   - When the source object is temporary or about to be destroyed
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
    // Because bio_ is a raw pointer, we must implement:
    //   - Destructor (to free heap memory)
    //   - Copy constructor (deep copy to avoid shallow copy danger)
    //   - Move constructor (transfer ownership efficiently)
    // We've deleted the assignment operators to keep this example focused.
    // In modern C++, you'd use std::unique_ptr<Bio> instead of Bio*
    // and get all this behavior automatically — we'll cover that next.
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

    // All local variables are destroyed in reverse order when main() returns

    std::cout << "\n--- Destructors ---\n";
     
    return 0;
}
