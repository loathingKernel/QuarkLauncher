#include "quarklineedit.h"

QuarkLineEdit::QuarkLineEdit(QWidget *parent) :
    QLineEdit(parent),
    QuarkOption(parent)
{
    QObject::connect(
                dynamic_cast<QLineEdit*>(this), SIGNAL(textChanged(QString)),
                dynamic_cast<QuarkOption*>(this), SLOT(setEnvVariable(QString)));
}

void QuarkLineEdit::setObjectName(const QString &name)
{
    QLineEdit::setObjectName(name + "_LineEdit");
    QuarkOption::setObjectName(name);
}

void QuarkLineEdit::setEnvVariable(const QString &text)
{
    if (text.isEmpty()) {
        environment()->remove(QuarkOption::objectName());
        settings()->remove(QuarkOption::objectName());
    } else {
        environment()->insert(QuarkOption::objectName(), text);
        settings()->setValue(QuarkOption::objectName(), text);
    }
    qDebug() << environment()->toStringList().join(" ");
}

void QuarkLineEdit::load(QProcessEnvironment* env)
{
    setText(loadOption(env).toString());
}

