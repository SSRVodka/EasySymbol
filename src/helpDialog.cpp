#include <QtCore/QTextStream>
#include <QtCore/QUrl>


#include "helpDialog.h"

helpDialog::helpDialog(QWidget* parent)
    : QDialog(parent) {
    setupUi(this);

    txt = new QFile(":/docs/README.html");
    txt->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream out(txt);
    out.setCodec("UTF-8");
    helpBrowser->setHtml(out.readAll());
}

helpDialog::~helpDialog() {
    txt->close();
    delete txt;
}

