#pragma once

#include <string>
#include <vector>

/* Type aliases */

/// Shorter names for accepted path types.
using Path = const char*;
using String = std::string;

/// Type of the table storing the directory search.
template <typename T>
using Table = std::vector<std::pair<T, std::vector<T>>>;

/* Class interface */

class DirectoryReader
{
  public:
    /**
     * Constructors.
     * Their unique argument is the top directory path, given either as a
     * std::string, or as a "à la C" char*.
     */
    DirectoryReader(const Path& path = ".");
    DirectoryReader(const String& string = ".");

    /// Read the directory tree, and return the result as a string.
    std::string read_directory() const;

  private:
    /// Top directory path.
    const Path path_;

    /*
     * Return, as a vector of strings, all directories lying directly below a
     * given directory.
     * Hidden subdirectories (i.e., starting with ".") are discarded.
     * In case of failure (I/O error), do not throw any exception, but
     * return an empty vector instead.
     */
    static std::vector<String> subdirectories(const String& current_dir);

    /**
     * Store the directory search into a table, and return it.
     * Throw a std::error_condition exception if opening the top directory
     * fails.
     */
    Table<String> table() const;
};
