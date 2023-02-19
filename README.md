# Quakespasm-CVmod
Custom fork with none Quake-y movements and other weird things.

Developing for a melee combat focused mod. Since some things are impossible in QC, I decided to add some functions to the source port itself. Good thing is, that this really gives freedom. Bad thing is, the mod will need this specific fork of Quakespasm-Spiked.

Planned changes:  
-Movement code:  
        + Bunny hopping can be disabled (sv_nobhop)  
        + Input vector normalizing: no more faster diagonal movement, not even when the player is moving lower than specified by sv_maxspeed.  
        + The sv_maxspeed has a secondary, sv_maxsidespeed and an sv_backspeed variable for strafe and backwards speed limitation
        + Mouse aiming / turning speed can be limited 
		+ Slight acceleration from standing and direction changing. Added for my mod that relies on dodging, but quick direction changes would make it too easy. So a dedicated dodge is advised to be used which costs stamina. The little added acceleration feature makes movement a bit more realistic
		! Stop sliding on slopes at all. Currently, since gravity is applied all the time and the nature of collision in the Quake code relies on sliding on all surfaces, if the player is pushed down, the player slides on even the smallest slope. To be fixed.
		! Better staircase code is needed. That's it. 
		
		
		

-Visuals:  
        + Per entity texture animation speed changes
		+ Model animation interpolation can be changed through QC. No more 10 fps animation speed limit. It can be anything and can be adjusted on the fly. Can be tied to "nextthink" for example. 
        * Better chase camera  
		/ Work in progress, more chase camera options, including orbit camera, camera relative movement, etc...
        / More to add...  
		! Fullbright texture colors are not working, looking into it and will be fixed soon.
		! Maybe a better access to camera would be nice for QC. But that also means lots of QC related changes too. But I think it's worth it. 
		! Sword trails would be nice. Or any kind of trail effects, easily accessible from QC. 
	
-Sounds:  
        + Footstep sounds based on surface types. Using a system similar to what Half-Life 1 has. Materials are definited in a materials.def file. Custom textures need to be added in there. It only reads the first 8 characters (special characters for transparency, water, etc... ignored).
		For example, adding metalplate_1 will match to metalplate_2, metalplat, metalpla1 so you don't need to add all of those if the first 8 characters match.
		
	
-Various  
        / More melee based things  

-Models
		+ Added an ugly md3x model format support that is basically md3 for now, but stores tags in euler angles. A Blender exporter has been written for these modifications. The tag data (tag position and rotation) can be accessed through QC. Multiple tags are supported. Tag position / rotation interpolation is done through QC code. Probably I'll add more features to the model format to distinguish itself more from normal md3 and add extra features to it. Probably vertex color data will be added (to use it with shaders for example)
		! md3 / md3x model loading needs to be changed / fixed, bloated with some unnecessary lines currently.

Legend:  
+: already added  
-: removed  
*: changed  
/: to be added  
!: to be changed / fixed
