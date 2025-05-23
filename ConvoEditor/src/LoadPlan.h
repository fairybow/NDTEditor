#pragma once

#include <QJsonObject>
#include <QJsonValue>
#include <QList>
#include <QObject>
#include <QSet>
#include <QString>
#include <QStringList>

#include "Coco/Utility.h"

#include "Keys.h"

class LoadPlan
{
public:
    struct Item
    {
        QString role{};
        QString speech{};
        bool eot = true;
    };

    bool isNull() const noexcept
    {
        return items_.isEmpty();
    }

    void add(const QJsonValue& jsonValue)
    {
        auto object = jsonValue.toObject();
        auto role = object[Keys::ROLE].toString();

        Item item
        {
            role,
            object[Keys::SPEECH].toString(),
            object[Keys::EOT].toBool()
        };

        items_ << item;
        roles_ << role; // Will not add duplicates
    }

    const QList<Item>& items() const noexcept
    {
        return items_;
    }

    QStringList roles() const
    {
        return Coco::Utility::toList(roles_, Coco::Sort::Yes);
    }

private:
    QList<Item> items_{};
    QSet<QString> roles_{};
};
