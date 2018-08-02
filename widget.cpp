#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget()), connProcess(CONN::NONE)
{
    ui->setupUi(this);
    connect(ui->graphicsView->scene(), &QGraphicsScene::selectionChanged,
            this, &Widget::sceneSelectionChanged);
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

void Widget::sceneSelectionChanged()
{
    auto listItems = ui->graphicsView->scene()->selectedItems();
    if (listItems.size() == 0) {
        ui->btnDelete->setEnabled(false);
    } else if (listItems.size() == 1) {
        ui->btnDelete->setEnabled(true);
        Node * node = dynamic_cast<Node *>(listItems.at(0));
        if (node) {
            if (connProcess == CONN::NEED_SOURCE) {
                node->setMark(true);
                connProcess = CONN::NEED_DEST;
            } else if (connProcess == CONN::NEED_DEST) {
                Node * nSourse = nullptr;
                foreach (auto it, ui->graphicsView->scene()->items()) {
                    Node *nTemp = dynamic_cast<Node *>(it);
                    if (nTemp && nTemp->mark()) {
                        nSourse = nTemp;
                        break;
                    }
                }
                if (nSourse) {
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
