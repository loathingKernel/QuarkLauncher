#include "quarkoption.h"

QuarkOption::QuarkOption(QObject *parent)
    : QObject{parent},
      QuarkEnv(parent)
{

}

void QuarkOption::setObjectName(const QString &name)
{
    QObject::setObjectName(name);
}

QString QuarkOption::objectName()
{
    return QObject::objectName();
}

QVariant QuarkOption::loadOption(QProcessEnvironment* env) {
    QVariant value;

    if (settings()->contains(QuarkOption::objectName()))
        value = settings()->value(QuarkOption::objectName());
    else
        value = env->value(this->objectName());
        env->remove(this->objectName());

    return value;
}

void QuarkOption::setEnvVariable(int num)
{
    qDebug() << QObject::objectName() << ": " << num;
    qDebug() << QuarkOption::parent()->objectName() << environment()->toStringList().join(" ");

}

void QuarkOption::setEnvVariable(bool state)
{
    qDebug() << QObject::objectName() << ": " << state;
    qDebug() << QuarkOption::parent()->objectName() << environment()->toStringList().join(" ");

}

void QuarkOption::setEnvVariable(const QString & text)
{
    qDebug() << QObject::objectName() << ": " << text;
    qDebug() << QuarkOption::parent()->objectName() << environment()->toStringList().join(" ");

}
