Class header file: [BWAPI/UnitCommand.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/UnitCommand.h#)

UnitCommand objects are currently used only as arguments to one function - [Unit::issueCommand](Unit#issueCommand.md). While units can be issued commands the normal way via the [Unit](Unit.md) methods (i.e. [Unit::attack](Unit#attack.md)), in some cases you may want to have a function that can process any unit command, such as when you're writing a proxy for BWAPI.



# Named Constructors #
  * attack([Unit](Unit.md)`*` unit, [Position](Misc#Position.md) target, bool shiftQueueCommand = false);
  * attack([Unit](Unit.md)`*` unit, [Unit](Unit.md)`*` target, bool shiftQueueCommand = false);
  * build([Unit](Unit.md)`*` unit, [TilePosition](Misc#TilePosition.md) target, UnitType type);
  * buildAddon([Unit](Unit.md)`*` unit, UnitType type);
  * train([Unit](Unit.md)`*` unit, UnitType type);
  * morph([Unit](Unit.md)`*` unit, UnitType type);
  * research([Unit](Unit.md)`*` unit, [TechType](TechType.md) tech);
  * upgrade([Unit](Unit.md)`*` unit, [UpgradeType](UpgradeType.md) upgrade);
  * setRallyPoint[Position](Position.md)([Unit](Unit.md)`*` unit, [Position](Misc#Position.md) target);
  * setRallyPoint([Unit](Unit.md)`*` unit, [Unit](Unit.md)`*` target);
  * move([Unit](Unit.md)`*` unit, [Position](Misc#Position.md) target, bool shiftQueueCommand = false);
  * patrol([Unit](Unit.md)`*` unit, [Position](Misc#Position.md) target, bool shiftQueueCommand = false);
  * hold[Position](Position.md)([Unit](Unit.md)`*` unit, bool shiftQueueCommand = false);
  * stop([Unit](Unit.md)`*` unit, bool shiftQueueCommand = false);
  * follow([Unit](Unit.md)`*` unit, [Unit](Unit.md)`*` target, bool shiftQueueCommand = false);
  * gather([Unit](Unit.md)`*` unit, [Unit](Unit.md)`*` target, bool shiftQueueCommand = false);
  * returnCargo([Unit](Unit.md)`*` unit, bool shiftQueueCommand = false);
  * repair([Unit](Unit.md)`*` unit, [Unit](Unit.md)`*` target, bool shiftQueueCommand = false);
  * burrow([Unit](Unit.md)`*` unit);
  * unburrow([Unit](Unit.md)`*` unit);
  * cloak([Unit](Unit.md)`*` unit);
  * decloak([Unit](Unit.md)`*` unit);
  * siege([Unit](Unit.md)`*` unit);
  * unsiege([Unit](Unit.md)`*` unit);
  * lift([Unit](Unit.md)`*` unit);
  * land([Unit](Unit.md)`*` unit, [TilePosition](Misc#TilePosition.md) target);
  * load([Unit](Unit.md)`*` unit, [Unit](Unit.md)`*` target, bool shiftQueueCommand = false);
  * unload([Unit](Unit.md)`*` unit, [Unit](Unit.md)`*` target);
  * unloadAll([Unit](Unit.md)`*` unit, bool shiftQueueCommand = false);
  * unloadAll([Unit](Unit.md)`*` unit, [Position](Misc#Position.md) target, bool shiftQueueCommand = false);
  * rightClick([Unit](Unit.md)`*` unit, [Position](Misc#Position.md) target, bool shiftQueueCommand = false);
  * rightClick([Unit](Unit.md)`*` unit, [Unit](Unit.md)`*` target, bool shiftQueueCommand = false);
  * haltConstruction([Unit](Unit.md)`*` unit);
  * cancelConstruction([Unit](Unit.md)`*` unit);
  * cancelAddon([Unit](Unit.md)`*` unit);
  * cancelTrain([Unit](Unit.md)`*` unit, int slot = -2);
  * cancelMorph([Unit](Unit.md)`*` unit);
  * cancelResearch([Unit](Unit.md)`*` unit);
  * cancelUpgrade([Unit](Unit.md)`*` unit);
  * useTech([Unit](Unit.md)`*` unit,[TechType](TechType.md) tech);
  * useTech([Unit](Unit.md)`*` unit,[TechType](TechType.md) tech, [Position](Misc#Position.md) target);
  * useTech([Unit](Unit.md)`*` unit,[TechType](TechType.md) tech, [Unit](Unit.md)`*` target);
  * placeCOP([Unit](Unit.md)`*` unit, [TilePosition](Misc#TilePosition.md) target);

# Methods #

## getType ##
[UnitCommandType](UnitCommandType.md) getType() const;

Returns the type of the command

## getUnit ##
[Unit](Unit.md)`*` getUnit() const;

Returns the unit to which the command has been issued.

## getTarget ##
[Unit](Unit.md)`*` getTarget() const;

Returns the target unit of the command, or null if there is no target unit.

## getTargetPosition ##
[Position](Misc#Position.md) getTargetPosition() const;

Returns the target position of the command, or Positions::None if there is no target position.

## getTargetTilePosition ##
[TilePosition](Misc#TilePosition.md) getTargetTilePosition() const;

Returns the target tile position of the command, or Positions::None if there is no target tile position.

## getUnitType ##
[UnitType](UnitType.md) getUnitType() const;

Returns the unit type of the command, or UnitTypes::None if the command is not of type Build, Build\_Addon?, Train, or Morph.

## getTechType ##
[TechType](TechType.md) getTechType() const;

Returns the tech type of the command, or TechTypes::None if the command is not of type Research, Use\_Tech, Use\_Tech\_Position, or Use\_Tech\_Unit.

## getUpgradeType ##
[UpgradeType](UpgradeType.md) getUpgradeType() const;

Returns the upgrade type of the command, or UpgradeTypes::None if the command is not of type Upgrade.

## getSlot ##
int getSlot() const;

Returns the slot of the command, or -1 if the command is not of type Cancel\_Train\_Slot.

## isQueued ##
bool isQueued() const;

Returns true if the command is a queued command.