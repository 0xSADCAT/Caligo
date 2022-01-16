#include "formatter.hpp"

QString MediaElementFormat::format(const QString& path, const QString& title)
{
    assert(not path.isEmpty());

    QString result = path;
    if (not title.isEmpty())
        result += " ## " + title;
    return result;
}
