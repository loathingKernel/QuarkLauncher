#include "quarklauncher.h"
#include "ui_quarklauncher.h"

QuarkLauncher::QuarkLauncher(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QuarkLauncher)
{
    ui->setupUi(this);

    m_args = QStringList(qApp->instance()->arguments());
    m_args.removeFirst();
    for (const auto & m_arg : m_args) {
        if (m_arg.contains("AppId=")) {
            m_appId = QString(m_arg.split("=")[1]);
        }
        if (m_arg.contains(".exe")) {
            m_winCmd = QString(m_arg);
        }
    }
    qDebug() << "Args: " << m_args.join(", ");
    qDebug() << "AppId: " << m_appId;
    qDebug() << "WinCmd: " << m_winCmd;

    QList<QuarkGroup*> groups = this->findChildren<QuarkGroup*>();
    qDebug() << "Groups:";
    QListIterator<QuarkGroup*> groups_iter(groups);
    while (groups_iter.hasNext()) {
        QuarkGroup* group = groups_iter.next();
        qDebug() << group;
        if (group)
            group->initGroup(m_appId);
    }

    m_env = QProcessEnvironment::systemEnvironment();

    QList<QuarkOption*> options = this->findChildren<QuarkOption*>();
    qDebug() << "Options:";
    QListIterator<QuarkOption*> options_iter(options);
    while (options_iter.hasNext()) {
        QuarkOption* option = options_iter.next();
        qDebug() << option;
        if (option)
            option->load(&m_env);
    }

    load();

    m_proc = new QProcess(this);

    m_envVariables = new EnvVariables(this);
    m_console = new Console(m_proc, this);

    ui->killButton->setEnabled(false);

    connect(ui->environButton, &QPushButton::released,
            this, &QuarkLauncher::environButtonReleased );
    connect(ui->consoleButton, &QPushButton::released,
            this, &QuarkLauncher::consoleButtonReleased );
    connect(ui->killButton,    &QPushButton::released,
            this, &QuarkLauncher::killButtonReleased    );

    connect(this->m_proc, &QProcess::started,
            this->m_console, &Console::started          );
//    connect(this->m_proc,       &QProcess::finished,
//            this->m_console,    &Console::finished);
    connect(this->m_proc, &QProcess::readyReadStandardError,
            this->m_console, &Console::readyReadStderr  );
    connect(this->m_proc, &QProcess::readyReadStandardOutput,
            this->m_console, &Console::readyReadStdout  );

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QuarkLauncher::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QuarkLauncher::reject);

    connect(ui->arguments,      &QLineEdit::textChanged,
            this, [=] (QString text) { save("arguments", text);        } );
    connect(ui->originalExe,    &QLineEdit::textChanged,
            this, [=] (QString text) { save("original_exe", text);     } );
    connect(ui->replacementExe, &QLineEdit::textChanged,
            this, [=] (QString text) { save("replacement_exe", text);  } );
}

QuarkLauncher::~QuarkLauncher()
{
    delete ui;
}

void QuarkLauncher::consoleButtonReleased()
{
    m_console->show();
}

void QuarkLauncher::killButtonReleased()
{
    if(m_proc->state() == QProcess::Running) {
        m_proc->terminate();
    }
    ui->killButton->setEnabled(false);
}

void QuarkLauncher::environButtonReleased()
{
    QProcessEnvironment env = getChildEnv(&m_env);
    m_envVariables->setTable(&env);
    m_envVariables->show();
}

void QuarkLauncher::accept()
{
    QProcessEnvironment denv = getChildEnv(nullptr);
    qDebug() << "Environ  : " << denv.toStringList().join(", ");

    QProcessEnvironment env = getChildEnv(&m_env);

    QStringList args(m_args);

    QString cmd = args.takeFirst();
    qDebug() << "Command  : " << cmd;

    if (!args.isEmpty()) {
        if (args.last().contains(ui->originalExe->text())) {
            args.last().replace(ui->originalExe->text(), ui->replacementExe->text());
        }
    }
    if (!ui->arguments->text().isEmpty()) {
        args.append(ui->arguments->text());
    }
    qDebug() << "Arguments: " << args.join(", ");

    m_proc->setProcessEnvironment(env);
    m_proc->start(cmd, args);
    ui->killButton->setEnabled(true);
}

void QuarkLauncher::save(QString name, QString text)
{
    QSettings settings(this);
    settings.beginGroup(m_appId);
    settings.beginGroup("appl");
    settings.setValue(name, text);
    settings.endGroup();
    settings.endGroup();
}

void QuarkLauncher::load()
{
    QSettings settings(this);
    settings.beginGroup(m_appId);
    settings.beginGroup("appl");
    ui->arguments->setText(settings.value("arguments", "").toString());
    ui->originalExe->setText(settings.value("original_exe", "").toString());
    ui->replacementExe->setText(settings.value("replacement_exe", "").toString());
    settings.endGroup();
    settings.endGroup();
}

QProcessEnvironment QuarkLauncher::getChildEnv(const QProcessEnvironment* env) const {
    QProcessEnvironment _env;
    if (env != nullptr)
        _env.insert(*env);

    _env.insert(*(ui->proton->environment()));
    _env.insert(*(ui->wine->environment()));
    _env.insert(*(ui->dxvk->environment()));
    _env.insert(*(ui->vkd3d->environment()));
    _env.insert(*(ui->osd->environment()));
    return _env;
}

