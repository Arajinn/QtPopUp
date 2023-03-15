#ifndef POPUPWIDGET_H
#define POPUPWIDGET_H

#include <QWidget>

namespace Ui
{
    class PopUpWidget;
}

class QPropertyAnimation;
class QTimer;

class PopUpWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double popupOpacity READ getPopupOpacity WRITE setPopupOpacity)

    void setPopupOpacity(double opacity);
    double getPopupOpacity() const;
public:
    enum class Type
    {
        Default,
        Warning,
        Error
    };

    explicit PopUpWidget(Type type = Type::Warning, QWidget *parent = 0);
    ~PopUpWidget();

    void setPopUpText(const QString& text);
    void reset_animation();
    void show(const int& x, const int& y);

    void setOrder(const int& order);
    int getOrder() const;
protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::PopUpWidget *ui;
    QPropertyAnimation* mPropertyAnimation;
    double popupOpacity;
    int mOrder;
    QTimer* mTimer;

private slots:
    void hideAnimation();
    void hide();
signals:
    void removeFromContainer();
};

#endif // POPUPWIDGET_H
