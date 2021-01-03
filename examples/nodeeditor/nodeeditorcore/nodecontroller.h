// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODECONTROLLER_H
#define NODECONTROLLER_H

//! Node editor: original code is taken from
//! http://algoholic.eu/qnodeseditor-qt-nodesports-based-data-processing-flow-editor/
//! Copyright (c) 2012, STANISLAW ADASZEWSKI

#include <QObject>

class QGraphicsScene;
class QGraphicsSceneMouseEvent;

namespace NodeEditor {

class NodeConnection;
class NodePort;

//! The main controller of NodeEditor machinery. Listens to mouse events of the graphics scene,
//! updates connections between ports.

class NodeController : public QObject {
public:
    NodeController(QGraphicsScene* scene);

    bool eventFilter(QObject* object, QEvent* event);

    NodePort* findPort(const QPointF& pos);

signals:
    void connectionIsEstablished(NodeConnection*);

private:
    bool processMousePress(QGraphicsSceneMouseEvent* event);
    bool processMouseMove(QGraphicsSceneMouseEvent* event);
    bool processMouseRelease(QGraphicsSceneMouseEvent* event);

    QGraphicsScene* m_scene{nullptr};
    NodeConnection* m_conn{nullptr};
};

} // namespace NodeEditor

#endif // NODECONTROLLER_H
