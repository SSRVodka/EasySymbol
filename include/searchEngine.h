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

// /**
//  * @brief Check the prefix of a string.
//  * 
//  * @param src The source string.
//  * @param prefix The prefix string.
//  * 
//  * @return If `prefix` is a prefix of `src`.
//  */
// bool isStartsWith(const QString& src, const QString& prefix);

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


class SearchEngine {
public:
    SearchEngine();
    ~SearchEngine();

    bool add(const QString &word);
    bool del(const QString &word);

    strQueue findRelative(const QString &pattern);

private:
    strList srcList;
};
