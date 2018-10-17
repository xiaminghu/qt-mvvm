// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef COMMANDSERVICE_H
#define COMMANDSERVICE_H

#include "mvvm_types.h"
#include <memory>

class SessionModel;
class QUndoStack;
class QUndoCommand;
class SessionItem;
class QVariant;

//! Provides undo/redo for all commands of SessionModel.

class CommandService
{
public:
    CommandService(SessionModel* model);

    void setUndoRedoEnabled(bool value);

    void push(QUndoCommand* command);

    SessionItem* insertNewItem(const model_type& modelType, SessionItem* parent, int row);

    bool setData(SessionItem* item, const QVariant& value, int role);

    QUndoStack* undoStack() const;

private:
    bool provideUndo() const;

    SessionModel* m_model;
    std::unique_ptr<QUndoStack> m_commands;
};

#endif