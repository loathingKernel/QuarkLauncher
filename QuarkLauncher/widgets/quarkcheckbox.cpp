#include "quarkcheckbox.h"

QuarkCheckBox::QuarkCheckBox(QWidget *parent) :
    QCheckBox(parent),
    QuarkOption(parent)
{
    QObject::connect(
        dynamic_cast<QCheckBox *>(this), SIGNAL(stateChanged(int)),
        dynamic_cast<QuarkOption *>(this), SLOT(setEnvVariable(int)));
}

void QuarkCheckBox::setObjectName(const QString &name)
{
    QCheckBox::setObjectName(name + "_CheckBox");
    QuarkOption::setObjectName(name);
}

void QuarkCheckBox::setText(const QString &text)
{
    QCheckBox::setText(QuarkOption::objectName());
}

void QuarkCheckBox::setEnvVariable(int state)
{
    if (state == Qt::Unchecked) {
        environment()->remove(QuarkOption::objectName());
        settings()->remove(QuarkOption::objectName());
    } else {
        environment()->insert(QuarkOption::objectName(), "1");
        settings()->setValue(QuarkOption::objectName(), "1");
    }
    QuarkOption::setEnvVariable(state);
}

void QuarkCheckBox::load(QProcessEnvironment* env)
{
    this->setChecked(loadOption(env).toBool());
}

