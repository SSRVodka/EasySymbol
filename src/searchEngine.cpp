#include <stdlib.h>

#include "searchEngine.h"

bool isStartsWith(const char* src, const char* prefix) {
    if (prefix == nullptr) return true;
    else if (src == nullptr) return false;
    int i;
    for (i = 0; src[i] && prefix[i]; ++i) {
        if (src[i] != prefix[i]) return false;
    }
    return prefix[i] == 0;
}

/**
 * @brief Computes the longest proper prefix which is also a suffix.
 * 
 * @param pattern The pattern string.
 * @param patternLength The length of the pattern string.
 * @param lps The array holds the longest prefix suffix.
 */
static void computeLPS(const QString &pattern, int *lps) {
    int len = 0, patternLength = pattern.length();
    lps[0] = 0;
    int i = 1;

    while (i < patternLength) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMPSearch(const QString &parent, const QString &substring) {

    int parentLength = parent.length();
    int substringLength = substring.length();

    if (substringLength > parentLength) {
        return -1;
    }

    int *lps = (int *)malloc(substringLength * sizeof(int));
    if (lps == NULL) {
        // Memory allocation failed
        return -1;
    }

    computeLPS(substring, lps);

    int i = 0;  // Index for parent string
    int j = 0;  // Index for substring

    while (i < parentLength) {
        if (substring[j] == parent[i]) {
            i++;
            j++;
        }

        if (j == substringLength) {
            // Substring found
            free(lps);
            return i - j;
        } else if (i < parentLength && substring[j] != parent[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    // Substring not found
    free(lps);
    return -1;
}


SearchEngine::SearchEngine() {

}

SearchEngine::~SearchEngine() {

}

bool SearchEngine::add(const QString &word) {
    QString wordStr = word, tmpStr;
    int wordLength = wordStr.length(), tmpLength;
    bool flag;
    strList::iterator iter = srcList.begin();
    for (; iter != srcList.end(); ++iter) {
        flag = true;
        tmpStr = *iter;
        tmpLength = tmpStr.length();
        for (int j = 0; tmpStr[j].unicode() && wordStr[j].unicode(); ++j) {
            if (tmpStr[j] < wordStr[j]) {
                flag = false;
                break;
            } else if (tmpStr[j] > wordStr[j]) {
                srcList.insert(iter, wordStr);
                return true;
            }
        }
        if (flag) {
            /* find a same word. */
            if (tmpLength == wordLength)
                return false;
            /* `tmpStr` starts with `wordStr`. */
            else if (tmpLength > wordLength) {
                srcList.insert(iter, wordStr);
                return true;
            }
            /* else: `wordStr` starts with `tmpStr`. */
        }
    }
    srcList.push_back(wordStr);
    return true;
}

bool SearchEngine::del(const QString &word) {
    strList::iterator iter = srcList.begin();
    for (; iter != srcList.end(); ++iter) {
        if (!(*iter).compare(word)) {
            srcList.erase(iter);
            return true;
        }
    }
    return false;
}

strQueue SearchEngine::findRelative(const QString &pattern) {
    strQueue startsWithMatch, fuzzyMatch;
    
    for (QString item : srcList) {
        
        if (item.startsWith(pattern))
            startsWithMatch.enQueue(item);
        else if (KMPSearch(item, pattern) != -1)
            fuzzyMatch.enQueue(item);
    }
    while (!fuzzyMatch.isempty())
        startsWithMatch.enQueue(fuzzyMatch.deQueue());
    return startsWithMatch;
}
