#include "MockWidgets.h"
#include "sessionitem.h"
#include "itemmapper.h"
#include "sessionmodel.h"
#include "modelmapper.h"

// ----------------------------------------------------------------------------

MockWidgetForItem::MockWidgetForItem(ModelView::SessionItem* item)
    : m_item(nullptr)
{
    setItem(item);
}

MockWidgetForItem::~MockWidgetForItem()
{
    if (m_item)
        m_item->mapper()->unsubscribe(this);
}

void MockWidgetForItem::setItem(ModelView::SessionItem* item)
{
    m_item = item;

    if (m_item == nullptr)
        return;

    // FIXME do we need on ItemDestroy ?
    m_item->mapper()->setOnItemDestroy([this](ModelView::SessionItem* item) {
        m_item = nullptr;
        onItemDestroy(item);
    }, this);

    m_item->mapper()->setOnDataChange([this](ModelView::SessionItem* item, int role) {
        onDataChange(item, role);
    }, this);
}

// ----------------------------------------------------------------------------

MockWidgetForModel::MockWidgetForModel(ModelView::SessionModel* model)
    : m_model(nullptr)
{
    setModel(model);
}

MockWidgetForModel::~MockWidgetForModel()
{
    if (m_model)
        m_model->mapper()->unsubscribe(this);
}

void MockWidgetForModel::setModel(ModelView::SessionModel* model)
{
    m_model = model;

    if (m_model == nullptr)
        return;

    m_model->mapper()->setOnDataChange([this](ModelView::SessionItem* item, int role) {
        onDataChange(item, role);
    }, this);

    m_model->mapper()->setOnRowInserted([this](ModelView::SessionItem* item, int row) {
        onRowInserted(item, row);
    }, this);

    m_model->mapper()->setOnRowRemoved([this](ModelView::SessionItem* item, int row) {
        onRowRemoved(item, row);
    }, this);
}

