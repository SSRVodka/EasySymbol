#pragma once
#include <QtCore/QFile>
#include <QtWidgets/QDialog>
#include "ui_helpDialog.h"

class helpDialog : public QDialog, public Ui::helpDialog {
    Q_OBJECT
public:
    helpDialog(QWidget* parent = nullptr);
    ~helpDialog();
private:
    QFile* txt;
    QString buf;
};
