#ifndef LIBRARYELEMENT_H
#define LIBRARYELEMENT_H

#include <QtWidgets>

#include <Style/style.cpp>

class LibraryElement : public QWidget
{
    Q_OBJECT
public:
    explicit LibraryElement(QString &path, QWidget *parent = nullptr);

    QString getPath() const;

    void setText(const QString &value);

    QString getString() const;

    void setSelected(bool v);

    QString getName() const;

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

    QString path;
    QString name;
};

#endif // LIBRARYELEMENT_H
