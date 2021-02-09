#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QtWidgets>
#include <QVideoWidget>

class VideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);

signals:
    void clicked();
    void doubleClicked();

protected:
    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *e) override;
};

#endif // VIDEOWIDGET_H
