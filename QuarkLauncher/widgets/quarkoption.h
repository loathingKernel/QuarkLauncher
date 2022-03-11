#ifndef QUARKOPTION_H
#define QUARKOPTION_H

#include <QObject>
#include <QtDebug>

#include "quarkenv.h"

class QuarkOption : public QObject, public QuarkEnv
{
    Q_OBJECT
public:
    explicit QuarkOption(QObject *parent = nullptr);

    // Override setObject name to also set m_varName;
    void setObjectName(const QString&);
    QString objectName();

    virtual void load() = 0;

public slots:
    virtual void setEnvVariable(int);
    virtual void setEnvVariable(const QString&);

signals:

private:

};

#endif // QUARKOPTION_H
