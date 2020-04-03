// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "importwindow.h"
#include "importdataeditor.h"
#include <QVBoxLayout>

ImportWindow::ImportWindow(QWidget* parent) : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(new ImportDataEditor);
}
