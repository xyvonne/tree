#pragma once

#include <string>
#include <vector>

/**
 * This class is the core of our directory search program. An instance of it
 * is constructed from the top directory path (i.e., the directory which
 * all subdirectories are to be read from).
 * Upon success, the reading yields a table, which is actually a vector of
 * (key, value) pairs; here, a key is a directory currently being read, and a
 * value is its corresponding vector of (direct) subdirectories.
 * In this table, directories are stored as strings in the following format:
 * root_path/subdir/subsubdir/... Keeping the whole names makes the keys
 * pairwise distinct.
 * If an (I/O) error occurs upon reading the top directory, an
 * std::error_condition is thrown. If a similar error later occurs, no
 * exception is thrown, and an undefined behavior results; most of the
 * times, the result will be valid, but incomplete.
 * Once the table is built, the last part of the job is made by the
 * "rd.cc" file. This table can be directly passed to a Tree constructor,
 * and the resulting tree can be easily pretty-printed with the
 * Tree::to_string() method, yielding the desired result.
 */

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
