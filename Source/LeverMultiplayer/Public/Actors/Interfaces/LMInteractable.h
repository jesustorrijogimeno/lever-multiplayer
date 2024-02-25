// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LMInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULMInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LEVERMULTIPLAYER_API ILMInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact(APawn* OwnerPawn);
};
