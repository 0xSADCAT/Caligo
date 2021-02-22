#ifndef RADIOELEMENT_H
#define RADIOELEMENT_H

#include <QtWidgets>

#include <Style/style.cpp>

class RadioElement : public QWidget
{
    Q_OBJECT
public:
    explicit RadioElement(QString &url, QString &name, QWidget *parent = nullptr);

    QString getName() const;
    QString getUrl() const;

    void setSelected(bool v);

signals:
    void clicked();
    void doubleClicked();
    void ctrlClicked();
    void shiftClicked();
    void focus();

protected:
    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *e) override;
    virtual void focusInEvent(QFocusEvent *) override;

private:
    QLabel *nameLabel;
    QLabel *urlLabel;
};

#endif // RADIOELEMENT_H
