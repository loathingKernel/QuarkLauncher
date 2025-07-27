#ifndef QUARKGROUP_H
#define QUARKGROUP_H

#include <QObject>

#include "quarkenv.h"

class QuarkGroup : public QObject, public QuarkEnv
{
    Q_OBJECT
public:
    explicit QuarkGroup(QObject *parent = nullptr);
    ~QuarkGroup();

    void setObjectName(const QString&);
    QString objectName();

    void initGroup(const QString&);
};

#endif // QUARKGROUP_H
