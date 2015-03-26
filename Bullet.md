Class header file: [BWAPI/Bullet.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/Bullet.h#)

The Bullet class is used to get information about individual bullets, missiles, spells, and generally any sort of non-melee attack. Unlike Units, Bullet objects are reused after they are destroyed, however the ID of the bullet is updated when it represents a new bullet.

If [Flag::CompleteMapInformation](Misc#Flag.md) is disabled, then a bullet is accessible if and only if it is visible. If a bullet is not visible, [Bullet::exists](Bullet#exists.md) will return false, regardless of whether or not the bullet exists. This is because absolutely no state information on invisible enemy bullets is made available to the AI.

If [Flag::CompleteMapInformation](Misc#Flag.md) is enabled, then all bullets that exist in the game are accessible, and [Bullet::exists](Bullet#exists.md) is accurate for all bullets.

No message similar to [AIModule::onUnitDestroy](AIModule#onUnitDestroy.md) exists for bullets. To determine if a bullet has been destroyed, check to see if exists() is false or getID() has changed to a new value.

Methods:

  * [getID](#getID.md)
  * [getPlayer](#getPlayer.md)
  * [getType](#getType.md)
  * [getSource](#getSource.md)
  * [getPosition](#getPosition.md)
  * [getAngle](#getAngle.md)
  * [getVelocityX](#getVelocityX.md)
  * [getVelocityY](#getVelocityY.md)
  * [getTarget](#getTarget.md)
  * [getTargetPosition](#getTargetPosition.md)
  * [getRemoveTimer](#getRemoveTimer.md)
  * [exists](#exists.md)
  * [isVisible](#isVisible.md)

### getID ###
int getID() const;

Returns a unique ID for this bullet.

### getPlayer ###
[Player](Player.md)`*` getPlayer() const;

Returns the player of the source unit, or NULL if the source unit has been destroyed or is otherwise inaccessible.

### getType ###
[BulletType](BulletType.md) getType() const;

Returns the type of the bullet.

### getSource ###
[Unit](Unit.md)`*` getSource() const;

Returns the unit that fired the bullet. If the unit is inaccessible (such as a cloaked or burrowed enemy unit with no detection around and complete map information disabled), this will return NULL.

### getPosition ###
[Position](Misc#Position.md) getPosition() const;

Returns the position of the bullet, or an invalid position if the bullet is inaccessible.

### getAngle ###
double getAngle() const;

Returns the direction the bullet is facing/traveling in, measured in radians. An angle of 0 means the bullet is facing east/right. If the bullet is inaccessible this will return 0.

### getVelocityX ###
double getVelocityX() const;

Returns the x component of the bullet's velocity, measured in pixels per frame. If the bullet is inaccessible this will return 0.

### getVelocityY ###
double getVelocityY() const;

Returns the y component of the bullet's velocity, measured in pixels per frame. If the bullet is inaccessible this will return 0.

### getTarget ###
[Unit](Unit.md)`*` getTarget() const;

Returns the unit that the bullet is trying to hit. If the unit is inaccessible (such as a cloaked or burrowed enemy unit with no detection around and complete map information disabled), this will return NULL. If the bullet is inaccessible this will return NULL.

### getTargetPosition ###
[Position](Misc#Position.md) getTargetPosition() const;

Returns the target position of the bullet. If the bullet is inaccessible this will return an invalid position.

### getRemoveTimer ###
int getRemoveTimer() const;

Returns the maximum number of frames until this bullet is removed. Generally bullets hit their targets before this timer reaches 0. If the bullet is inaccessible this will return 0.

### exists ###
bool exists() const;

Returns true if the bullet is accessible. If [Flag::CompleteMapInformation](Misc#Flag.md) is enabled, all bullets that actually exist in the game will be accessible. If it is disabled, then only visible bullets will be accessible.

### isVisible ###
bool isVisible() const;

bool isVisible([Player](Player.md)`*` player) const;

Returns true if the bullet is visible.

If [Flag::CompleteMapInformation](Misc#Flag.md) is enabled, you can also specify to which player you want to check visibility for, otherwise [Game::self](Game#self.md) is used.