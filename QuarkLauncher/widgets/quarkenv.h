#ifndef QUARKENV_H
#define QUARKENV_H

#include <QtDebug>
#include <QSettings>
#include <QProcessEnvironment>

class QuarkEnv
{
public:
    explicit QuarkEnv(QObject* parent = nullptr);
    ~QuarkEnv();

public:
    QProcessEnvironment* environment() const;
    void setEnvironment(QProcessEnvironment*);

    QSettings *settings() const;
    void setSettings(QSettings*);

    virtual QString objectName();

    const QString &appid() const;
    void setAppid(const QString&);

    const QString &group() const;
    void setGroup(const QString&);

private:
    QSettings* m_settings;
    QProcessEnvironment* m_environment;
    QString m_appid;
    QString m_group;
};

#endif // QUARKENV_H
