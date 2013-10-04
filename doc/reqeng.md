Requirements Document
=====================

A document justifying what we want and what we need to implement it,
aiding in the attempt to scope the order of magnitude of a task. Each
subchapter is a requirement which enhanches the code as justified in
rationale. The fit criterion is how one can see whether it works or not.
Dependencies list what must be done first before this can be properly
implemented.

The result shall be easily integratable with VegaStrike
-------------------------------------------------------
*Rationale*:
From its very conception it is supposed to create an Economy for
vegastrike. Easy integration is key in actually doing it.

*Fit Criterion*:
Someone takes upon himself the task to integrate this with Vegastrike.

*Dependencies*:
* Outsiders can interact with the Economy


Outsiders can interact with the Economy
---------------------------------------
*Rationale*:
The player acts outside of the Economy. Other non-economic entities may
be useful for story purposes.

*Fit Criterion*:
A base can be accessed and traded with by an entity outside the Economy.

The Economy can generate news.
------------------------------
*Rationale*:
Global news reporting actual shortages and abundances is useful for
traders, and can give a player a better immension into the game.

*Fit Criterion*:
The Economy can be generate reports of certain conditions with
information about the location, Cargo in question and faction involved
for the news generator to build a story from.

The Economy can generate Cargo.
-------------------------------
*Rationale*:
This breaks the stalemate from having all possible Cargo transported.
One can choose to just deliver stuff in one system or just one Cargo
catagory and still have plenty of oppertunities.

*Fit Criterion*:
In order to have a working Economy, Cargo of one type needs to be able
to be turned into Cargo of another type.

*Implementation*:
* FactoryTest::testProduce

Economy trading can be interupted.
----------------------------------
*Rationale*:
Not all Cargo arrives. That is the essential idea of blockades and why
pirates are annoying. and it provides an interaction with the universe.

*Fit Criterion*:
It is possible for traded Cargo to not arrive.

*Dependencies*:
* The Economy can trade Cargo

Cargo travels by ship.
----------------------
*Rationale*:
Trading Cargo is nice, but it still has to go from point A to point B.
Barring the presence of inter-system and inter-universe transport
devices, the probably need to go by ship, and can possibly not arrive.
Also, this allows the player a view on the economy outside from the
trading window and may eliminate the need for random ships for sake of
population.

*Fit Criterion*:
Cargo transferred between bases is first transferred from Base A to a
ship, and from the ship to point B.

The Economy can trade Cargo.
----------------------------
*Rationale*:
Having one global production is fine and all, having individual bases
interact with eachother dynamically gives the opportunity to influence
the transactions.

*Fit Criterion*:
A function exists which moves Cargo from one point to another
