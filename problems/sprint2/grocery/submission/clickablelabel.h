#pragma once

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>

class ClickableLabel : public QLabel
{
public:
    ClickableLabel(QWidget *parent = nullptr) : QLabel(parent) {}

    void SetCountLabel(QLabel* label) {
        count_label_ = label;
        ShowCount();
    }

    int GetSelectedCount() const {
        return count_;
    }

    void SetSelectedCount(int new_count) {
        count_ = new_count;
        ShowCount();
    }

    void Inc() {
        count_++;
        ShowCount();
    }

private:
    void ShowCount() {
        auto font = this->font();
        font.setBold(count_ > 0);
        setFont(font);

        if (!count_label_) {
            return;
        }
        count_label_->setText(QString::number(count_));
    }

protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton)
        {
            count_++;
        }
        else if (event->button() == Qt::RightButton)
        {
            count_ = std::max(0, count_ - 1);
        }

        ShowCount();

        QLabel::mousePressEvent(event);
    }

private:
    QLabel* count_label_ = nullptr;
    int count_ = 0;
};
