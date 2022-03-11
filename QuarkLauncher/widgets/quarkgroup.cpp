#include "quarkgroup.h"

QuarkGroup::QuarkGroup(QWidget *parent) :
    QGroupBox(parent),
    QuarkEnv(parent)
{
    setEnvironment(new QProcessEnvironment());
    setSettings(new QSettings(this));
}

void QuarkGroup::setObjectName(const QString &name)
{
    QGroupBox::setObjectName(name + "_Group");
    setGroup(name);
}

void QuarkGroup::initGroup(const QString &newAppid)
{
    setAppid(newAppid);
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
