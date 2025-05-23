/*#pragma once

#include <algorithm>

#include <QLayoutItem>
#include <QList>
#include <QScrollArea>
#include <QSet>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

#include "ElementBlock.h"

/// Next:
/// Changing combo boxes, speech edit, eot check values needs to update the model.
/// However, when does it really need to do this? Do we really need a full
/// model, given that these widgets (the text edit, check box, and combo box)
/// hold state? It's there for us when we need it in the view, so what should we
/// do?

class JsonView : public QWidget
{
    Q_OBJECT

public:
    explicit JsonView(QWidget* parent = nullptr)
        : QWidget(parent)
    {
        mainLayout_ = new QVBoxLayout(this);
        //mainLayout_->setContentsMargins(0, 0, 0, 0);

        // Scroll area setup
        scrollArea_->setWidgetResizable(true);
        scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        // Content widget that holds all blocks
        scrollAreaLayout_ = new QVBoxLayout(scrollAreaContainer_);
        scrollAreaLayout_->setAlignment(Qt::AlignTop);
        scrollAreaLayout_->setSpacing(5);
        scrollArea_->setWidget(scrollAreaContainer_);

        // Set up main layout
        mainLayout_->addWidget(scrollArea_);
    }

    void add(const QString& role, const QString& speech, bool eot)
    {
        auto block = new ElementBlock(scrollAreaContainer_);

        block->setRoles(roles_);
        block->setRole(role);
        block->setSpeech(speech);
        block->setEot(eot);

        scrollAreaLayout_->addWidget(block);

        connect
        (
            block,
            &ElementBlock::roleChangeRequested,
            this,
            &JsonView::onElementBlockRoleChangeRequested_
        );

        connect
        (
            block,
            &ElementBlock::roleAddRequested,
            this,
            &JsonView::onElementBlockRoleAddRequested_
        );
    }

    void clear()
    {
        QLayoutItem* item = nullptr;

        while ((item = scrollAreaLayout_->takeAt(0)) != nullptr)
        {
            if (auto widget = item->widget())
                delete widget;

            delete item;
        }
    }

    void initRoles(const QSet<QString>& roles)
    {
        roles_ = { roles.begin(), roles.end() };
        sortRoles_();

        for (auto i = 0; i < scrollAreaLayout_->count(); ++i)
            if (auto block = elementAt_(i))
                block->setRoles(roles_);
    }

signals:
    void roleChangeRequested(const QString& from, const QString& to);
    void roleAddRequested(const QString& role);

private:
    QVBoxLayout* mainLayout_ = nullptr;
    QVBoxLayout* scrollAreaLayout_ = nullptr;
    
    QScrollArea* scrollArea_ = new QScrollArea(this);
    QWidget* scrollAreaContainer_ = new QWidget(scrollArea_);

    QList<QString> roles_{};

    void sortRoles_()
    {
        std::sort(roles_.begin(), roles_.end());
    }

    ElementBlock* elementAt_(int index) const
    {
        auto item = scrollAreaLayout_->itemAt(index);
        return qobject_cast<ElementBlock*>(item->widget());
    }

private slots:
    void onElementBlockRoleChangeRequested_(const QString& from, const QString& to)
    {
        roles_.removeAll(from);
        roles_ << to;
        sortRoles_();

        for (auto i = 0; i < scrollAreaLayout_->count(); ++i)
        {
            if (auto block = elementAt_(i))
            {
                // Recall current selection
                auto current = block->role();
                block->setRoles(roles_);
                block->setRole((current == from) ? to : current);
            }
        }

        emit roleChangeRequested(from, to);
    }

    void onElementBlockRoleAddRequested_(const QString& role)
    {
        roles_ << role;
        sortRoles_();

        for (auto i = 0; i < scrollAreaLayout_->count(); ++i)
        {
            if (auto block = elementAt_(i))
            {
                // Recall current selection
                auto current = block->role();
                block->setRoles(roles_);
                block->setRole(current);
            }
        }

        emit roleAddRequested(role);
    }
};
*/