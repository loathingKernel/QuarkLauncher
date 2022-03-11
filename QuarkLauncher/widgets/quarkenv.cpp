#include "quarkenv.h"

QuarkEnv::QuarkEnv(QObject *parent)
{
    QuarkEnv* container = dynamic_cast<QuarkEnv*>(parent);
    if (container) {
        m_environment = container->environment();
        m_settings = container->settings();
    } else {
        if (parent)
            qDebug() << objectName() << ": Couldn't get env from parent " << parent->objectName();
        else
            qDebug() << objectName() << ": Parent is null";
    }
}

QuarkEnv::~QuarkEnv()
{

}

QProcessEnvironment *QuarkEnv::environment() const
{
    return m_environment;
}

void QuarkEnv::setEnvironment(QProcessEnvironment *env)
{
    m_environment = env;
}

QSettings *QuarkEnv::settings() const
{
    return m_settings;
}

void QuarkEnv::setSettings(QSettings *settings)
{
    m_settings = settings;
}

QString QuarkEnv::objectName()
{
    return QString("QuarkEnv");
}

const QString &QuarkEnv::appid() const
{
    return m_appid;
}

void QuarkEnv::setAppid(const QString &appid)
{
    m_appid = appid;
}

const QString &QuarkEnv::group() const
{
    return m_group;
}

void QuarkEnv::setGroup(const QString &group)
{
    m_group = group;
}
