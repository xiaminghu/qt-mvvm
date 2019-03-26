// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef SESSIONITEMTAG_H
#define SESSIONITEMTAG_H

#include "global.h"
#include "taginfo.h"
#include <vector>

namespace ModelView
{

class SessionItem;

//! Holds collection of SessionItem objects related to the same tag.

class CORE_EXPORT SessionItemTag
{
public:
    SessionItemTag(TagInfo tag_info);
    SessionItemTag(const SessionItemTag&) = delete;
    SessionItemTag& operator=(const SessionItemTag&) = delete;
    ~SessionItemTag();

    int childrenCount() const;

    bool insertItem(SessionItem* item, int index = -1);

    SessionItem* takeItem(int index);

    std::vector<SessionItem*> children() const;

    int indexOfChild(SessionItem* child) const;

    SessionItem* itemAt(int index) const;

    std::string name() const;

private:
    int insert_index(const SessionItem* item, int requested_index) const;
    bool maximum_reached() const;
    bool minimum_reached() const;
    bool is_valid_item(const SessionItem* item) const;
    TagInfo m_tag_info;
    std::vector<SessionItem*> m_items;
};

} // namespace ModelView

#endif // SESSIONITEMTAG_H