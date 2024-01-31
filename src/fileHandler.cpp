#include "fileHandler.h"

FileHandler::FileHandler() {
    index = 0;
}

FileHandler::~FileHandler() {
    
}

bool FileHandler::loadFromText(const QString& filename) {
    QFile rawFile(filename);
    /* Create file if not exists. */
    if (!rawFile.exists()) {
        rawFile.open(QIODevice::WriteOnly);
        rawFile.close();
    }
    if (!rawFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream stream(&rawFile);
    QString contents = stream.readAll();

    loadFromString(contents);

    rawFile.close();
    return true;
}

void FileHandler::loadFromString(const QString& rawString) {
    int start = lines.length(), stop;
    lines.append(rawString.split('\n'));
    stop = lines.length();
    for (int i = start; i < stop; ++i) {
        lines[i] = lines[i].trimmed();
    }
    lines.removeAll("");
    lines.removeDuplicates();
}

bool FileHandler::saveAsText(const QString& filename) {
    QFile rawFile(filename);
    if (!rawFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        return false;
    foreach (QString line, lines) {
        rawFile.write(line.toStdString().c_str());
        rawFile.write("\n");
    }
    rawFile.close();
    return true;
}

bool FileHandler::getWordPair(QString& key, QString& value) {
    if (index >= lines.length()) return false;

    QString curWord = lines[index];
    int sp = curWord.indexOf(pairDelim);
    value = curWord.mid(0, sp);
    if (sp > 0) key = curWord.mid(sp + 1);
    else {
        key = undefinedKey;
        stdLogger.Warning(
            QString("Imported '%1' with no key.")
            .arg(value).toStdString().c_str()
        );
    }
    ++index;

    return true;
}
