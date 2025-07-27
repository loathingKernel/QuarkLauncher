#ifndef QUARKCONTAINER_WIDGET_H
#define QUARKCONTAINER_WIDGET_H

#include <QWidget>

#include "quarkgroup.h"

class QuarkContainerWidget : public QWidget, public QuarkGroup
{
public:
    explicit QuarkContainerWidget(QWidget *parent = nullptr);

    // Override setObjectName to handle both parent classes
    void setObjectName(const QString&);
};

#endif // QUARKCONTAINER_WIDGET_H
