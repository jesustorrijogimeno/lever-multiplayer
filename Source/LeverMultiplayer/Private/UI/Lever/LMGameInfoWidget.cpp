// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lever/LMGameInfoWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"

void ULMGameInfoWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	KeepPosition();
}

void ULMGameInfoWidget::KeepPosition()
{
	if (!IsValid(ToAttach))
	{
		RemoveFromParent();
		return;
	}

	const FVector ActorLocation = ToAttach->GetActorLocation() + Offset;
	FVector2D ScreenTranslation;
	UGameplayStatics::ProjectWorldToScreen(
		GetOwningPlayer(),
		ActorLocation
		, ScreenTranslation);

	ScreenTranslation /= UWidgetLayoutLibrary::GetViewportScale(this);
	TextInfo->SetRenderTranslation(ScreenTranslation);
}

void ULMGameInfoWidget::ChangeText_Implementation(const FString& NewText)
{
}
