/**
 * @file   searchEngine.h
 * @brief  The search engine implemented KMP algorithm.
 * 
 * @author SJTU-XHW
 * @date   Jan 30, 2024
 */

#pragma once

#include "consts.h"
#include "utils.h"

typedef QVector<QString> strList;
typedef seqQueue<QString> strQueue;

/**
 * @brief Finds substring using KMP algorithm.
 * 
 * @param parent    The source string.
 * @param substring The pattern string.
 * 
 * @return The index of `parent` where `substring` occurs.
 *         If `substring` never occurs in `parent`, then return -1.
 */
int KMPSearch(const QString &parent, const QString &substring);

/** 
 * @class SearchEngine
 * @brief Search engine for the project.
 * 
 */

class SearchEngine {
public:
    SearchEngine();
    ~SearchEngine();

    /** 
     * @brief Adds an entry to the search engine.
     * 
     * @param word The entry.
     * @return If the operation is successful.
     *         If the `word` can be found in the engine, then return FALSE.
     */
    bool add(const QString &word);
    /** 
     * @brief Removes an entry in the search engine.
     * 
     * @param word The entry.
     * @return If the operation is successful.
     *         If the `word` cannot be found in the engine, then return FALSE.
     */
    bool del(const QString &word);

    /**
     * @brief Finds the entries similiar to `pattern`.
     * 
     * @param pattern The specific pattern string.
     * @return An <b>ordered</b> entry list including:
     *       - Entries start with `pattern`;
     *       - Entries contain `pattern`.
     */
    strQueue findRelative(const QString &pattern);

private:
    /** @brief Ordered entry list. */
    strList srcList;
};
