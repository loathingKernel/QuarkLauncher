#include "console.h"
#include "ui_console.h"

#include "utils/ansiescapecodehandler.h"

Console::Console(QProcess* process, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Console)
{
    ui->setupUi(this);
    proc = process;
}

Console::~Console()
{
    delete ui;
}

void Console::started()
{
    this->show();
    ui->console->clear();
}

void Console::finished()
{
}

void Console::readyReadStdout()
{
    QString text(proc->readAllStandardOutput());
    // QString html("<p style=\"white-space:pre\">%1</p>");
    // ui->console->appendHtml(html.arg(text));
    const QList<Utils::FormattedText> fmtList = handler.parseText(Utils::FormattedText(text));
    QTextCursor cursor = ui->console->textCursor();
    cursor.beginEditBlock();
    for (const auto &fmtChunk : fmtList)
        cursor.insertText(fmtChunk.text, fmtChunk.format);
    cursor.endEditBlock();
    ui->console->document()->setModified(false);
}

void Console::readyReadStderr()
{
    QString text(proc->readAllStandardError());
    // QString html("<p style=\"color:red;white-space:pre\">%1</p>");
    // ui->console->appendHtml(html.arg(text));
    const QList<Utils::FormattedText> fmtList = handler.parseText(Utils::FormattedText(text));
    QTextCursor cursor = ui->console->textCursor();
    cursor.beginEditBlock();
    for (const auto &fmtChunk : fmtList)
        cursor.insertText(fmtChunk.text, fmtChunk.format);
    cursor.endEditBlock();
    ui->console->document()->setModified(false);
}
