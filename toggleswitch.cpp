#include "toggleswitch.h"
#include <QPainter>
#include <QMouseEvent>

ToggleSwitch::ToggleSwitch(QWidget *parent)
    : QAbstractButton(parent)
{
    setCheckable(true);
    setFixedSize(100, 40);
    connect(this, &QAbstractButton::clicked, [this]() {
        m_checked = !m_checked;
        update();
        emit toggled(m_checked);
    });
}

QSize ToggleSwitch::sizeHint() const
{
    return QSize(100, 40);
}

bool ToggleSwitch::isChecked() const
{
    return m_checked;
}

void ToggleSwitch::setChecked(bool checked)
{
    if (m_checked != checked) {
        m_checked = checked;
        update();
        emit toggled(m_checked);
    }
}

void ToggleSwitch::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Фон
    painter.setBrush(m_checked ? QColor("#00c084") : QColor("#e0e0e0"));
    painter.drawRoundedRect(rect(), height()/2, height()/2);

    // Ползунок
    painter.setBrush(Qt::white);
    int sliderSize = height() - 8;
    int x = m_checked ? width() - sliderSize - 4 : 4;
    painter.drawEllipse(x, 4, sliderSize, sliderSize);
}

void ToggleSwitch::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setDown(true);
    }
    QAbstractButton::mousePressEvent(event);
}

void ToggleSwitch::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setDown(false);
        if (rect().contains(event->pos())) {
            setChecked(!m_checked);
        }
    }
    QAbstractButton::mouseReleaseEvent(event);
}
