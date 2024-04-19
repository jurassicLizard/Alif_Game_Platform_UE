# Alif

This is a Demonstrator game intended to create a platform for developing top-down squad-based games similar to Commandos with Unreal Engine 5
For learning purposes everything in this demonstrator was written in C++ including UE5s EnhancedInput for responding to key presses. Therefore it can also be used as a simple How-To to showcase how to do things in pure C++ instead of relying on a Hybrid C++/Blueprint Setup.


# Most Important Actor Classes

## Characters
* **ABaseCharacter** : 
 * Contains the base skeleton functionality and configuration for all characters to be placed in the game, any Character in this game will extend this class
* **AMainSquadCharacter** : any Class extending this will inherit all movement functionality. as well as collision capsules. meshes can be adjusted in child accordingly i.e. :
 * Character is selectable with LMB
 * Character is moveable around the world with LMB
 * RMB deselects everything
 * Character has collisions set up and is placeable in world (no meshes yet)
* **TestCharacter** : an example of how to extend AMainSquadCharacter and set it up with Animation and Meshes for a more realistic character. Blueprints can also be used from within the Unreal Editor to extend AMainSquadCharacter for a more UI-Friendly Approach . In this project however the focus was on doing almost everything possible in C++ for learning purposes even if it is not the most efficient way of doing things.

## Items
* **ABaseItem** : any class extending this will inherit base item functionality
 * An ABaseItem can be pickable or non pickable
* **ABaseWeapon** : extends ABaseItem and is meant to supplement it with weapon specific logic (i.e. this can't be a Medkit but something that is a weapon)
* **APrototypeCannon** : extends ABaseWeapon and is meant to be visible in the world by initializing a relevant texture mesh
* **APrototypeRifle** :  extends ABaseWeapon and is meant to be visible in the world by initializing a relevant texture mesh


# Most Important Component Classes that can be attached to actors

## Characters

* **UInventoryCapabilityComponent** : Can be attached to any Child of ABaseCharacter and gives it a simple inventory (i.e. it can carry weapons and items)
* **UPickupCapabilityComponent** : Can be attached to any Child of ABaseCharacter and gives it the capability to pickup floating items in the world 


## Items

* **UFloatingPickableComponent** : This component can be attached to any Child of ABaseItem. Giving it following features : 
 * Can be picked up by Any Character with an UInventoryCapabilityComponent and UPickupCapabilityComponent
 * Floats in the world idly if it is not picked up by any character


# Interfaces 

* **IInventoryCapabilityInterface**
* **IItemIdentificationIterface**
* **IPickupCapabilityInterface**
* **ISelectableActorInterface**

# Implemented Demonstrator


* From the Unreal Editor open the Content/Levels/MainTestMap.umap
* There are two clickable and moveable characters and multiple pickable weapons
 * Characters can be selected with LMB and deselected with RMB for a selection of a second character . LMB also moves around any selected character
 * when a character passes over a floating weapon it holsters the currently equiped weapon on its back and equipes the newly picked up weapon
 * some simple Inverse Kinematics (for example : prone) are available and have been adapted for the ParagonWraith Character from Mixamo


