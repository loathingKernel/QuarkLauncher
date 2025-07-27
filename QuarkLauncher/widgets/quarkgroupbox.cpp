#include "quarkgroupbox.h"

QuarkGroupBox::QuarkGroupBox(QWidget *parent) :
    QGroupBox(parent),
    QuarkOption(parent)
{
    QObject::connect(
                dynamic_cast<QGroupBox*>(this), SIGNAL(toggled(bool)),
                dynamic_cast<QuarkOption*>(this), SLOT(setEnvVariable(bool)));
}

void QuarkGroupBox::setObjectName(const QString &name)
{
    QGroupBox::setObjectName(name + "_GroupBox");
    QuarkOption::setObjectName(name);
}

void QuarkGroupBox::setText(const QString &text)
{
    QGroupBox::setTitle(QuarkOption::objectName());
}

void QuarkGroupBox::setEnvVariable(bool state)
{
    if (!state) {
        environment()->remove(QuarkOption::objectName());
        settings()->remove(QuarkOption::objectName());
    } else {
        environment()->insert(QuarkOption::objectName(), "1");
        settings()->setValue(QuarkOption::objectName(), "1");
    }
    qDebug() << environment()->toStringList().join(" ");
}

void QuarkGroupBox::load(QProcessEnvironment* env)
{
    this->setChecked(loadOption(env).toBool());
}
