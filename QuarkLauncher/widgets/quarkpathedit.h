#ifndef QUARKPATHEDIT_H
#define QUARKPATHEDIT_H

#include <QWidget>
#include <QFileDialog>
#include <QStandardPaths>

#include "quarklineedit.h"

namespace Ui {
class QuarkPathEdit;
}

class QuarkPathEdit : public QWidget, public QuarkEnv
{
    Q_OBJECT

public:
    explicit QuarkPathEdit(QWidget *parent = nullptr);
    ~QuarkPathEdit();

    void setObjectName(const QString&);

private:
    Ui::QuarkPathEdit *ui;

private slots:
    void browseReleased();
};

#endif // QUARKPATHEDIT_H
