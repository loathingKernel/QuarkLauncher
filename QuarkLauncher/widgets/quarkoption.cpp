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

void QuarkOption::setEnvVariable(int num)
{
    qDebug() << QObject::objectName() << ": " << num;
}

void QuarkOption::setEnvVariable(const QString & text)
{
    qDebug() << QObject::objectName() << ": " << text;
}
