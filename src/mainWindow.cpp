#include "mainWindow.h"


mainWindow::mainWindow(QWidget* parent)
    : QMainWindow(parent) {

    stdLogger.Debug("Loading utilities...");
    
    clipboard = QApplication::clipboard();
    fHandler = new FileHandler;
    searchEngine = new SearchEngine;

    hDialog = new helpDialog(this);
    
    setupUi(this);
    initAppearance();
    createActions();
    loadSettings();

    popup = new Popup(
        QString("✨ Welcome to %1! ✨")
        .arg(projectName),
        this
    );
    popup->show();
    initAnimation();
    seqGroup->start();
}

mainWindow::~mainWindow() {
    stdLogger.Debug("Saving configurations...");
    writeSettings();
    delete searchEngine;
    delete fHandler;
    stdLogger.Debug("Program exited normally.");
}

void mainWindow::import_dict() {
    QString fn = QFileDialog::getOpenFileName(
        this, "Import from...", ".", fileFilter
    );
    QString msg = QString("Dictionary imported: %1")
                    .arg(fn);
    if (fn.isEmpty()) return;
    if (!load(fn)) {
        QMessageBox::warning(
            this, projectName,
            QString("Failed to load: %1")
            .arg(fn)
        );
        return;
    }
    stdLogger.Debug(msg.toStdString().c_str());
    statusBar()->showMessage(msg, 2000);
}

void mainWindow::export_dict() {
    QString fn = QFileDialog::getSaveFileName(
        this, projectName, ".", fileFilter
    );
    QString msg = QString("Dictionary exported: %1")
                    .arg(fn);
    if (fn.isEmpty()) return;
    if (!save(fn)) {
        QMessageBox::warning(
            this, projectName,
            QString("Failed to save: %1")
            .arg(fn)
        );
        return;
    }
    stdLogger.Debug(msg.toStdString().c_str());
    statusBar()->showMessage(msg, 2000);
}

bool mainWindow::load(const QString& fn) {
    if (!fHandler->loadFromText(fn)) {
        stdLogger.Warning(
            QString(
                "Failed to load dictionary: %1. Check format or permission."
            ).arg(fn).toStdString().c_str()
        );
        return false;
    }
    QString key, value;
    while (fHandler->getWordPair(key, value)) {
        searchEngine->add(key + pairDelim + value);
    }
    return true;
}

bool mainWindow::save(const QString& fn) {
    return fHandler->saveAsText(fn);
}

void mainWindow::updateTable() {
    clearTableContentItems();
    QTableWidgetItem* item;

    strQueue res = searchEngine->findRelative(hintEdit->text());
    int realSize = res.length(), delimIdx;
    QString hint, target, tmp;
    targetTable->setRowCount(realSize);
    targetTable->insertRow(realSize);
    for (int i = 0; i < realSize; ++i) {
        tmp = res.deQueue();
        delimIdx = tmp.indexOf(pairDelim);
        hint = tmp.mid(0, delimIdx);
        target = tmp.mid(delimIdx + 1);
        item = new QTableWidgetItem(hint);
        targetTable->setItem(i, 0, item);
        item = new QTableWidgetItem(target);
        targetTable->setItem(i, 1, item);
    }
}

void mainWindow::clearTableContentItems() {
    /* Release all the nodes itself. */
    while (targetTable->rowCount() > 0) {
        targetTable->removeRow(0);
    }
}

void mainWindow::on_hintEdit_textChanged(const QString& text) {
    updateTable();
}

void mainWindow::on_targetTable_itemClicked(QTableWidgetItem* item) {
    int rowNum = item->row();
    QString target = targetTable->model()->index(rowNum, 1).data().toString();
    clipboard->setText(target);
    popup->setText(QString("Copied: %1").arg(target));
    seqGroup->start();
}

void mainWindow::on_targetTable_itemDoubleClicked(QTableWidgetItem* item) {
    on_targetTable_itemClicked(item);
    QTimer::singleShot(100, this, SLOT(close()));
}

