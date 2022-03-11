#ifndef QUARKGROUP_H
#define QUARKGROUP_H

#include <QGroupBox>

#include "quarkenv.h"

class QuarkGroup : public QGroupBox, public QuarkEnv
{
public:
    explicit QuarkGroup(QWidget *parent = nullptr);
    ~QuarkGroup();

    void setObjectName(const QString&);

    void initGroup(const QString&);
};

#endif // QUARKGROUP_H
