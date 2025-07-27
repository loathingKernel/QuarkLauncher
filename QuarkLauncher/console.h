#ifndef CONSOLE_H
#define CONSOLE_H

#include <QDialog>
#include <QProcess>

#include <utils/ansiescapecodehandler.h>

namespace Ui {
class Console;
}

class Console : public QDialog
{
    Q_OBJECT

public:
    explicit Console(QProcess*, QWidget *parent = nullptr);
    ~Console();

public slots:
    void started();
    void finished();
    void readyReadStdout();
    void readyReadStderr();

private:
    QProcess* proc;
    Utils::AnsiEscapeCodeHandler handler;

    Ui::Console *ui;
};

#endif // CONSOLE_H
