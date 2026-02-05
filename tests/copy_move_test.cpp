#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "Bio.h"
#include "NameTag.h"
#include "FancyNameTag.h"

// ==================== Bio Struct Tests (4 points) ====================

TEST(BioTest, MembersAreAccessible) {
    Bio b{"Scott", "Professor", "Computer Science", 2010};
    EXPECT_EQ(b.name, "Scott");
    EXPECT_EQ(b.title, "Professor");
    EXPECT_EQ(b.department, "Computer Science");
    EXPECT_EQ(b.year, 2010);
}

TEST(BioTest, PrintOutputsInfo) {
    Bio b{"Scott", "Professor", "Computer Science", 2010};

    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    b.print();
    std::cout.rdbuf(oldCout);

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("Scott") != std::string::npos)
        << "print() should output the name";
    EXPECT_TRUE(output.find("Professor") != std::string::npos)
        << "print() should output the title";
}

// ==================== NameTag Constructor Tests (4 points) ====================

TEST(NameTagTest, ConstructorSetsId) {
    NameTag tag(1, "Waldo", "Weber State Univ.");
    EXPECT_EQ(tag.getId(), 1);
}

TEST(NameTagTest, ConstructorSetsName) {
    NameTag tag(1, "Waldo", "Weber State Univ.");
    EXPECT_EQ(tag.getName(), "Waldo");
}

// ==================== NameTag Default Copy Constructor (4 points) ====================

TEST(NameTagTest, CopyConstructorCopiesId) {
    NameTag original(1, "Waldo", "Weber State Univ.");
    NameTag copied(original);
    EXPECT_EQ(copied.getId(), 1);
}

TEST(NameTagTest, CopyConstructorCopiesName) {
    NameTag original(1, "Waldo", "Weber State Univ.");
    NameTag copied(original);
    EXPECT_EQ(copied.getName(), "Waldo");
}

// ==================== FancyNameTag Constructor (4 points) ====================

TEST(FancyNameTagTest, ConstructorSetsId) {
    Bio bio{"Scott", "Professor", "Computer Science", 2010};
    FancyNameTag tag(1, "Weber State Univ.", bio);
    EXPECT_EQ(tag.getId(), 1);
}

TEST(FancyNameTagTest, ConstructorSetsCompany) {
    Bio bio{"Scott", "Professor", "Computer Science", 2010};
    FancyNameTag tag(1, "Weber State Univ.", bio);
    EXPECT_EQ(tag.getCompany(), "Weber State Univ.");
}

// ==================== FancyNameTag Destructor (2 points) ====================

TEST(FancyNameTagTest, DestructorDoesNotCrash) {
    // Construct and destroy — if destructor is broken, this crashes or leaks
    Bio bio{"Scott", "Professor", "Computer Science", 2010};
    FancyNameTag* tag = new FancyNameTag(1, "Weber State Univ.", bio);
    EXPECT_NO_THROW(delete tag);
}

// ==================== FancyNameTag Copy Constructor (6 points) ====================

TEST(FancyNameTagTest, CopyConstructorCopiesId) {
    Bio bio{"Scott", "Professor", "Computer Science", 2010};
    FancyNameTag original(1, "Weber State Univ.", bio);
    FancyNameTag copied(original);
    EXPECT_EQ(copied.getId(), 1);
}

TEST(FancyNameTagTest, CopyConstructorCopiesCompany) {
    Bio bio{"Scott", "Professor", "Computer Science", 2010};
    FancyNameTag original(1, "Weber State Univ.", bio);
    FancyNameTag copied(original);
    EXPECT_EQ(copied.getCompany(), "Weber State Univ.");
}

TEST(FancyNameTagTest, CopyConstructorDeepCopiesBio) {
    Bio bio{"Scott", "Professor", "Computer Science", 2010};
    FancyNameTag original(1, "Weber State Univ.", bio);
    FancyNameTag copied(original);

    // Bio data should match
    EXPECT_EQ(copied.getBio().name, "Scott");
    EXPECT_EQ(copied.getBio().department, "Computer Science");

    // But the Bio objects must be at DIFFERENT addresses (deep copy)
    EXPECT_NE(&original.getBio(), &copied.getBio())
        << "Copy constructor must allocate a NEW Bio on the heap (deep copy), "
           "not share the same Bio (shallow copy)";
}

// ==================== FancyNameTag Move Constructor (8 points) ====================

TEST(FancyNameTagTest, MoveConstructorTransfersId) {
    Bio bio{"Scott", "Professor", "Computer Science", 2010};
    FancyNameTag original(1, "Weber State Univ.", bio);
    FancyNameTag moved(std::move(original));
    EXPECT_EQ(moved.getId(), 1);
}

TEST(FancyNameTagTest, MoveConstructorTransfersCompany) {
    Bio bio{"Scott", "Professor", "Computer Science", 2010};
    FancyNameTag original(1, "Weber State Univ.", bio);
    FancyNameTag moved(std::move(original));
    EXPECT_EQ(moved.getCompany(), "Weber State Univ.");
}

TEST(FancyNameTagTest, MoveConstructorTransfersBio) {
    Bio bio{"Scott", "Professor", "Computer Science", 2010};
    FancyNameTag original(1, "Weber State Univ.", bio);

    // Capture the Bio address before the move
    const Bio* originalBioAddr = &original.getBio();

    FancyNameTag moved(std::move(original));

    // The moved object should have the SAME Bio pointer (stolen, not copied)
    EXPECT_EQ(&moved.getBio(), originalBioAddr)
        << "Move constructor should transfer the Bio pointer, not allocate a new one";
}

TEST(FancyNameTagTest, MoveConstructorSetsSourceBioToNullptr) {
    Bio bio{"Scott", "Professor", "Computer Science", 2010};
    FancyNameTag original(1, "Weber State Univ.", bio);
    FancyNameTag moved(std::move(original));

    // The moved-from object's destructor must not crash
    // (bio_ should be nullptr so delete does nothing)
    // We verify indirectly: if this test completes without crashing, it works
    EXPECT_EQ(moved.getBio().name, "Scott");
}

// ==================== Copy Independence (2 points) ====================

TEST(FancyNameTagTest, CopyConstructorIsIndependent) {
    Bio bio{"Scott", "Professor", "Computer Science", 2010};
    FancyNameTag original(1, "Weber State Univ.", bio);
    FancyNameTag copied(original);

    // Modify original after copying
    original.setId(99);
    original.setCompany("Changed");

    // Copied should be unaffected
    EXPECT_EQ(copied.getId(), 1)
        << "Modifying the original should not affect the copy";
    EXPECT_EQ(copied.getCompany(), "Weber State Univ.")
        << "Modifying the original should not affect the copy";
}

// ==================== Setter Validation (4 points) ====================

TEST(FancyNameTagTest, SetIdRejectsZero) {
    Bio bio{"Scott", "Professor", "Computer Science", 2010};
    FancyNameTag tag(1, "Weber State Univ.", bio);
    EXPECT_THROW(tag.setId(0), std::invalid_argument);
}

TEST(FancyNameTagTest, SetCompanyRejectsEmpty) {
    Bio bio{"Scott", "Professor", "Computer Science", 2010};
    FancyNameTag tag(1, "Weber State Univ.", bio);
    EXPECT_THROW(tag.setCompany(""), std::invalid_argument);
}
