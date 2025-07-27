#include "quarkgroup.h"

QuarkGroup::QuarkGroup(QObject *parent)
    : QObject{parent},
      QuarkEnv(parent)
{
    setEnvironment(new QProcessEnvironment());
    setSettings(new QSettings(this));
}

void QuarkGroup::setObjectName(const QString &name)
{
    QObject::setObjectName(name);
}

QString QuarkGroup::objectName()
{
    return QObject::objectName();
}

void QuarkGroup::initGroup(const QString &newAppid)
{
    setAppid(newAppid);
    // this is not needed but keep it this way for now
    setGroup(QObject::objectName());
    settings()->beginGroup(appid());
    settings()->beginGroup(group());
}

QuarkGroup::~QuarkGroup()
{
    if (environment())
        delete environment();
    if (settings()) {
        settings()->endGroup();
        settings()->endGroup();
        delete settings();
    }
}
