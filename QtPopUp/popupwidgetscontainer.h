#ifndef POPUPWIDGETSCONTAINER_H
#define POPUPWIDGETSCONTAINER_H

#include <QtCore/QObject>
#include <QtCore/QVector>

class PopUpWidget;

class PopUpWidgetsContainer : public QObject
{
    Q_OBJECT
public:
    enum class MaxPopUpAmountType
    {
        ByMaxCount,
        ByParentHeight
    };

    PopUpWidgetsContainer(QWidget* parent);

    void addPopUp(const QString& text);
private:
    QWidget* mParentWidget;

    QVector<PopUpWidget*> mWidgets;
    MaxPopUpAmountType mMaxPopUpAmountType{MaxPopUpAmountType::ByMaxCount};
    int mMaxPopCount{7};

    void replot();
private slots:
    void removeFromConainer();
};

#endif // POPUPWIDGETSCONTAINER_H
