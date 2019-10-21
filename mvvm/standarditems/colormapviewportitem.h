// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_COLORMAPVIEWPORTITEM_H
#define MVVM_COLORMAPVIEWPORTITEM_H

#include "viewportitem.h"

namespace ModelView
{

class GraphItem;
class ViewportAxisItem;

/*!
@class ColorMapViewportItem
@brief Container with viewport and collection of ColorMapItem's to plot.
*/

class CORE_EXPORT ColorMapViewportItem : public ViewportItem
{
public:
    static inline const std::string P_XAXIS = "P_XAXIS";
    static inline const std::string P_YAXIS = "P_YAXIS";
    static inline const std::string T_COLORMAP = "T_COLORMAP";
    ColorMapViewportItem();

private:
    virtual std::pair<double, double> data_xrange() const override;
    virtual std::pair<double, double> data_yrange() const override;
};

} // namespace ModelView

#endif // MVVM_COLORMAPVIEWPORTITEM_H
