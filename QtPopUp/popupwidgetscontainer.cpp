#include "popupwidgetscontainer.h"
#include "popupwidget.h"

PopUpWidgetsContainer::PopUpWidgetsContainer(QWidget* parent)
    :QObject(parent)
{
    mParentWidget=parent;
}

void PopUpWidgetsContainer::addPopUp(const QString& text)
{
    static int t=0;

    if (t==0)
        t=1;
    else if (t==1)
        t=2;
    else if (t==2)
        t=0;

    PopUpWidget::Type type=(PopUpWidget::Type)t;

    PopUpWidget* new_popup=new PopUpWidget(type,mParentWidget);
    new_popup->setPopUpText(text);
    new_popup->setOrder(0);
    new_popup->reset_animation();
    QObject::connect(new_popup,&PopUpWidget::removeFromContainer,this,&PopUpWidgetsContainer::removeFromConainer);

    for (int i=0,isize=mWidgets.size();i<isize;i++)
        mWidgets[i]->setOrder(i+1);

    mWidgets.push_front(new_popup);

    if (mMaxPopUpAmountType==MaxPopUpAmountType::ByParentHeight)
    {
        int posy=mParentWidget->frameGeometry().y()+mParentWidget->frameGeometry().height()-8;
        const auto max_y_pos=mParentWidget->frameGeometry().y();
        int max_index=-1;
        for (int i=0,isize=mWidgets.size();i<isize;i++)
        {
            const auto popup_widget=mWidgets.at(i);
            popup_widget->adjustSize();

            posy=posy-popup_widget->height()-2;

            if (posy<=max_y_pos)
            {
                max_index=i;
                break;
            }
        }

        if (max_index!=-1)
        {
            for (int i=mWidgets.size()-1;i>=max_index;i--)
            {
                auto popup_widget=mWidgets.at(i);
                mWidgets.remove(i);
                popup_widget->deleteLater();
            }
        }
    }
    else if (mMaxPopUpAmountType==MaxPopUpAmountType::ByMaxCount)
    {
        if (mWidgets.size()>mMaxPopCount)
        {
            for (int i=mWidgets.size()-1;i>=mMaxPopCount;i--)
            {
                auto popup_widget=mWidgets.at(i);
                mWidgets.remove(i);
                popup_widget->deleteLater();
            }
        }
    }

    replot();
}

void PopUpWidgetsContainer::removeFromConainer()
{
    auto sender=QObject::sender();

    auto popup_widget=dynamic_cast<PopUpWidget*>(sender);
    if (!sender)
        return;

    const auto iter=std::find_if(mWidgets.begin(),mWidgets.end(),[&popup_widget](QWidget* const& elem)
    {
            return (elem==popup_widget);
    });

    if (iter!=mWidgets.end())
        mWidgets.erase(iter);

    popup_widget->deleteLater();

    replot();
}

void PopUpWidgetsContainer::replot()
{
    int posy=mParentWidget->frameGeometry().y()+mParentWidget->frameGeometry().height()-8;
    for (int i=0,isize=mWidgets.size();i<isize;i++)
    {
        const auto popup_widget=mWidgets.at(i);
        popup_widget->adjustSize();

        const auto x=mParentWidget->frameGeometry().x()+mParentWidget->frameGeometry().width()-popup_widget->width()-10;
        const auto y=posy-popup_widget->height()-2;
        popup_widget->show(x,y);

        posy=y;
    }
}
