// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/LMActivatable.h"
#include "LMWall.generated.h"

UCLASS()
class LEVERMULTIPLAYER_API ALMWall : public AActor, public ILMActivatable
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
	float FinalZ;
	UPROPERTY(EditAnywhere, Category="Configuration")
	float StartZ;
	UPROPERTY(EditAnywhere, Category="Configuration")
	float TimeToComplete;
	
	float TimeElapsed;
	float InitialZ;
	float TargetZ;
	bool bInMovement;
	
	void ManageLocation(float DeltaTime);
public:
	// Sets default values for this actor's properties
	ALMWall();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void ManageActivation_Implementation(const bool bIsActive) override;
};
