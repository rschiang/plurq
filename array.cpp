#include "array.h"
#include <QJsonDocument>
#include <QDebug>

using namespace Plurq;

Array::Array(const QJsonArray &array)
    : m_valid(true), m_array(array)
{}

Array::Array(QIODevice *stream)
    : Array(stream->readAll())
{}

Array::Array(const QByteArray &json)
{
    QJsonParseError parseError;
    const QJsonDocument doc = QJsonDocument::fromJson(json, &parseError);
    if (parseError.error) {
        qDebug() << "Error parsing JSON array" << parseError.errorString();
        qDebug() << QString::fromUtf8(json.data());
    } else {
        m_array = doc.array();
        m_valid = true;
    }
}

Array::iterator Array::begin() const
{
    return iterator(*this, 0);
}

Array::iterator Array::end() const
{
    return iterator(*this, m_array.count());
}

Array::iterator::iterator(const Array &array, int i)
    : array(array), i(i)
{}
