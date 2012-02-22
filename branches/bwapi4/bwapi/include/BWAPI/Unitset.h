#pragma once
#include <BWAPI/Vectorset.h>
#include <BWAPI/Position.h>
#include <BWAPI/Regionset.h>

namespace BWAPI
{
	class Unit;

	/// @~English
	/// The Unitset is a container for a set of pointers
	/// to Unit objects. It is typically used for groups
	/// of units instead of having to manage each Unit
	/// individually.
	///
	/// @note Because of the efficiency, it is recommended
	/// to use the Unitset over any of the STL containers.
	///
	/// @~
	/// @see Unit, UnitType, UnitSizeType
	class Unitset : public Vectorset<BWAPI::Unit*>
	{
	public:
		/// @~English
		/// The Unitset constructor.
		///
		/// @param initialSize The initial maximum size of
		/// the Unitset before expanding it is necessary.
		/// @~
		Unitset(size_t initialSize = 16);
		
		/// @overload
		/// @~English 
		///
		/// @param other The Unitset to construct this one
		/// from.
		/// @~
		Unitset(const Unitset &other);

		/// @~English
		/// Calculates the average of all valid Unit positions
		/// in this set.
		///
		/// @returns Average Position of all units in the set.
		/// @~
		/// @see Unit::getPosition
		Position getPosition() const;

		/// @~English
		/// Creates a single set containing all units that
		/// are loaded into units of this set.
		///
		/// @returns The set of all loaded units.
		/// @~
		/// @see Unit::getLoadedUnits
		Unitset getLoadedUnits() const;

		/// @~English
		/// Creates a single set containing all the
		/// @Interceptors of all @Carriers in this set.
		///
		/// @returns The set of all @Interceptors .
		/// @~
		/// @see Unit::getInterceptors
		Unitset getInterceptors() const;

		/// @~English
		/// Creates a single set containing all the
		/// @Larvae of all @Hatcheries, @Lairs, and
		/// @Hives in this set.
		///
		/// @returns The set of all @Larvae .
		/// @~
		/// @see Unit::getLarva
		Unitset getLarva() const;

		/// @~English
		/// Sets the client info for every unit
		/// in this set.
		///
		/// @param clientInfo A pointer to client information,
		/// managed by the AI module, or NULL if client 
		/// information is to be cleared.
		/// @~
		/// @see Unit::setClientInfo
		void setClientInfo(void *clientInfo = NULL);

	};
}
