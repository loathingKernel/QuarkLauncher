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

void EnvVariables::setTable(QProcessEnvironment* env)
{
    ui->table->clearContents();
    ui->table->setRowCount(env->keys().size());

    for (int idx = 0; idx < env->keys().size(); idx++) {
        QTableWidgetItem *name = new QTableWidgetItem(env->keys().at(idx));
        ui->table->setItem(idx, 0, name);
        QTableWidgetItem *value = new QTableWidgetItem(env->value(env->keys().at(idx)));
        ui->table->setItem(idx, 1, value);
    }

    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}
