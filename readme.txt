PacGun Version 1 by Team 11
######################################

How to Play
*************************

Best played at 8x8 raster font size!

Controls
================
- Menus
	- Arrow keys to Navigate
	- Space to Select
- In Game
	- Arrow keys to Move
	- Space to Shoot
	- Esc button to pause

Objective
================
- Collect all the pellets in a level or hit the minimum score
- If you hit the minimum score and then lose a life, you move to the next level

Pacman
================
- Your bullets deal 1 damage

Ghosts
================
- Green
	- 1 Damage
	- 1 Health
- Purple
	- 1 Damage
	- 2 Health
- Red
	- 1 Damage
	- 3 Health
	
Power Ups
================
- Blue Star
	- Increase Bullet Movement Speed
- Green Summation Icon
	- 2x Score Multiplier
- Yellow Triangle
	- Increase Bullet Damage
- Red Heart
	- Additional Life
- The player character blinks the colour of the power ups picked ups

Custom Map Creation
*************************
- A Map is comprised of two files
	- .map
	- .aimap

- Creating a map is in a \"What you see is what you get\" fashion!

.map file
=============
- Header Portion
	- Excluded from the physical map.
	- Contains other map details
		- Number of Zones
			- Must be below 10
		- Ghost Details
			- Row 1: Health
			- Row 2: Speed
			- Row 3: Respawn Time
			- Row 4: Zone ID
				- The zone indicated in the .aimap file that the Ghost will be restricted to
			- Must be single digit
			- A column of data = 1 ghost
		- Minimum Score
- Actual "map" Portion
	'#' - Symbol for a wall.
	' ' - Symbol for empty space
	'P' - Symbol for player spawn point. Only 1 may exist on the map.
	'H' - Symbol for a extra life power up.
	's' - Symbol for a increased bullet speed power up.
	'd' - Symbol for a increased bullet damage power up.
	'M' - Symbol for a 2x score multiplier power up.

.aimap file
=============
'#' - Symbol for a wall.
' ' - Symbol for empty space.
'1' to '9' - Symbol for zone where the ghost roams. Corresponds to a Ghost's Zone ID

Mapping Rules
=============
- Map and AIMap size must be equal.
- Zones specified in Map and AIMap files must be equal.
- Zones specified and Zones used by Ghosts in Map file must be equal.
- Number of Zones must be set.
- A spawn point must be set and only 1 can be set.
- A minimum score must be set and only 1 can be set.
- There must be at least 1 pellet on the map.

A template for creating maps is waiting for you in the Custom Maps folder!

Note: If the map is too big, the console might not be able to expand itself big enough as it is still limited by your screen resolution.
      This may cause your map to appear deformed.