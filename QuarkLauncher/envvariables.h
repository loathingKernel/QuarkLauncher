#ifndef ENVVARIABLES_H
#define ENVVARIABLES_H

#include <QDialog>
#include <QHeaderView>
#include <QProcessEnvironment>

namespace Ui {
class EnvVariables;
}

class EnvVariables : public QDialog
{
    Q_OBJECT

public:
    explicit EnvVariables(QWidget *parent = nullptr);
    ~EnvVariables();

    void setTable(const QProcessEnvironment*) const;

private:
    Ui::EnvVariables *ui;
};

#endif // ENVVARIABLES_H
