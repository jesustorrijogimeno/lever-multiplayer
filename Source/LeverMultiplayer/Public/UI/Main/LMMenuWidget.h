// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LMMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEVERMULTIPLAYER_API ULMMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FString MapName = "Lever";
	UFUNCTION(BlueprintCallable, Category="Options")
	void HostGame(FString PlayerName) const;
	UFUNCTION(BlueprintCallable, Category="Options")
	void JoinGame(FString PlayerName) const;
	UFUNCTION(BlueprintCallable, Category="Options")
	void QuitGame() const;
};
