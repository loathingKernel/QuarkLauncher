#include "quarkcontainer_widget.h"

QuarkContainerWidget::QuarkContainerWidget(QWidget *parent) :
    QuarkGroup(parent)
{

}

void QuarkContainerWidget::setObjectName(const QString &name)
{
    QWidget::setObjectName(name + "_Container");
    QuarkGroup::setObjectName(name);
}
