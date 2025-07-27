#ifndef QUARKCONTAINER_GROUPBOX_H
#define QUARKCONTAINER_GROUPBOX_H

#include <QGroupBox>

#include "quarkgroup.h"

class QuarkContainerGroupBox : public QGroupBox, public QuarkGroup
{
public:
    explicit QuarkContainerGroupBox(QWidget *parent = nullptr);

    // Override setObjectName to handle both parent classes
    void setObjectName(const QString&);
};

#endif // QUARKCONTAINER_GROUPBOX_H
