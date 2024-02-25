// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LMActivatable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULMActivatable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LEVERMULTIPLAYER_API ILMActivatable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ManageActivation(const bool bIsActive);
};
