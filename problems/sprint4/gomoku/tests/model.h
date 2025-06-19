#pragma once

#include <vector>
#include <QString>

enum class Symbol {
    kEmpty = ' ',
    kCross = 'x',
    kNought = 'o'
};

inline QString ToQString(Symbol s) {
    return QChar(static_cast<char>(s));
}

inline Symbol ToSymbol(const QString &s) {

    if (s == "x") {
        return Symbol::kCross;
    }
    if (s == "o") {
        return Symbol::kNought;
    }
    return Symbol::kEmpty;
}

class Model {
public:
    Model() : Model(0,0) {}
    Model(size_t size_x, size_t size_y) {
        size_ = {size_x, size_y};
        reset();
    }

    void Reset(size_t field_size_x, size_t field_size_y) {
        size_ = {field_size_x, field_size_y};
        reset();
    }

    Symbol DoMove(size_t, size_t) {
        return do_move_symbol_;
    }

    Symbol GetNextPlayer() const {
        return next_move_;
    }

    std::optional<Symbol> GetWinner() const {
        return winner_;
    }

    std::vector<std::pair<size_t, size_t>> GetWinnerPath() const {
        return winner_path_;
    }

    static void reset() {
        next_move_ = Symbol::kCross;
        was_reset = true;
        winner_path_.clear();
        winner_ = {};
    }

    static void setNextMove(Symbol next_move) {
        next_move_ = next_move;
    }

    static void setWinner(std::optional<Symbol> winner) {
        winner_ = winner;
    }

    static void setWinnerPath(const std::vector<std::pair<size_t, size_t>>& winner_path) {
        winner_path_ = winner_path;
    }

    static void setDoMove(Symbol next_move) {
        do_move_symbol_ = next_move;
    }

    static std::pair<size_t, size_t> getSize() {
        return size_;
    }

    static bool getWasReset() {
        const auto value = was_reset;
        was_reset = false;
        return value;
    }

private:
    static inline std::pair<size_t, size_t> size_ = {0,0};
    static inline Symbol next_move_ = Symbol::kCross;
    static inline std::optional<Symbol> winner_ = {};
    static inline std::vector<std::pair<size_t, size_t>> winner_path_ = {};

    static inline Symbol do_move_symbol_;
    static inline bool was_reset = false;
};
