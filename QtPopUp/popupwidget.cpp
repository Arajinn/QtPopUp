#include "popupwidget.h"
#include "ui_popupwidget.h"

#include <QtCore/QPropertyAnimation>
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtWidgets/QDesktopWidget>

PopUpWidget::PopUpWidget(Type type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PopUpWidget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);

    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);

    mPropertyAnimation=new QPropertyAnimation(this,"popupOpacity");
    QObject::connect(mPropertyAnimation,&QPropertyAnimation::finished,this,&PopUpWidget::hide);

    mTimer=new QTimer();
    QObject::connect(mTimer,&QTimer::timeout,this,&PopUpWidget::hideAnimation);

    QString icon_path;
    if (type==Type::Default)
        icon_path=":/icons/default.png";
    else if (type==Type::Warning)
        icon_path=":/icons/warning.png";
    else if (type==Type::Error)
        icon_path=":/icons/error.png";

    QPixmap pixmap(icon_path);
    ui->icon_label->setPixmap(pixmap.scaled(16,16,Qt::KeepAspectRatio));
}

void PopUpWidget::setPopupOpacity(double opacity)
{
    popupOpacity=opacity;
    setWindowOpacity(opacity);
}

double PopUpWidget::getPopupOpacity() const
{
    return popupOpacity;
}

PopUpWidget::~PopUpWidget()
{
    delete ui;
}

void PopUpWidget::setPopUpText(const QString &text)
{
    ui->label->setText(text);
    adjustSize();
}

void PopUpWidget::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect roundedRect;
    roundedRect.setX(rect().x()+5);
    roundedRect.setY(rect().y()+5);
    roundedRect.setWidth(rect().width()-10);
    roundedRect.setHeight(rect().height()-10);

    painter.setBrush(QBrush(QColor(0,0,0,180)));
    painter.setPen(Qt::NoPen);

    painter.drawRoundedRect(roundedRect,10,10);
}

void PopUpWidget::reset_animation()
{
    setWindowOpacity(0.0);

    mPropertyAnimation->setDuration(1);
    mPropertyAnimation->setStartValue(0.0);
    mPropertyAnimation->setEndValue(1.0);
    mPropertyAnimation->start();

    mTimer->start(3000);
}

void PopUpWidget::show(const int& x, const int& y)
{
    adjustSize();

    //const auto x=QApplication::desktop()->availableGeometry().width()-36-width()+QApplication::desktop()->availableGeometry().x();
    //const auto y=QApplication::desktop()->availableGeometry().height()-36-height()+QApplication::desktop()->availableGeometry().y();

    //const auto pw=parentWidget();
    //const auto x=pw->frameGeometry().x()+pw->frameGeometry().width()-width()-10;
    //const auto y=pw->frameGeometry().y()+pw->frameGeometry().height()-height()-10;

    setGeometry(x,y,width(),height());

    QWidget::show();
}

void PopUpWidget::hideAnimation()
{
    mTimer->stop();

    mPropertyAnimation->setDuration(3000);
    mPropertyAnimation->setStartValue(1.0);
    mPropertyAnimation->setEndValue(0.0);
    mPropertyAnimation->start();
}

void PopUpWidget::hide()
{
    if (getPopupOpacity()==0.0)
    {
        QWidget::hide();
        emit removeFromContainer();
    }
}

void PopUpWidget::setOrder(const int& order)
{
    mOrder=order;
}

int PopUpWidget::getOrder() const
{
    return mOrder;
}
