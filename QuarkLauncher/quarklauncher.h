#ifndef QUARKLAUNCHER_H
#define QUARKLAUNCHER_H

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
    void environButtonReleased();
    void consoleButtonReleased();
    void killButtonReleased();
    void accept();

    void save(QString, QString);
    void load();

private:
    QProcessEnvironment getChildEnv(const QProcessEnvironment*) const;

    QString m_appId;
    QString m_winCmd;

//    QString m_appArgs;
//    QString m_appOrigExe;
//    QString m_appReplExe;

    QStringList m_args;
    QProcess* m_proc;
    QProcessEnvironment m_env;

    EnvVariables* m_envVariables;
    Console* m_console;

    Ui::QuarkLauncher *ui;
};
#endif // QUARKLAUNCHER_H
