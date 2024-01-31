/**
 * @file   fileHandler.h
 * @brief  The file handler utilities.
 * 
 * @author SJTU-XHW
 * @date   Jan 30, 2024
 */

#pragma once

#include "consts.h"
#include "logger.h"

class FileHandler {
public:
    FileHandler();
    ~FileHandler();

    void resetReadPtr() { index = 0; }
    void clearCache() { resetReadPtr(); lines.clear(); }

    /**
     * @brief Loads a text file (`*.txt`) as the dictionary.
     * 
     * The text file (dictionary in `*.txt`) should be in this format:
     * ```
     * 
     * <Target-Word1><delim><Hint-Word1>
     * <Target-Word2><delim><Hint-Word2>
     *     ...     <delim>     ...
     * 
     * ```
     * where `delim` is defined in `consts.h`.
     * 
     * @param filename The name of the text file.
     * @return If the operation is successful or not.
     * 
     * @note If the text file is in a wrong format / failed to read, it will return FALSE.
     */
    bool loadFromText(const QString& filename);

    /**
     * @brief Loads dictionary directly from a string.
     * 
     * @param rawString The string representing dictionary.
     * 
     * @see loadFromText
     */
    void loadFromString(const QString& rawString);

    /** 
     * @brief Saves current line buffer (`lines`) to a text file.
     * 
     * @param filename The target file name.
     * @return If the retrieve operation successful or not.
     */
    bool saveAsText(const QString& filename);

    /**
     * @brief Retrieves a pair of words from the current dictionary.
     * 
     * @param[out] key The key of the current word.
     * @param[out] value The value corresponding to `key`.
     * @return If the retrieve operation successful or not.
     *         If the end of the `rawFile` is reached, it will return FALSE.
     */
    bool getWordPair(QString& key, QString& value);

    // TODO: bool addWordPair(const QString& key, const QString& value);

private:
    /** @brief Buffer line of the file. */
    QStringList lines;
    /** @brief Current index of the line. */
    int         index;
};
