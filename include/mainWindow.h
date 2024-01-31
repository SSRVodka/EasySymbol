#pragma once

#include "consts.h"
#include "fileHandler.h"
#include "searchEngine.h"
#include "logger.h"
#include "popup.h"

#include "ui_mainWindow.h"

class mainWindow : public QMainWindow, public Ui::mainWindow {
    Q_OBJECT
public:
    mainWindow(QWidget* parent = 0);
    ~mainWindow();
private:
    void initAppearance();
    void loadStyleSheet();
    void createActions();

    void loadSettings();
    void writeSettings();

    bool load(const QString& filename);
    bool save(const QString& filename);

    void updateTable();
    void clearTableContentItems();

    void initAnimation();

    QClipboard* clipboard;

    Popup* popup;
    FileHandler* fHandler;
    SearchEngine* searchEngine;

    QPropertyAnimation* animeIn;
    QPropertyAnimation* animeOut;

    QSequentialAnimationGroup* seqGroup;

private slots:

    void on_hintEdit_textChanged(const QString& text);
    void on_targetTable_itemDoubleClicked(QTableWidgetItem* item);

    /* Common Actions */
    void import_dict();
    void export_dict();
    void help();
    void aboutAuthor();
};
