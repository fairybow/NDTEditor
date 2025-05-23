/*#pragma once

#include <memory>

#include <QObject>
#include <QStack>

#include "Command.h"

/// @warning These function more as a record (or a command-on-redo-only). We are
/// not intercepting user input, merely observing and recording for reuse
class CommandStack : public QObject
{
    Q_OBJECT

public:
    explicit CommandStack(QObject* parent = nullptr)
        : QObject(parent)
    {
    }

    ~CommandStack() { clear(); }

    void push(std::unique_ptr<Command> command)
    {
        // Clear the redo stack when a new command is pushed
        qDeleteAll(redos_);
        redos_.clear();

        // Execute the command
        //command->execute();

        connect
        (
            command.get(),
            &Command::invalidated,
            this,
            &CommandStack::onCommandInvalidated_
        );

        // Add to undo stack
        undos_.push(command.release());

        emit canUndoChanged(!undos_.isEmpty());
        emit canRedoChanged(!redos_.isEmpty());
    }

    void undo()
    {
        if (canUndo())
        {
            auto command = undos_.pop();
            command->undo();
            redos_.push(command);

            emit canUndoChanged(!undos_.isEmpty());
            emit canRedoChanged(!redos_.isEmpty());
        }
    }

    void redo()
    {
        if (canRedo())
        {
            auto command = redos_.pop();
            command->execute();
            undos_.push(command);

            emit canUndoChanged(!undos_.isEmpty());
            emit canRedoChanged(!redos_.isEmpty());
        }
    }

    bool canUndo() const noexcept { return !undos_.isEmpty(); }
    bool canRedo() const noexcept { return !redos_.isEmpty(); }

    void clear()
    {
        qDeleteAll(undos_);
        qDeleteAll(redos_);
        undos_.clear();
        redos_.clear();

        emit canUndoChanged(false);
        emit canRedoChanged(false);
    }

signals:
    void canUndoChanged(bool canUndo);
    void canRedoChanged(bool canRedo);

private:
    QStack<Command*> undos_{};
    QStack<Command*> redos_{};

private slots:
    void onCommandInvalidated_(Command* command)
    {
        auto undo_index = undos_.indexOf(command);

        if (undo_index > -1)
        {
            undos_.remove(undo_index);
            delete command;
            emit canUndoChanged(!undos_.isEmpty());
            return;
        }

        auto redo_index = redos_.indexOf(command);

        if (redo_index > -1)
        {
            redos_.remove(redo_index);
            delete command;
            emit canRedoChanged(!redos_.isEmpty());
        }
    }
};
*/