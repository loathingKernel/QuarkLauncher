#include "quarkcontainer_groupbox.h"

QuarkContainerGroupBox::QuarkContainerGroupBox(QWidget *parent) :
    QuarkGroup(parent)
{

}

void QuarkContainerGroupBox::setObjectName(const QString &name)
{
    QWidget::setObjectName(name + "_Container");
    QuarkGroup::setObjectName(name);
}
