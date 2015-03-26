Class header file: [BWAPI/Order.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/Order.h#)

To get detailed information about what a unit is doing, you can use the Unit::getOrder method, which will return an Order object. Note that a single command, like gather minerals, can consist of several orders ( MoveToMinerals, HarvestMinerals2, MiningMinerals, ReturnMinerals, etc) which will indicate what state the unit is in while executing the command. For information about how to issue commands to units, go to [Unit](Unit.md).

List of all [Orders](Orders.md).

Methods:

  * [getID](#getID.md)
  * [getName](#getName.md)

Non-member methods in Orders namespace:

  * [getOrder](#getOrder.md)
  * [allOrders](#allOrders.md)

### getID ###
int getID();

Returns the unique ID for this order.

### getName ###
std::string getName();

Returns the name of this order.

### getOrder ###
[Order](Order.md) getOrder(std::string name);

Given the name of an order, getOrder() will return the corresponding order object.

### allOrders ###
std::set<[Order](Order.md)>& allOrders();

Returns the set of all the [Orders](Orders.md).