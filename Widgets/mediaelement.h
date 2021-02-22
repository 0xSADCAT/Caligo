#ifndef MEDIAELEMENT_H
#define MEDIAELEMENT_H

#include <QtWidgets>

#include <Style/style.cpp>

class MediaElement : public QWidget
{
    Q_OBJECT
public:
    explicit MediaElement(const QString &path, QWidget *parent = nullptr);

    QString getPath() const;

    bool hasMeta() const;

    void setText(const QString &text);

    void setPlaying(bool value);

    void setSelected(bool value);

    QString getString() const;

signals:
    void clicked();
    void shiftClicked();
    void ctrlClicked();
    void doubleClicked();

    // Needs to set focus to Playlist but not on element (playlist keyboard controls)
    void focus();

    // Signals from context menu.
    void selectAll();
    void deleteSelected();

protected:
    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *e) override;
    virtual void focusInEvent(QFocusEvent *) override;
    virtual void contextMenuEvent(QContextMenuEvent *e) override;

private:
    QLabel *text;
    // Path to file.
    QString path;
    bool meta;
    // Playing/selected states.
    bool playing;
    bool selected;

    void updStyle();

    QMenu *contextMenu;
};

#endif // MEDIAELEMENT_H
