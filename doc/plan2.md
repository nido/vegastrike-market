Vegastrike Economy Simplified Algorithm {#mainpage}
=======================================

This is an implemenatation proposal for getting an economy running
within vegastrike. This proposal is based on RedAdders code and text
and contributions by others at 
http://forums.vega-strike.org/viewtopic.php?t=13404

The primary problem this tries to solve is the problem with cargo.
Prices are fixed per base, cargo is regenerated only at startup, and its
distribution makes little sense. Also, it has been suggested that the
vegastrike economy has more influence in the universe itself; from
giving it the ability create missions and ships flying around, to having
the economy production linked into the availability of ships and
weapons.

he latter will give an extra option for the ongoing war between
factions between other then blowing bases to bits. If the parts to make
missles never arrive, no missles can be made and no missles can be
fired.

Further suggestions are giving the player the ability to own a base, in
this case one may want to have the ability to control how and what is
produced. If bases get the ability to send ships with cargo around, the
player could also make use of this ability to get their own base
supplied. This interface may also be useful for sending player fleets
around regardless of owning a base. The principal implementation will
be more restricted, but the suggestions mentioned above should be taken
into account.

Cargo
-----

The principal unit we are working with is Cargo. Cargo has a type (for
example, Iron Ore. Iron ore has a fixed volume and mass and category per
unit; but different amounts of units may be owned by different entities.
The player may have a pile of Hull Patches in his cargo bay, the fighter
barracks may have a very small pile of Hull Patches and there may be a
even bigger stack of it back at the factory where the player for it
from. Each of these piles is a single Cargo. 

Before the economy is integrated into vegastrike itself, it needs to be
able to work with the player just sitting back, so forget any player
involvement from this point on.

CargoHold
---------

CargoHolds are 'containers' of multiple types of cargo. One example
would be the cargo hold on the player ship, another the cargo available
for trade at a base. Factories could have their own pools of cargo
separate from the base trader. Cargo can be added to and deleted from a
CargoHold as well as a Cargo Hold. Removing cargo by any of these
methods will only work if _all_ cargo can be removed. On success, that
function returns true, on failure, it will return false.

ProductionOption
----------------

A ProductionOption represents a possible act of production of a Factory.
A factory may have multiple ProductionOptions available, one of which it
may use in an economic turn. 

Factory
-------

Cargo can be produced. Cargo is produced at a Factory. Factories can
have different ProductionOptions giving different options to produce in
a given turn. For example, a console factory might produce 1, 10 or 100
consoles inputting either 1, 10 or 100 recycled electronics, depending
on the ProductionOption used. ProductionOptions are independent of
eachother, and have a possibility of multiple inputs and outputs. Whilst
not used in the initial economy, it is perfectly possible to have a
factory produce either one good or another from totally different input
cargo.

Base
----

Economically, bases are collections of factories packed together on a
single station. From an economic perspective, Cargo can travel instantly
within a base. Between bases, transfer takes time (and money?).

PriceList
---------

A priceList is an indication of what the prices are.
Initially; are dependant on a price indication (the current base price),
a modifier which can differ from basetype/universe/other(?) and a
quantity modifier.

The price is also dependant on who is requesting it. A base considering
the worth of its own products will get the price as calculated above. A
Player may get charget some space-VAT, and a discount or markup
depending on faction standing. Prices for bases of different factions
may also change depending on mutual standing. Transfer of goods between
bases will also cost depending on distance (and may or may not succeed
due to piracy, accidents and the sorts), but that is to be covered
elsewhere.

Governor
--------

A base is ruled by a Governor which is in charge of making sure a sane
amount of goods is available. The governor is to be responsible for
deciding how many or which goods are to be produced in a particular
factory, though initial factories may use a function choosing a default
production option. Still, Initially this governer is to call these
functions and give the factories access to the correct cargo.




