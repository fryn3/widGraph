#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget())
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnCreateNode_clicked()
{
    Node *node = new Node();
    ui->graphicsView->scene()->addItem(node);
}

void Widget::on_btnDelete_clicked()
{
    while (!ui->graphicsView->scene()->selectedItems().isEmpty())
        delete ui->graphicsView->scene()->selectedItems().takeFirst();
}
