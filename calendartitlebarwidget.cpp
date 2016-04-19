#include "calendartitlebarwidget.h"

LeftArrowButton::LeftArrowButton(QWidget *parent)
    : DImageButton(parent) {
    this->setHoverPic(":/resources/icon/left_button.png");
    this->setNormalPic(":/resources/icon/left_button.png");
    this->setPressPic(":/resources/icon/left_button.png");

    connect(this, &LeftArrowButton::clicked, this, &LeftArrowButton::setIncrease);
}
void LeftArrowButton::setIncrease() {
    emit leftArrowClicked();
}
LeftArrowButton::~LeftArrowButton(){}

RightArrowButton::RightArrowButton(QWidget *parent)
    : DImageButton(parent) {
    this->setFixedSize(24, 24);
    this->setHoverPic(":/resources/icon/right_button.png");
    this->setNormalPic(":/resources/icon/right_button.png");
    this->setPressPic(":/resources/icon/right_button.png");

    connect(this, &RightArrowButton::clicked, this, &RightArrowButton::setIncrease);
}

void RightArrowButton::setIncrease() {
    emit rightArrowclicked();
}
RightArrowButton::~RightArrowButton(){}

CalendarTitleBarWidget::CalendarTitleBarWidget(QWidget *parent)
    : QWidget(parent) {
    setFixedWidth(parent->width() - 120);
    DImageButton* m_calendarIcon = new DImageButton(this);
    m_calendarIcon->setFixedSize(24, 24);
    m_calendarIcon->setHoverPic(":/resources/icon/calendar.png");
    m_calendarIcon->setNormalPic(":/resources/icon/calendar.png");
    m_calendarIcon->setPressPic(":/resources/icon/calendar.png");

    m_festivalLabel = new QLabel(this);
    m_festivalLabel->setText(m_festival);
    m_yearLabel = new QLabel(this);
    m_yearLabel->setText(QString(tr("%1 year")).arg(m_year));

    m_monthLabel = new QLabel(this);
    m_monthLabel->setText(QString(tr("%1 month").arg(m_month)));
    m_yearLeftBtn = new LeftArrowButton(this);
    m_yearRightBtn = new RightArrowButton(this);

    m_monthLeftBtn = new LeftArrowButton(this);
    m_monthRightBtn = new RightArrowButton(this);

    m_layout = new QHBoxLayout;
    m_layout->setMargin(0);
    m_layout->setSpacing(0);
    m_layout->addSpacing(18);
    m_layout->addWidget(m_calendarIcon);
    m_layout->addStretch(1);
    m_layout->addWidget(m_festivalLabel);
    m_layout->addStretch(1);
    m_layout->addWidget(m_yearLeftBtn);
    m_layout->addSpacing(5);
    m_layout->addWidget(m_yearLabel);
    m_layout->addSpacing(5);
    m_layout->addWidget(m_yearRightBtn);
    m_layout->addSpacing(20);
    m_layout->addWidget(m_monthLeftBtn);
    m_layout->addSpacing(5);
    m_layout->addWidget(m_monthLabel);
    m_layout->addSpacing(5);
    m_layout->addWidget(m_monthRightBtn);
    m_layout->addSpacing(130);
    setLayout(m_layout);

    setStyleSheet("QLabel{font-family:SourceHanSansCN-Normal;font-size:14px;}");

    connect(m_yearLeftBtn, &LeftArrowButton::leftArrowClicked, this, &CalendarTitleBarWidget::setYearIncrease);
    connect(m_yearRightBtn, &RightArrowButton::rightArrowclicked, this, &CalendarTitleBarWidget::setYearIncrease);
    connect(m_monthLeftBtn, &LeftArrowButton::leftArrowClicked, this, &CalendarTitleBarWidget::setMonthIncrease);
    connect(m_monthRightBtn, &RightArrowButton::rightArrowclicked, this, &CalendarTitleBarWidget::setMonthIncrease);
}

void CalendarTitleBarWidget::setFestival(const QString &festival) {
    m_festival = festival;
    m_festivalLabel->setText(m_festival);
    update();
}

void CalendarTitleBarWidget::setCurrentYearMonth(int yearNum, int monthNum) {
    m_year = yearNum;
    m_month = monthNum;
    m_yearLabel->setText(QString(tr("%1 year")).arg(m_year));
    m_monthLabel->setText(QString(tr("%1 month").arg(m_month)));
}

void CalendarTitleBarWidget::setYearIncrease(bool increase) {
    if (increase) {
        m_year+=1;
    } else {
        m_year-=1;
    }
    m_yearLabel->setText(QString(tr("%1 year")).arg(m_year));

    emit currentYearMonthChanged(m_year, m_month);
}

void CalendarTitleBarWidget::setMonthIncrease(bool increase) {
    if (increase) {
        if (m_month<12) {
            m_month+=1;
        } else {
            m_month=1;
            m_year+=1;
        }
    } else {
        if (m_month==1) {
            m_month=12;
            m_year-=1;
        } else {
            m_month-=1;
        }
    }

    m_yearLabel->setText(QString(tr("%1 year")).arg(m_year));
    m_monthLabel->setText(QString(tr("%1 month").arg(m_month)));
    emit currentYearMonthChanged(m_year, m_month);
}
CalendarTitleBarWidget::~CalendarTitleBarWidget() {

}
