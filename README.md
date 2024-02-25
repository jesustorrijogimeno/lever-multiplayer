# Lever Multiplayer


## Considerations

For the scene and for the character model/animations I used two plugins:
- Modular dungeon
- SCK_Casual01

In the c++ ULMGameInfoWidget class I have exposed the following in Blueprints:
- Property Offset
- Property ToAttach
- Event ChangeText

In the LMLever c++ class I have exposed the ILMUIShow interface and implemented its functions in Blueprint:
- ShowUI
- DisableUI

Also in the same LMLever c++ class I have exposed the following properties:
- FinalPitch
- StartPitch
- TimeToComplete
- TargetActor

I the LMWall c++ clas I have exposed the following properties:
- FinalZ
- StartZ
- TimeToComplete

In the c++ ULMMenuWidget class I have exposed various functions to be called from the Blueprint:
- HostGame
- JoinGame
- QuitGame

The code I've written in Blueprints has mostly been to UI purposes.

I have done the animation of the lever and the door in C++, since it was requested that almost everything be done in C++, but
it could have been done in Blueprint with a FlipFlop + Timeline for a more organic result.

I have only created one RCP call, and it was in the LMInteractComponent class with the ServerInteract function.
I have handled the rest with variable replication and authority control as can be seen in the following classes:
- LMLever (bLeverActive, OnRepLeverActive)
- LMMap
- LCharacter (OnRep_PlayerState)
- LMGameModeLever (PostLogin)

I have created a command to be able to debug the sphere cast that I use for interaction with the lever. The command is:
- lm.InteractionDebug = true

If you have problems compiling the code in version 5.3 of Unreal, it seems that it is because you have to install a Visual Studio package
-> Individual Components MSVC v143 - VS 2022 C++ x64/x86(v14.36-17.6)