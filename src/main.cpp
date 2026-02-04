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

    // TODO: Create a NameTag called "original" with id=1, name="Waldo",
    //       and company="Weber State University"


    // TODO: Print original to see its initial state
    //       Hint: original.print("original");


    // --- Default Copy Constructor ---

    std::cout << "\n--- Default Copy Constructor ---\n";

    // TODO: Create a NameTag called "copied" as a copy of original
    //       using the compiler-generated copy constructor
    //       Hint: NameTag copied(original);


    // TODO: Print original first to verify it was not modified by the copy
    //       Hint: use print("original", "unchanged")


    // TODO: Print copied to verify it has the same values as original
    //       Hint: use print("copied")


    // --- Modify the copy to prove independence ---

    std::cout << "\n--- Modify Copy (prove independence) ---\n";

    // TODO: Change the copy's id to 2, name to "Scott",
    //       and company to "The School of Computing"
    //       to prove this is a separate object


    // TODO: Print original first — it should still have id=1, name="Waldo",
    //       company="Weber State University"
    //       Hint: use print("original", "still unchanged")


    // TODO: Print copied — it should now have id=2, name="Scott",
    //       company="The School of Computing"
    //       Hint: use print("copied", "modified")


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
    // TODO: Print copied BEFORE assignment to see Scott's current data
    //       Hint: use print("copied", "before")


    // TODO: Print original to see the source data we're copying from (Waldo)
    //       Hint: use print("original", "source")


    // TODO: Use the compiler-generated copy assignment operator to overwrite
    //       copied with original's data
    //       Hint: copied = original;


    // TODO: Print original first to verify it was not modified by the assignment
    //       Hint: std::cout << "\n"; then use print("original", "unchanged")

    std::cout << "\n";

    // TODO: Print copied to verify it was overwritten with Waldo's data
    //       Hint: use print("copied", "after")


    // --- Default Move Constructor ---
    // See images/default_move.png for a visual diagram of what happens during a move.
    //
    // When would you use a move instead of a copy?
    //   - When the source object is temporary or about to be destroyed
    //   - When copying is expensive (large strings, heap data) and you don't need the original anymore
    // For NameTag (stack-only), move and copy behave the same — the compiler just copies each member.
    // The real benefit of move shows up in Part 2 (FancyNameTag) where it avoids a heap allocation.

    std::cout << "\n--- Default Move Constructor ---\n";

    // TODO: Print original BEFORE the move so we can compare before and after
    //       Hint: use print("original", "before move")


    // TODO: Create a NameTag called "moved" using std::move(original) to invoke
    //       the compiler-generated move constructor
    //       Hint: NameTag moved(std::move(original));


    // Print original AFTER the move — the source is now in a "valid but unspecified" state.
    // Notice what happened to each member:
    //   - id_ (int): still has its value. Primitive types are just copied — there's
    //     nothing to "steal," so the original keeps its value.
    //   - name_ and company_ (std::string): likely empty now. std::string stores its
    //     characters on the heap internally. Moving a string transfers (steals) that
    //     heap buffer to the new string, leaving the source empty.
    // This is why move matters: it avoids copying heap data by transferring ownership.

    // TODO: Print original AFTER the move to see the "moved-from" state
    //       Hint: use print("original", "after move")


    // TODO: Print moved to verify it received original's values
    //       Hint: use print("moved")


    // -------------------------------------------------------
    // Part 2: FancyNameTag (heap resource, custom copy/move)
    // We must implement the Rule of Five because bio_ is a raw pointer.
    // -------------------------------------------------------

    std::cout << "\n========================================\n";
    std::cout << " Part 2: FancyNameTag (custom copy/move)\n";
    std::cout << "========================================\n\n";

    // --- Construct a FancyNameTag ---

    std::cout << "--- Construct ---\n";

    // TODO: Create a FancyNameTag called "fOriginal" with id=1,
    //       company="Weber State University", and a Bio using aggregate initialization:
    //       {"Scott", "Professor", "Computer Science", 2010}


    // TODO: Print fOriginal to see its initial state and heap address
    //       Hint: fOriginal.print("fOriginal");


    // --- Copy Constructor (deep copy) ---

    std::cout << "\n--- Copy Constructor (deep copy) ---\n";

    // TODO: Create a FancyNameTag called "fCopied" as a deep copy of fOriginal
    //       A NEW Bio is allocated on the heap
    //       Hint: FancyNameTag fCopied(fOriginal);


    // TODO: Print fOriginal first to verify it was not modified by the copy
    //       Hint: use print("fOriginal", "unchanged")


    // TODO: Print fCopied to verify it has the same data but a DIFFERENT heap address
    //       Hint: use print("fCopied")


    // --- Modify the copy to prove independence ---

    std::cout << "\n--- Modify Copy (prove independence) ---\n";

    // TODO: Change the copy's id to 2 using the setter to give it a unique identifier


    // TODO: Print fOriginal first — it should still have id=1
    //       Hint: use print("fOriginal", "still unchanged")


    // TODO: Print fCopied — it should now have id=2
    //       Notice the heap address is still the same as before (we only changed id, not bio)
    //       Hint: use print("fCopied", "modified")


    // --- Copy Assignment ---
    // Copy ASSIGNMENT differs from copy CONSTRUCTOR:
    //   - Copy constructor: creates a NEW object as a copy     -> FancyNameTag b(a);
    //   - Copy assignment:  overwrites an EXISTING object       -> b = a;
    // For FancyNameTag, assignment must DELETE the old Bio before allocating a new one.
    // This is critical: if we didn't delete the old Bio, we'd leak heap memory.

    std::cout << "\n--- Copy Assignment ---\n";

    // TODO: Create a FancyNameTag called "fAssigned" with id=2,
    //       company="The School of Computing", and Bio:
    //       {"Pat", "Advisor", "Student Services", 2008}


    // TODO: Print fAssigned BEFORE assignment to see its original data and heap address
    //       Hint: use print("fAssigned", "before")


    // TODO: Print fOriginal to see the source data we're copying from
    //       Hint: use print("fOriginal", "source")


    // TODO: Use the copy assignment operator to overwrite fAssigned with fOriginal's data
    //       fAssigned's old Bio is deleted, a new one is allocated with fOriginal's data
    //       Hint: fAssigned = fOriginal;


    // TODO: Print fOriginal first to verify it was not modified
    //       Hint: use print("fOriginal", "unchanged")


    // TODO: Print fAssigned to verify its data was overwritten — notice a NEW heap address
    //       Hint: use print("fAssigned", "after")


    // --- Move Constructor (transfer ownership) ---

    std::cout << "\n--- Move Constructor (transfer ownership) ---\n";

    // TODO: Create a FancyNameTag called "fMoved" using std::move(fOriginal)
    //       std::move casts fOriginal to an rvalue reference, enabling the move constructor
    //       The move constructor steals fOriginal's Bio pointer instead of allocating new memory
    //       Hint: FancyNameTag fMoved(std::move(fOriginal));


    // TODO: Print fOriginal first to verify its bio_ is now nullptr (it was moved from)
    //       Hint: use print("fOriginal", "after move")


    // TODO: Print fMoved to verify it has fOriginal's data at the SAME heap address
    //       Hint: use print("fMoved")


    // --- Move Assignment ---

    std::cout << "\n--- Move Assignment ---\n";

    // TODO: Create a FancyNameTag called "fMoveAssigned" with id=3,
    //       company="Computer Science Program", and Bio:
    //       {"Charlie", "Lecturer", "Software Engineering", 2018}


    // TODO: Use the move assignment operator to steal fMoved's resources
    //       fMoveAssigned's old Bio is deleted, then it steals fMoved's Bio pointer
    //       Hint: fMoveAssigned = std::move(fMoved);


    // TODO: Print fMoved first to verify its bio_ is now nullptr
    //       Hint: use print("fMoved", "after move")


    // TODO: Print fMoveAssigned to verify it took fMoved's data
    //       Hint: use print("fMoveAssigned")


    // All local variables are destroyed in reverse order when main() returns

    std::cout << "\n--- Destructors ---\n";

    return 0;
}
