#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include <QString>

struct Formatter
{
    /**
     * @brief Format two strings in one to write to file
     * @param path File path
     * @param title Media title in format "@Author - @Title"
     * @return Formatted string
     */
    virtual QString format(const QString& path, const QString& title) = 0;
};

struct MediaElementFormat : Formatter
{
    QString format(const QString& path, const QString& title) override;
};

#endif // FORMATTER_HPP
