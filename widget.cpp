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
    Node *node = new Node(ui->graphicsView);
    ui->graphicsView->scene()->addItem(node);
}
