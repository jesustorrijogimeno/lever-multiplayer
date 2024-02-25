// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/LMInteractable.h"
#include "Interfaces/LMUIShow.h"
#include "LMLever.generated.h"

class ALMWall;

UCLASS()
class LEVERMULTIPLAYER_API ALMLever : public AActor, public ILMInteractable, public ILMUIShow
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BaseMesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditAnywhere, Category="Configuration")
	float FinalPitch;
	UPROPERTY(EditAnywhere, Category="Configuration")
	float StartPitch;
	UPROPERTY(EditAnywhere, Category="Configuration")
	float TimeToComplete;
	UPROPERTY(EditAnywhere, Category="Configuration")
	TObjectPtr<AActor> TargetActor;
	
	float TimeElapsed;
	float InitialPitch;
	float TargetPitch;
	bool bLeverInMovement;

	UPROPERTY(ReplicatedUsing = OnRepLeverActive)
	bool bLeverActive;
	UFUNCTION()
	void OnRepLeverActive();
	
	void ManageLeverRotation(float DeltaTime);
public:
	// Sets default values for this actor's properties
	ALMLever();

	virtual void Interact_Implementation(APawn* OwnerPawn) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
