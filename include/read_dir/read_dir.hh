#pragma once

#include <string>
#include <vector>

// TODO: documentation

/* Type aliases */

/// Shorter names for some simple types.
using Path = const char*;
using String = std::string;

/// ???
template <typename T>
using Table = std::vector<std::pair<T, std::vector<T>>>;

/* Class interface */

class DirectoryReader
{
  public:
    /// ???
    DirectoryReader(const Path& path = ".");
    DirectoryReader(const String& string = ".");

    /// ???
    Table<String> table() const;

  private:
    /// Path corresponding to the topmost directory.
    const Path path_;

    /*
     * Return as a vector of strings all subdirectories from a directory.
     * Hidden subdirectories (i.e., starting with ".") are discarded.
     */
    static std::vector<String> subdirectories(const String& current_dir);
};
