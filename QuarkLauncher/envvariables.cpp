#include "envvariables.h"
#include "ui_envvariables.h"

EnvVariables::EnvVariables(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnvVariables)
{
    ui->setupUi(this);
}

EnvVariables::~EnvVariables()
{
    delete ui;
}

void EnvVariables::setTable(const QProcessEnvironment* env) const {
    ui->table->clearContents();
    ui->table->setRowCount(env->keys().size());

    for (int idx = 0; idx < env->keys().size(); idx++) {
        ui->table->setItem(idx, 0, new QTableWidgetItem(env->keys().at(idx)));
        ui->table->setItem(idx, 1, new QTableWidgetItem(env->value(env->keys().at(idx))));
    }

    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}
