#pragma once

#include <QString>
#include <QTest>

template<> inline char * QTest::toString(const std::string &str)
{
    const auto data = new char[str.size() + 1];
    memcpy(data, str.c_str(), str.size() + 1);
    return data;
}

template <typename T1, typename T2>
inline bool prac_compare(const T1 &t1, const T2 &t2, const char *actual, const char *expected,
                         const char *file, const int line)
{

    return QTest::qCompare(t1, t2, actual, expected, file, line);
}

inline bool prac_compare(const QString &t1, const QString &t2, const char *actual, const char *expected,
                         const char *file, const int line)
{
    return QTest::qCompare(t1.toStdString(), t2.toStdString(), actual, expected, file, line);
}

template <typename T2>
inline bool prac_compare(const QString &t1, const T2 &t2, const char *actual, const char *expected,
                         const char *file, const int line)
{

    return QTest::qCompare(t1.toStdString(), t2, actual, expected, file, line);
}

template <typename T2>
inline bool prac_compare(const QString &t1, const T2 *t2, const char *actual, const char *expected,
                         const char *file, const int line)
{

    return QTest::qCompare(t1.toStdString(), t2, actual, expected, file, line);
}

template <typename T2>
inline bool prac_compare(const QString &t1, const T2 t2, const char *actual, const char *expected,
                         const char *file, const int line)
{

    return QTest::qCompare(t1.toStdString(), t2.toStdString(), actual, expected, file, line);
}

#define PRAC_COMPARE(actual, expected) \
do {\
    if (!prac_compare(actual, expected, #actual, #expected, __FILE__, __LINE__))\
    return;\
} while (false)

template <typename T1, typename T2>
inline bool prac_compare2(const T1 &t1, const T2 &t2, const char *actual, const char *expected, const char *msg,
                         const char *file, const int line)
{
    return QTest::compare_helper(t1 == t2, msg,
                                  [t1] { return QTest::toString(t1); }, [t2] { return QTest::toString(t2); },
                                  actual, expected, file, line);
}

inline bool prac_compare2(const QString &t1, const QString &t2, const char *actual, const char *expected, const char *msg,
                         const char *file, const int line)
{
    return prac_compare2(t1.toStdString(), t2.toStdString(), actual, expected, msg, file, line);
}

template <typename T2>
inline bool prac_compare2(const QString &t1, const T2 &t2, const char *actual, const char *expected, const char *msg,
                         const char *file, const int line)
{
    return prac_compare2(t1.toStdString(), t2, actual, expected, msg, file, line);

}

template <typename T2>
inline bool prac_compare2(const QString &t1, const T2 *t2, const char *actual, const char *expected, const char *msg,
                         const char *file, const int line)
{
    return prac_compare2(t1.toStdString(), t2, actual, expected, msg, file, line);
}


template <typename T2>
inline bool prac_compare2(const QString &t1, const T2 t2, const char *actual, const char *expected, const char *msg,
                         const char *file, const int line)
{
    return prac_compare2(t1.toStdString(), t2, actual, expected, msg, file, line);
}

#define PRAC_COMPARE2(actual, expected, message) \
do {\
    if (!prac_compare2(actual, expected, #actual, #expected, static_cast<const char *>(message), __FILE__, __LINE__))\
    return;\
} while (false)
