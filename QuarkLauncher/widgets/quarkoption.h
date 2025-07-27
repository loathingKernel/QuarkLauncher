#ifndef QUARKOPTION_H
#define QUARKOPTION_H

#include <QObject>

#include "quarkenv.h"

class QuarkOption : public QObject, public QuarkEnv
{
    Q_OBJECT
public:
    explicit QuarkOption(QObject *parent = nullptr);

    // Override object name
    void setObjectName(const QString&);
    QString objectName();

    virtual void load(QProcessEnvironment*) = 0;
    QVariant loadOption(QProcessEnvironment*);

public slots:
    virtual void setEnvVariable(int);
    virtual void setEnvVariable(bool);
    virtual void setEnvVariable(const QString&);

signals:

private:

};

#endif // QUARKOPTION_H
