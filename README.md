# SRB2Kart: Uranus - Nepanus fork

[SRB2Kart](https://srb2.org/mods/) is a kart racing mod based on the 3D Sonic the Hedgehog fangame [Sonic Robo Blast 2](https://srb2.org/), based on a modified version of [Doom Legacy](http://doomlegacy.sourceforge.net/).

## Nepanus Fork
A fork of a fork. This hardcodes many features that I personally enjoy using or I thought would be good customization. btw its pronounced nep-a-nus :^)

## Features (Nepanus)
- Sneaker Extension with mini-turbos (Choose between two types bs and zbl)
- Additive Mini-turbos
- Customizable mini-turbo boost time
- Colorized HUD
- BoostStacking(This is a big one!)
- More to come!
- All added features are toggable via convars

## New CVARs
- sneakerextend Default value: On
- sneakerextendtype Default value: zbl
- additivemt Default value: Off
- bluesparktics Default value: 20
- redsparktics Default value: 50
- rainbowsparktics Default value: 125
- colorizedhud Default value: On
- stacking Default value:	On
- stackingdim Default value: On
- stackingdimval Default value: 1.20
- stackingbrakemod Default value: 0.05
- stacking_sneakerstack Default value: 5
- stacking_sneakerspeedeasy Default value: 0.8317
- stacking_sneakerspeednormal Default value: 0.5
- stacking_sneakerspeedhard Default value: 0.2756
- stacking_sneakeraccel Default value: 8.0
- stacking_invincibilitypeed Default value: 0.375
- stacking_invincibilityaccel Default value: 3.0
- stacking_growspeed Default value: 0.2
- stacking_growaccel Default value: 0.5
- stacking_growmult Default value: 0
- stacking_drfitspeed Default value: 0.25
- stacking_drfitaccel Default value: 4.0
- stacking_startspeed Default value: 0.25
- stacking_startaccel Default value: 6.0
- stacking_hyuudorospeed Default value: 0.1
- stacking_hyuudoroaccel Default value: 0.5
- stacking_speedcap Default value: On
- stacking_speedcapval Default value: 128.0

## New kartstuff data
- k_sneakerstack Current number of active sneaker stacks. Modfifying this will effect stack value
- k_driftstack Cosmetic Stack number. Can be used to see if a specfic boost is active but modifying it won't change how it stacks
- k_startstack ^
- k_invincibilitystack ^
- k_ssstack  ^
- k_totalstacks Value of all current stacks coesmetic or not
- k_ssspeedboost Used to pass through slipstream speedboost to internal stacking system
- k_ssaccelboost Used to pass through slipstream accelboost to internal stacking system
- k_slopespeedboost Used to pass through slopeboost speedboost to internal stacking system
- k_slopeaccelboost Used to pass through slopeboost accelboost to internal stacking system

## Dependencies
- SDL2 (Linux/OS X only)
- SDL2-Mixer (Linux/OS X only)
- libupnp (Linux/OS X only)
- libgme (Linux/OS X only)
- libopenmpt (Linux/OS X only)

## Compiling

See [SRB2 Wiki/Source code compiling](http://wiki.srb2.org/wiki/Source_code_compiling). The compiling process for SRB2Kart is largely identical to SRB2.

## Disclaimer
Kart Krew is in no way affiliated with SEGA or Sonic Team. We do not claim ownership of any of SEGA's intellectual property used in SRB2.
