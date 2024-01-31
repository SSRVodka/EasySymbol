#pragma once

#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QtCore/QFile>
#include <QtCore/QSettings>
#include <QtCore/QTextStream>
#include <QtCore/QVector>

#include <QtGui/QPen>
#include <QtGui/QPainter>

#include <QtWidgets/QTableWidget>
#include <QtWidgets/QHeaderView>

#include <QtCore/QTimer>

#include <QtCore/QPropertyAnimation>
#include <QtCore/QSequentialAnimationGroup>

#include <QtGui/QClipboard>

#define projectName "MySymbol"

#define pairDelim ' '
#define fileFilter "text file (*.txt)"

#define builtinConfig ".dict"

#define undefinedKey "undefined"

/* Unit: Millisecond */
const int defaultDuration = 2000;
const int scrollInDuration = 300;
const int scrollOutDuration = 300;

const int popupHeight = 40;

const double maxOpacity = 1.0;

const QStringList targetTableHeaders = {
    "Hint", "Target"
};
