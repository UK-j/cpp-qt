#include "magic_horoscope.h"


QString GetAnimalForEasternCalendar(int year) {
    // Используем static-переменную. Это значит, что
    // при любом вызове в ней будет один и тот же объект.
    static const std::vector<QString> years = {
        QStringLiteral("Обезьяны"), QStringLiteral("Петуха"),
        QStringLiteral("Собаки"),   QStringLiteral("Свиньи"),
        QStringLiteral("Крысы"),    QStringLiteral("Быка"),
        QStringLiteral("Тигра"),    QStringLiteral("Кролика"),
        QStringLiteral("Дракона"),  QStringLiteral("Змеи"),
        QStringLiteral("Лошади"),   QStringLiteral("Овцы"),
    };
    return years[year % 12];
}

QString GetElementForEasternCalendar(int year) {
    // Используем static-переменную. Это значит, что
    // при любом вызове в ней будет один и тот же объект.
    static const std::vector<QString> elements = {
        QStringLiteral("металл/белый"),   QStringLiteral("металл/белый"),
        QStringLiteral("вода/синий"),     QStringLiteral("вода/синий"),
        QStringLiteral("дерево/зелёный"), QStringLiteral("дерево/зелёный"),
        QStringLiteral("огонь/красный"),  QStringLiteral("огонь/красный"),
        QStringLiteral("земля/жёлтый"),   QStringLiteral("земля/жёлтый"),
    };
    return elements[year % 10];
}

QString GetAnimalForTibetanCalendar(int year){
    // Используем static-переменную. Это значит, что
    // при любом вызове в ней будет один и тот же объект.
    static const std::vector<QString> years = {
        QStringLiteral("Нефритового столба"),
        QStringLiteral("Гонга"),
        QStringLiteral("Черепахи"),
        QStringLiteral("Кожаного браслета"),
        QStringLiteral("Чёрного быка"),
        QStringLiteral("Новолуния"),
        QStringLiteral("Горячего солнца"),
        QStringLiteral("Монаха"),
        QStringLiteral("Дракона"),
        QStringLiteral("Кобры"),
        QStringLiteral("Хранителя огня"),
        QStringLiteral("Источника"),

    };
    return years[year % 12];
}

QString GetAnimalForZoroastrianCalendar(int year) {
    // Используем static-переменную. Это значит, что
    // при любом вызове в ней будет один и тот же объект.
    static const std::vector<QString> years = {
        QStringLiteral("Барсука"), QStringLiteral("Верблюда"), QStringLiteral("Ежа"),
        QStringLiteral("Лани"), QStringLiteral("Слона"), QStringLiteral("Коня"),
        QStringLiteral("Гепарда"), QStringLiteral("Павлина"), QStringLiteral("Лебедя"),
        QStringLiteral("Рыси"), QStringLiteral("Осла"), QStringLiteral("Белого медведя"),
        QStringLiteral("Орла"), QStringLiteral("Лисицы"), QStringLiteral("Дельфина"),
        QStringLiteral("Вепря"), QStringLiteral("Совы"), QStringLiteral("Сокола"),
        QStringLiteral("Оленя"), QStringLiteral("Барана"), QStringLiteral("Мангуста"),
        QStringLiteral("Волка"), QStringLiteral("Аиста"), QStringLiteral("Паука"),
        QStringLiteral("Змеи"), QStringLiteral("Бобра"), QStringLiteral("Черепахи"),
        QStringLiteral("Сороки"), QStringLiteral("Белки"), QStringLiteral("Ворона"),
        QStringLiteral("Петуха"), QStringLiteral("Быка")
    };
    return years[year % 32];
}

struct MonthItem {
    int from;
    QString label;
};

class DayMarker {
    int DaysPerMonth(int month, int year) {
        if (month == 2) {
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                return 29; // February in a leap year.
            } else {
                return 28; // February in a non-leap year.
            }
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            return 30; // April, June, September, November have 30 days.
        } else {
            return 31; // All other months have 31 days.
        }
    }

public:
    DayMarker(std::vector<std::vector<MonthItem>> items)
        : items_(items) {
    }

    QString Get(int month, int day, int year) {
        if (day > DaysPerMonth(month, year)) {
            return {};
        }
        month -= 1;
        if (day < items_[month].front().from) {
            int total_months = int(items_.size());
            int prev_month = ((month - 1) % total_months + total_months) % total_months;
            return items_[prev_month].back().label;
        }
        for (size_t i = items_[month].size(); i > 0; --i) {
            const auto& item = items_[month][i - 1];
            if (day >= item.from) {
                return item.label;
            }
        }
        return {};
    }

private:
    std::vector<std::vector<MonthItem>> items_;
};

QString GetZodiac(int day, int month, int year) {
    // Используем static-переменную. Это значит, что
    // при любом вызове в ней будет один и тот же объект.
    using MI = MonthItem;
    static DayMarker marker{{
        {MI{20, "Водолей (стихия - воздух)"}},
        {MI{19, "Рыбы (стихия - вода)"}},
        {MI{21, "Овен (стихия - огонь)"}},
        {MI{20, "Телец (стихия - земля)"}},
        {MI{21, "Близнецы (стихия - воздух)"}},
        {MI{21, "Рак (стихия - вода)"}},
        {MI{23, "Лев (стихия - огонь)"}},
        {MI{23, "Дева (стихия - земля)"}},
        {MI{23, "Весы (стихия - воздух)"}},
        {MI{23, "Скорпион (стихия - вода)"}},
        {MI{22, "Стрелец (стихия - огонь)"}},
        {MI{22, "Козерог (стихия - земля)"}},
    }};

    return marker.Get(month, day, year);
}

QString GetTree(int day, int month, int year) {
    // Используем static-переменную. Это значит, что
    // при любом вызове в ней будет один и тот же объект.
    using MI = MonthItem;
    static DayMarker marker{{
        {MI{2, "пихта"}, MI{11, "вяз"}, MI{25, "кипарис"}},
        {MI{4, "тополь"}, MI{9, "кедр"}, MI{19, "сосна"}},
        {MI{1, "ива"}, MI{11, "липa"}, MI{21, "дуб"}, MI{22, "орешник"}},
        {MI{1, "pябина"}, MI{11, "клён"}, MI{21, "орех"}},
        {MI{1, "жасмин"}, MI{15, "каштан"}, MI{25, "ясень"}},
        {MI{4, "граб"}, MI{14, "инжир"}, MI{24, "берёза"}, MI{25, "яблоня"}},
        {MI{5, "пихта"}, MI{15, "вяз"}, MI{26, "кипарис"}},
        {MI{5, "тополь"}, MI{14, "кедр"}, MI{24, "сосна"}},
        {MI{3, "ива"}, MI{13, "липa"}, MI{24, "орешник"}},
        {MI{4, "pябина"}, MI{14, "клён"}, MI{24, "орех"}},
        {MI{3, "жасмин"}, MI{12, "каштан"}, MI{22, "ясень"}},
        {MI{2, "граб"}, MI{12, "инжир"}, MI{23, "яблоня"}},
    }};

    return marker.Get(month, day, year);
}
