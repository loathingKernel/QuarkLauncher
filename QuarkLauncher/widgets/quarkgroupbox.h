#ifndef QUARKGROUPBOX_H
#define QUARKGROUPBOX_H

#include <QGroupBox>

#include "quarkoption.h"

class QuarkGroupBox : public QGroupBox, public QuarkOption
{
public:
    explicit QuarkGroupBox(QWidget *parent = nullptr);

    // Override setObjectName to handle both parent classes
    void setObjectName(const QString&);
    // Override setText to unconditionally set the label to the object name
    void setText(const QString&);

    // QuarkOption interface
public slots:
    void setEnvVariable(bool) override;

    // QuarkOption interface
public:
    void load(QProcessEnvironment*) override;
};

#endif // QUARKGROUPBOX_H
