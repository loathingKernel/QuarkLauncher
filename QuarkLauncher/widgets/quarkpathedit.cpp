#include "quarkpathedit.h"
#include "ui_quarkpathedit.h"

QuarkPathEdit::QuarkPathEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuarkPathEdit),
    QuarkEnv(parent)
{
    ui->setupUi(this);
    connect(ui->browse, &QPushButton::released, this, &QuarkPathEdit::browseReleased);
}

QuarkPathEdit::~QuarkPathEdit()
{
    delete ui;
}

void QuarkPathEdit::setObjectName(const QString &name)
{
    QWidget::setObjectName(name + "_PathEdit");
    ui->browse->setObjectName(name + "_Browse");
    ui->value->setObjectName(name);
}

void QuarkPathEdit::browseReleased()
{
    QString path;
    if (ui->value->text().isEmpty())
        path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    else
        path = ui->value->text();
    QFileDialog dialog(this, "Choose " + ui->value->QuarkOption::objectName() + " path", path);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    dialog.setViewMode(QFileDialog::Detail);
    if (dialog.exec()) {
        QStringList fileNames = dialog.selectedFiles();
        ui->value->setText(fileNames[0]);
    }
}
