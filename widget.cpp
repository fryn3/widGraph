#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMouseEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget()), connProcess(CONN::NONE)
{
    ui->setupUi(this);
    connect(ui->graphicsView, &GraphWidget::mousePressedSignal,
            this, &Widget::graphWidgetClicked);
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

void Widget::on_btnConnectNode_clicked()
{
    Node *node;
    if(ui->graphicsView->scene()->selectedItems().size() == 0) {
        connProcess = CONN::NEED_SOURCE;
    } else if (ui->graphicsView->scene()->selectedItems().size() == 1
               && (node = dynamic_cast<Node *>
                   (ui->graphicsView->scene()->selectedItems().at(0)))) {
        node->setMark(true);
        ui->graphicsView->scene()->clearSelection();
        connProcess = CONN::NEED_DEST;
    }
}

void Widget::graphWidgetClicked(QMouseEvent *event)
{
    auto selectedItems = ui->graphicsView->scene()->selectedItems();
    if (selectedItems.size() == 0) {
        // Если выделенных элементов нет.
        ui->btnDelete->setEnabled(false);
        return;
    } else if (ui->graphicsView->itemAt(event->pos())) {
        // Если нажатие произошло над элементом сцены.
        ui->btnDelete->setEnabled(true);
        Node *node = dynamic_cast<Node *>(selectedItems.at(0));
        if (node) { // Если выделена вершина.
            if (connProcess == CONN::NEED_SOURCE) {
                // Отмечаем источник.
                node->setMark(true);
                connProcess = CONN::NEED_DEST;
            } else if (connProcess == CONN::NEED_DEST) {
                // Находим вершину назначения.
                Node * nSourse = nullptr;
                foreach (auto it, ui->graphicsView->scene()->items()) {
                    Node *nTemp = dynamic_cast<Node *>(it);
                    if (nTemp && nTemp->mark()) {
                        nSourse = nTemp;
                        break;
                    }
                }
                if (nSourse) {
                    // Если нашлась выделенная вершина.
                    Edge *e = new Edge(nSourse, node);
                    ui->graphicsView->scene()->addItem(e);
                    nSourse->setMark(false);
                    connProcess = CONN::NONE;
                } else {
                    qDebug() << "Error connProcess value";
                }
            }
        }
    }
}
