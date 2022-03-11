#ifndef QUARKCHECKBOX_H
#define QUARKCHECKBOX_H

#include <QCheckBox>

#include "quarkoption.h"

class QuarkCheckBox : public QCheckBox, public QuarkOption
{
public:
    explicit QuarkCheckBox(QWidget *parent = nullptr);

    // Override setObjectName to handle both parent classes
    void setObjectName(const QString&);
    // Override setText to unconditionally set the label to the object name
    void setText(const QString&);

    // QuarkOption interface
public slots:
    void setEnvVariable(int);

    // QuarkOption interface
public:
    void load();
};

#endif // QUARKCHECKBOX_H
