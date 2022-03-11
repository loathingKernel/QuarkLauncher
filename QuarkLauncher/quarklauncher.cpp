#include "quarklauncher.h"
#include "ui_quarklauncher.h"

QuarkLauncher::QuarkLauncher(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QuarkLauncher)
{
    ui->setupUi(this);

    m_args = QStringList(qApp->instance()->arguments());
    m_args.removeFirst();
    for (int idx = 0; idx < m_args.size(); idx++) {
        if (m_args.at(idx).contains("AppId=")) {
            m_appId = QString(m_args.at(idx).split("=")[1]);
        }
        if (m_args.at(idx).contains(".exe")) {
            m_winCmd = QString(m_args.at(idx));
        }
    }
    qDebug() << "Args: " << m_args.join(", ");
    qDebug() << "AppId: " << m_appId;
    qDebug() << "WinCmd: " << m_winCmd;

    QList<QuarkGroup*> groups = this->findChildren<QuarkGroup*>();
    qDebug() << groups;
    QListIterator<QuarkGroup*> groups_iter(groups);
    while (groups_iter.hasNext()) {
        QuarkGroup* group = groups_iter.next();
        if (dynamic_cast<QuarkGroup*>(group))
            group->initGroup(m_appId);
    }

    QList<QuarkOption*> options = this->findChildren<QuarkOption*>();
    qDebug() << options;
    QListIterator<QuarkOption*> options_iter(options);
    while (options_iter.hasNext()) {
        QuarkOption* option = options_iter.next();
        if (dynamic_cast<QuarkOption*>(option))
            option->load();
    }

    m_env = QProcessEnvironment().systemEnvironment();
    m_proc = new QProcess(this);

    m_envDialog = new EnvVariables(this);
    m_conDialog = new Console(m_proc, this);

    ui->killButton->setEnabled(false);

    connect(ui->envButton, SIGNAL(released()), this, SLOT(envButtonReleased()));
    connect(ui->conButton, SIGNAL(released()), this, SLOT(conButtonReleased()));
    connect(ui->killButton, SIGNAL(released()), this, SLOT(killButtonReleased()));
    connect(this->m_proc, SIGNAL(started()), this->m_conDialog, SLOT(started()));
//    connect(this->proc, SIGNAL(finished()), this->conDlg, SLOT(finished()));
    connect(this->m_proc, SIGNAL(readyReadStandardError()), this->m_conDialog, SLOT(readyReadStderr()));
    connect(this->m_proc, SIGNAL(readyReadStandardOutput()), this->m_conDialog, SLOT(readyReadStdout()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

QuarkLauncher::~QuarkLauncher()
{
    delete ui;
}

void QuarkLauncher::conButtonReleased()
{
    m_conDialog->show();
}

void QuarkLauncher::killButtonReleased()
{
    if(m_proc->state() == QProcess::Running) {
        m_proc->terminate();
    }
    ui->killButton->setEnabled(false);
}

void QuarkLauncher::envButtonReleased()
{
    QProcessEnvironment env(m_env);
    env.insert(*(ui->Proton->environment()));
    m_envDialog->setTable(&env);
    m_envDialog->show();
}

void QuarkLauncher::accept()
{
    QString cmd = m_args.takeFirst();
    m_proc->setProcessEnvironment(m_env);
    m_proc->start(cmd, m_args);
    ui->killButton->setEnabled(true);
}