void mainWindow::initAppearance() {
    setWindowTitle(projectName);

    loadStyleSheet();

    targetTable->setShowGrid(true);
    targetTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    targetTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    targetTable->setSortingEnabled(false);
    QHeaderView* targetVerticalHeader = targetTable->verticalHeader();
    targetVerticalHeader->setHidden(true);

    int wtLength = targetTableHeaders.length();
    targetTable->setColumnCount(wtLength);
    targetTable->setHorizontalHeaderLabels(targetTableHeaders);
    targetTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    targetTable->horizontalHeader()->setMinimumSectionSize(150);
    targetTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
}

void mainWindow::initAnimation() {

    animeIn = new QPropertyAnimation(popup, "geometry");
    animeIn->setStartValue(QRect(0, 0, width(), 0));
    animeIn->setEndValue(QRect(0, 0, width(), popupHeight));
    animeIn->setDuration(scrollInDuration);

    animeOut = new QPropertyAnimation(popup, "geometry");
    animeOut->setStartValue(QRect(0, 0, width(), popupHeight));
    animeOut->setEndValue(QRect(0, 0, width(), 0));
    animeOut->setDuration(scrollOutDuration);

    seqGroup = new QSequentialAnimationGroup(this);
    seqGroup->addAnimation(animeIn);
    seqGroup->addPause(defaultDuration);
    seqGroup->addAnimation(animeOut);
}

void mainWindow::createActions() {
    
    importAction->setIcon(QIcon(":/import.png"));
    importAction->setShortcut(QKeySequence::Open);
    importAction->setStatusTip(tr("Import dictionary from a text file."));
    connect(importAction, SIGNAL(triggered()), this, SLOT(import_dict()));

    exportAction->setIcon(QIcon(":/export.png"));
    exportAction->setShortcut(QKeySequence::SaveAs);
    exportAction->setStatusTip(tr("Export the dictionary to a text file."));
    connect(exportAction, SIGNAL(triggered()), this, SLOT(export_dict()));

    exitAction->setIcon(QIcon(":/exit.png"));
    exitAction->setShortcut(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit the application"));
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    // connect(helpMenu, SIGNAL(aboutToShow()), this, SLOT(help()));
    helpAction->setIcon(QIcon(":/help.png"));
    helpAction->setShortcut(QKeySequence::HelpContents);
    helpAction->setStatusTip(tr("Help contents"));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(help()));

    aboutQtAction->setStatusTip(tr("About Qt"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    aboutAuthorAction->setStatusTip(tr("About Author"));
    connect(aboutAuthorAction, SIGNAL(triggered()), this, SLOT(aboutAuthor()));
}

void mainWindow::loadStyleSheet() {
    QFile file(":/style.qss");
	if(file.open(QFile::ReadOnly)){
		QString styleSheet = QLatin1String(file.readAll());
    	this->setStyleSheet(styleSheet);
    	file.close();
	} else {
		QMessageBox::warning(
            0, projectName,
            "Failed to load page style sheet."
        );
        stdLogger.Warning(
            "Failed to load page style sheet."
        );
    }
}

void mainWindow::writeSettings() {
    QSettings settings("SJTU-XHW Inc.", projectName);
    settings.setValue("geometry", saveGeometry());
    save(builtinConfig);
}

void mainWindow::loadSettings() {
    QSettings settings("SJTU-XHW Inc.", projectName);
    restoreGeometry(settings.value("geometry").toByteArray());
    load(builtinConfig);
}

void mainWindow::help() {
    hDialog->exec();
}

void mainWindow::aboutAuthor() {
    QMessageBox::about(this, tr("About me & my program"),
    QString("<h2>%1</h2>"
        "<p>Copyright &copy; 2023 SJTU-XHW Inc. "
        "%1 is a small application that "
        "demonstrates numerous Qt classes, "
        "which is written by C++/Qt.</p>"
        "If you want to learn more about the application, or report a bug, "
        "please visit <a href='https://sjtuxhw.top/myBlog/'>my blog</a>"
        " or visit <a href='https://github.com/SSRVodka'>Github</a> :)")
        .arg(projectName)
    );
}
