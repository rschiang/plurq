#ifndef ARRAY_H
#define ARRAY_H

#include <QJsonArray>
#include <QJsonObject>
#include <QIODevice>

namespace Plurq {

class Array
{
public:
    Array(const QJsonArray &array);
    explicit Array(QIODevice *stream);
    explicit Array(const QByteArray &json);

    inline bool valid() const { return m_valid; }
    inline QJsonArray& array() { return m_array; }
    inline QJsonValue operator[](int i) const { return m_array[i]; }

    class iterator {
        friend class Array;
    public:
        iterator& operator++();
        iterator& operator=(const iterator&);
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;
        QJsonObject operator*() const;

    protected:
        iterator(const Array&, int);
        const Array &array;
        int i;
    };

    iterator begin() const;
    iterator end() const;

protected:
    bool m_valid = false;
    QJsonArray m_array;
};

}

#endif // ARRAY_H
