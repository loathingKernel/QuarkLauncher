#ifndef QUARKLAUNCHER_H
#define QUARKLAUNCHER_H

#include <QDialog>
#include <QProcess>
#include <QProcessEnvironment>
#include <QtDebug>

#include "envvariables.h"
#include "console.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QuarkLauncher; }
QT_END_NAMESPACE

class QuarkLauncher : public QDialog
{
    Q_OBJECT

public:
    QuarkLauncher(QWidget *parent = nullptr);
    ~QuarkLauncher();

private slots:
    void envButtonReleased();
    void conButtonReleased();
    void killButtonReleased();
    void accept();

private:
    QString m_appId;
    QString m_winCmd;

    QStringList m_args;
    QProcess* m_proc;
    QProcessEnvironment m_env;

    EnvVariables* m_envDialog;
    Console* m_conDialog;

    Ui::QuarkLauncher *ui;
};
#endif // QUARKLAUNCHER_H
