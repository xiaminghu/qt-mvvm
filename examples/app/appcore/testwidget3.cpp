// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "testwidget3.h"
#include "standardviewmodels.h"
#include "itemstreeview.h"
#include "propertyeditor.h"
#include "toy_includes.h"
#include "viewitem.h"
#include <QBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QTreeView>
#include <QUndoView>

namespace
{
const QString text = "Undo/Redo basics.\n"
                     "Tree view on the left is looking on our ViewModel. Use right mouse button "
                     "on the left view to add/remove items, "
                     "or just modify values of items. View on the right displays command stack.";
}

using namespace ModelView;

TestWidget3::TestWidget3(QWidget* parent)
    : QWidget(parent), m_defaultTreeView(new ItemsTreeView), m_topItemView(new ItemsTreeView),
      m_subsetTreeView(new ItemsTreeView), m_undoView(new QUndoView),
      m_propertyEditor(new PropertyEditor), m_sessionModel(new ToyItems::SampleModel)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);

    mainLayout->addLayout(create_top_layout());

    auto hlayout = new QHBoxLayout;
    hlayout->addLayout(create_left_layout());
    hlayout->addLayout(create_middle_layout());
    hlayout->addLayout(create_right_layout());
    mainLayout->addLayout(hlayout);

    init_session_model();
    init_default_view();
    init_topitems_view();
    init_subset_view();

    setLayout(mainLayout);
}

TestWidget3::~TestWidget3() = default;

void TestWidget3::onContextMenuRequest(const QPoint& point)
{
    auto treeView = qobject_cast<QTreeView*>(sender());

    auto item = item_from_view(treeView, point);
    auto taginfo = item->parent()->tagIndexOfItem(item);

    QMenu menu;

    // inserting item of same type after given item
    auto addItemAction = menu.addAction("Add item");
    auto add_item = [&]() {
        m_sessionModel->insertNewItem(item->modelType(), item->parent(), taginfo.first,
                                      taginfo.second + 1);
    };
    connect(addItemAction, &QAction::triggered, add_item);

    // removing item under the mouse
    auto removeItemAction = menu.addAction("Remove item");
    auto remove_item = [&]() {
        m_sessionModel->removeItem(item->parent(), taginfo.first, taginfo.second);
    };
    connect(removeItemAction, &QAction::triggered, remove_item);

    menu.exec(treeView->mapToGlobal(point));
}

//! Inits session model with some test content.

void TestWidget3::init_session_model()
{
    auto multi_layer = m_sessionModel->insertNewItem(ToyItems::Constants::MultiLayerType);
    auto layer = m_sessionModel->insertNewItem(ToyItems::Constants::LayerType, multi_layer);
    m_sessionModel->insertNewItem(ToyItems::Constants::ParticleType, layer);

    m_sessionModel->insertNewItem(ToyItems::Constants::LayerType, multi_layer);

    m_sessionModel->insertNewItem(ToyItems::Constants::InterferenceType);

    m_sessionModel->setUndoRedoEnabled(true);
    m_undoView->setStack(m_sessionModel->undoStack());
}

//! Returns SessionItem corresponding to given coordinate in a view.

SessionItem* TestWidget3::item_from_view(QTreeView* view, const QPoint& point)
{
    QModelIndex index = view->indexAt(point);
    auto item = m_defaultTreeView->viewModel()->itemFromIndex(index);
    auto viewItem = dynamic_cast<ViewItem*>(item);
    Q_ASSERT(viewItem);
    return viewItem->item();
}

void TestWidget3::init_default_view()
{
    m_defaultTreeView->setViewModel(Utils::CreateDefaultViewModel(m_sessionModel.get()));

    connect(m_defaultTreeView, &ItemsTreeView::itemSelected, [this](SessionItem* item) {
        m_subsetTreeView->setRootSessionItem(item);
        m_propertyEditor->setItem(item);
        m_topItemView->setSelected(item);
    });

    m_defaultTreeView->treeView()->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_defaultTreeView->treeView(), &QTreeView::customContextMenuRequested, this,
            &TestWidget3::onContextMenuRequest);
}

void TestWidget3::init_topitems_view()
{
    m_topItemView->setViewModel(Utils::CreateTopItemsViewModel(m_sessionModel.get()));
    connect(m_topItemView, &ItemsTreeView::itemSelected,
            [this](SessionItem* item) { m_defaultTreeView->setSelected(item); });
}

void TestWidget3::init_subset_view()
{
    m_subsetTreeView->setViewModel(Utils::CreateDefaultViewModel(m_sessionModel.get()));
}

QBoxLayout* TestWidget3::create_top_layout()
{
    auto result = new QHBoxLayout;
    auto label = new QLabel(this);
    label->setText(text);
    label->setWordWrap(true);
    result->addWidget(label);
    return result;
}

QBoxLayout* TestWidget3::create_left_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_defaultTreeView);
    return result;
}

QBoxLayout* TestWidget3::create_middle_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_topItemView);
    result->addWidget(m_subsetTreeView);
    return result;
}

QBoxLayout* TestWidget3::create_right_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_undoView);
    result->addWidget(m_propertyEditor);
    return result;
}
