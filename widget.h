#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <graphwidget.h>
#include <node.h>
#include <edge.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnCreateNode_clicked();
    void on_btnDelete_clicked();
    void on_btnConnectNode_clicked();
    void graphWidgetClicked(QMouseEvent *event);
private:
    Ui::Widget *ui;
    int connProcess;
};

namespace CONN {
enum {
    NONE,
    NEED_SOURCE,
    NEED_DEST
};
}

#endif // WIDGET_H
