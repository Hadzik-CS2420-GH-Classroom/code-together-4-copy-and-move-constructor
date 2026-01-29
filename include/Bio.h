// Header guard - prevents this file from being included more than once
#pragma once

// iostream for std::cout in print()
#include <iostream>
// string for std::string members
#include <string>

// Bio is a struct - a way to group related data together.
//
// struct vs class:
//   - In a struct, members are PUBLIC by default.
//   - In a class, members are PRIVATE by default.
//   - That is the ONLY difference in C++.
//   - By convention, we use struct for simple data holders (like this one)
//     and class when we need encapsulation (private data + public methods).
//
// A struct can have member functions, constructors, and everything a class can.
// We use a struct here because Bio is just a plain bundle of data with a
// convenience print function - there's no invariant to protect.
struct Bio {
    // All members below are public by default (no "public:" needed in a struct)

    std::string name;       // person's name
    std::string title;      // job title
    std::string department; // department they belong to
    int year;               // year they joined

    // A struct can have member functions just like a class.
    // const means this function does not modify any members.
    // Prints all Bio fields to the console, separated by commas.
    void print() const;
};
