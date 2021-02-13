#ifndef IMAGE_H
#define IMAGE_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>

class Image : public QWidget
{
    Q_OBJECT
public:
    explicit Image(QWidget *parent = nullptr);

    void setPix(const QPixmap &value);

    bool notSquare;

protected:
    virtual void paintEvent(QPaintEvent *) override;

private:
    QPixmap pix;
};

#endif // IMAGE_H
