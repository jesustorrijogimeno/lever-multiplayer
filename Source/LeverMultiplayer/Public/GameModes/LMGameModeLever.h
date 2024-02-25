// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LMGameModeLever.generated.h"

/**
 * 
 */
UCLASS()
class LEVERMULTIPLAYER_API ALMGameModeLever : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = TEXT("")) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
