# Quakespasm-CVmod
Custom fork with none Quake-y movements and other weird things.

Developing for a melee combat focused mod. Since some things are impossible in QC, I decided to add some functions to the source port itself. Good thing is, that this really gives freedom. Bad thing is, the mod will need this specific fork of Quakespasm-Spiked.

Planned changes:
-Movement code:
	+ bunny hopping can be disabled (sv_nobhop)
	+ input vector normalizing: no more faster diagonal movement, not even when the player is moving lower than specified by sv_maxspeed.
	+ sv_maxspeed has a secondary, sv_maxsidespeed variable for strafe speed limitation
	+ mouse aiming / turning speed can be limited

-Visuals:
	/ Per entity texture animation speed changes
	/ Better chase camera
	/ More to add...

-Sounds:
	/ Footstep sounds based on surface types

-Various
	/ More melee based things

Legend:
+: already added
-: removed
*: changed
/: to be added
