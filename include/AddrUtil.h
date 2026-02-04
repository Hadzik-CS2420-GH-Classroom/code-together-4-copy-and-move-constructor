// Header guard - prevents this file from being included more than once
#pragma once

// sstream for std::ostringstream (building strings from non-string types)
#include <sstream>
// string for std::string
#include <string>

// Converts any pointer to a short hex string (last 5 hex characters).
// This makes console output easier to read by trimming the leading zeros
// that are common on 64-bit systems.
//
// Example: 0x00007FFD3A2B1C80 -> "B1C80"
//
// Works on any OS and pointer size — we just take the last 5 characters
// of the full hex address, which is enough to tell addresses apart.
inline std::string shortAddr(const void* ptr) {
    // Convert the pointer to a hex string using a string stream
    std::ostringstream oss;
    oss << ptr;
    std::string full = oss.str();
    // Take the last 5 characters (or the whole string if shorter)
    const std::size_t len = 5;
    if (full.size() <= len) {
        return full;
    }
    return full.substr(full.size() - len);
}
