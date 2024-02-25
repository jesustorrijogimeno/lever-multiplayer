// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "LMGameInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEVERMULTIPLAYER_API ULMGameInfoWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void KeepPosition();
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Configuration")
	FVector Offset;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TextInfo;
public:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn=true), Category="Configuration")
	TObjectPtr<AActor> ToAttach;
	UFUNCTION(BlueprintNativeEvent, Category="Events")
	void ChangeText(const FString& NewText);
};
