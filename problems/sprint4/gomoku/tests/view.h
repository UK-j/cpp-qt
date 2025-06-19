#pragma once
#include <QWidget>
#include <QString>

class View
{

public:
    using Move = std::pair<std::pair<size_t, size_t>, QString>;
    using MoveStyle = std::tuple<std::pair<size_t, size_t>, QString, bool>;
    View(QWidget *parent = nullptr);
    ~View()=default;
    static void SetupField(size_t size_x, size_t size_y);

    void UpdateCell(size_t x, size_t y, QString new_value);
    void SetCellStyle(size_t x, size_t y, const QString& new_color, bool bold);

    static void SetStatus(const QString& status);
    static void SetStatusStyle(const QString& new_color, bool bold);

    void SetMoveCallback(const std::function<void (size_t x,size_t y)>& callback) {
        move_callback_ = callback;
        move_callback_is_set_ = true;
    }

    void SetNewgameCallback(const std::function<void (size_t size_x,size_t size_y)>& callback) {
        newgame_callback_ = callback;
        new_game_callback_is_set_ = true;
    }

    // Test methods

    void show() {
        is_shown_ = true;
    }

    static void move(std::pair<size_t, size_t> pos) {
        move_callback_(pos.first, pos.second);
    }

    static void newgame(size_t x, size_t y) {
        newgame_callback_(x,y);
    }

    static bool getMoveCallbackIsSet() {
        return move_callback_is_set_;
    }

    static bool getNewGameCallbackIsSet() {
        return new_game_callback_is_set_;
    }
    static bool getIsShown() {
        return is_shown_;
    }
    static std::pair<size_t, size_t> getSize() {
        return size_;
    }

    static QString getStatus() {
        return status_;
    }

    static QString getStatusColor() {
        return status_color_;
    }

    static bool getStatusBoldness() {
        return is_status_bold_;
    }

    static void move(size_t x, size_t y) {
        move_callback_(x,y);
    }

    static std::vector<Move> getMoves() {
        return moves_;
    }

    static std::vector<MoveStyle> getMovesStyles () {
        return moves_styles_;
    }

    static void resetMoves() {
        moves_.clear();
    }

    static void resetMovesStyles() {
        moves_styles_.clear();
    }

private:
    static inline std::function<void (size_t x,size_t y)> move_callback_;
    static inline std::function<void (size_t size_x,size_t size_y)> newgame_callback_;


    static inline bool move_callback_is_set_ = false;
    static inline bool new_game_callback_is_set_ = false;
    static inline bool is_shown_ = false;
    static inline std::pair<size_t, size_t> size_ = {0, 0};

    static inline QString status_ = {};
    static inline QString status_color_ = {};
    static inline bool is_status_bold_ = false;

    static inline std::vector<Move> moves_{};
    static inline std::vector<MoveStyle> moves_styles_{};

};
