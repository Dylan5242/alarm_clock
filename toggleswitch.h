#ifndef TOGGLESWITCH_H
#define TOGGLESWITCH_H

#include <QAbstractButton>

class ToggleSwitch : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked NOTIFY toggled)

public:
    explicit ToggleSwitch(QWidget *parent = nullptr);
    QSize sizeHint() const override;

    bool isChecked() const;
    void setChecked(bool checked);

signals:
    void toggled(bool checked);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool m_checked = false;
};

#endif // TOGGLESWITCH_H
