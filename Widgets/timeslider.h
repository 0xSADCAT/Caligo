#ifndef TIMESLIDER_H
#define TIMESLIDER_H

#include <QMouseEvent>
#include <QWidget>
#include <QPainter>

class TimeSlider : public QWidget
{
    Q_OBJECT
public:
    explicit TimeSlider(QWidget *parent = nullptr);

signals:
    void clicked(qint64);

public slots:
    void setDuration(qint64 v);
    void setPosition(qint64 v);

protected:
    virtual void enterEvent(QEvent *) override;
    virtual void leaveEvent(QEvent *) override;
    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void paintEvent(QPaintEvent *) override;

private:
    qint64 _pos, _dur;
    bool isIn;
};

#endif // TIMESLIDER_H
