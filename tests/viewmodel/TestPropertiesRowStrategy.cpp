#include "google_test.h"
#include "propertiesrowstrategy.h"
#include "sessionitem.h"
#include "vectoritem.h"
#include "viewdataitem.h"

using namespace ModelView;

class TestPropertiesRowStrategy : public ::testing::Test
{
public:
    ~TestPropertiesRowStrategy();
};

TestPropertiesRowStrategy::~TestPropertiesRowStrategy() = default;

TEST_F(TestPropertiesRowStrategy, initialState)
{
    PropertiesRowStrategy strategy({});
    EXPECT_EQ(strategy.constructRow(nullptr).size(), 0);
    EXPECT_EQ(strategy.columnCount(), 0);
    EXPECT_EQ(strategy.horizontalHeaderLabels(), QStringList());
}

//! Checks row construction for standard top level item. It shouldn't generate any rows.

TEST_F(TestPropertiesRowStrategy, topLevelItem)
{
    SessionItem item("model_type");

    PropertiesRowStrategy strategy({});
    auto items = strategy.constructRow(&item);
    EXPECT_EQ(items.size(), 0);
    EXPECT_EQ(strategy.columnCount(), 0);
    EXPECT_EQ(strategy.horizontalHeaderLabels(), QStringList());
}

//! Checks row construction for property item. It shouldn't generate any rows.

TEST_F(TestPropertiesRowStrategy, propertyItem)
{
    SessionItem item("model_type");
    item.setData(42.0, ItemDataRole::DATA);

    PropertiesRowStrategy strategy({});
    auto items = strategy.constructRow(&item);
    EXPECT_EQ(items.size(), 0);
    EXPECT_EQ(strategy.columnCount(), 0);
    EXPECT_EQ(strategy.horizontalHeaderLabels(), QStringList());
}

//! Checks row construction for vector item.
//! There should be 3 view items looking to x, y, z properties.

TEST_F(TestPropertiesRowStrategy, vectorItem)
{
    VectorItem item;

    EXPECT_EQ(item.getItemValue(VectorItem::P_X).toDouble(), 0.0);
    EXPECT_EQ(item.getItemValue(VectorItem::P_Y).toDouble(), 0.0);
    EXPECT_EQ(item.getItemValue(VectorItem::P_Z).toDouble(), 0.0);

    PropertiesRowStrategy strategy({"a", "b", "c"});
    auto items = strategy.constructRow(&item);

    EXPECT_EQ(items.size(), 3);
    EXPECT_EQ(strategy.columnCount(), 3);
    EXPECT_EQ(strategy.horizontalHeaderLabels(), QStringList() << "a" << "b" << "c");

    // views should look at 3 property items
    auto view_x = dynamic_cast<ViewDataItem*>(items.at(0));
    ASSERT_TRUE(view_x != nullptr);
    EXPECT_EQ(view_x->item(), item.getItem(VectorItem::P_X));

    auto view_y = dynamic_cast<ViewDataItem*>(items.at(1));
    ASSERT_TRUE(view_y != nullptr);
    EXPECT_EQ(view_y->item(), item.getItem(VectorItem::P_Y));

    auto view_z = dynamic_cast<ViewDataItem*>(items.at(2));
    ASSERT_TRUE(view_z != nullptr);
    EXPECT_EQ(view_z->item(), item.getItem(VectorItem::P_Z));
}