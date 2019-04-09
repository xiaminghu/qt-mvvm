// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "editorfactory.h"
#include "comboproperty.h"
#include "combopropertyeditor.h"
#include "sessionitem.h"
#include "viewitem.h"
#include "viewmodel.h"
#include <QDebug>
#include <QModelIndex>

using namespace ModelView;

namespace
{

const SessionItem* itemFromIndex(const QModelIndex& index)
{
    auto model = dynamic_cast<const ViewModel*>(index.model());
    return model ? model->sessionItemFromIndex(index) : nullptr;
}

bool isComboProperty(const QVariant& variant)
{
    return variant.canConvert<ComboProperty>();
}

} // namespace

EditorFactory::EditorFactory() {}

CustomEditor* EditorFactory::createEditor(const QModelIndex& index, QWidget* parent) const
{
    CustomEditor* result(nullptr);

    if (auto item = itemFromIndex(index))
        return createEditor(item, parent);

    return result;
}

CustomEditor* EditorFactory::createEditor(const SessionItem* item, QWidget* parent) const
{
    if (!item)
        return nullptr;

    CustomEditor* result(nullptr);

    if (isComboProperty(item->data(ItemDataRole::DATA))) {
        result = new ComboPropertyEditor;
        qDebug() << "EditorFactory::createEditor():" << item << result;
    }

    if (result)
        result->setParent(parent);

    return result;
}

//! Returns true if the index data has known (custom) convertion to string.

bool EditorFactory::hasStringRepresentation(const QModelIndex& index)
{
    auto variant = index.data();
    if (isComboProperty(variant))
        return true;

    return false;
}

//! Provides string representation of index data.

std::string EditorFactory::toString(const QModelIndex& index)
{
    auto variant = index.data();
    if (isComboProperty(variant))
        return variant.value<ComboProperty>().label();

    return {};
}