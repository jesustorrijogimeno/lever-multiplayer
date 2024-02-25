// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/LMMenuWidget.h"
#include "Kismet/GameplayStatics.h"

void ULMMenuWidget::HostGame(const FString PlayerName) const
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(*MapName), true, "?listen?PlayerName=" + PlayerName);
}

void ULMMenuWidget::JoinGame(const FString PlayerName) const
{
	// Here I should get the url from an API or something like that
	UGameplayStatics::OpenLevel(GetWorld(), FName("127.0.0.1"), true, "?PlayerName=" + PlayerName);
}

void ULMMenuWidget::QuitGame() const
{
	UKismetSystemLibrary::QuitGame(
		GetWorld(),
		UGameplayStatics::GetPlayerController(GetWorld(),0),
		EQuitPreference::Type::Quit,
		false);
}

