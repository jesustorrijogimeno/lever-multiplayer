// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/LMGameModeLever.h"
#include "Character/LMCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerStates/LMPlayerStateLever.h"

FString ALMGameModeLever::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
                                        const FString& Options, const FString& Portal)
{
	FString ErrorMsg = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
	if (UGameplayStatics::HasOption(Options, "PlayerName"))
	{
		const FString PlayerName = UGameplayStatics::ParseOption(Options, "PlayerName");
		NewPlayerController->GetPlayerState<ALMPlayerStateLever>()->SetPlayerName(PlayerName);
	}
	return ErrorMsg;
}

void ALMGameModeLever::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if(NewPlayer->HasAuthority())
	{
		Cast<ALMCharacter>(NewPlayer->GetCharacter())->OnRep_PlayerState();
	}
}
