#include "view.h"


View::View(QWidget *)
{
    move_callback_is_set_ = false;
    new_game_callback_is_set_ = false;
    size_ = {};
    is_shown_ = false;

    status_ = {};
    status_color_ = {};
    is_status_bold_ = false;
}

void View::UpdateCell(size_t x, size_t y, QString new_value) {
    moves_.push_back({{x, y}, new_value});
}

void View::SetupField(size_t size_x, size_t size_y) {
    size_ =  {size_x, size_y};
    resetMoves();
    resetMovesStyles();
}

void View::SetStatus(const QString& new_status) {
    status_ = new_status;
}

void View::SetStatusStyle(const QString& new_color, bool bold) {
    status_color_ = new_color;
    is_status_bold_ = bold;
}

void View::SetCellStyle(size_t x, size_t y, const QString& new_color, bool bold) {
    moves_styles_.push_back({{x, y}, new_color, bold});
}
