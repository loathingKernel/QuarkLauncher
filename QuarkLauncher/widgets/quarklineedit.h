#ifndef QUARKLINEEDIT_H
#define QUARKLINEEDIT_H

#include <QLineEdit>

#include "quarkoption.h"

class QuarkLineEdit : public QLineEdit, public QuarkOption
{
public:
    explicit QuarkLineEdit(QWidget *parent = nullptr);

    // Override setObjectName to handle both parent classes
    void setObjectName(const QString&);

    // QuarkOption interface
public slots:
    void setEnvVariable(const QString &);

    // QuarkOption interface
public:
    void load(QProcessEnvironment*);
};

#endif // QUARKLINEEDIT_H
