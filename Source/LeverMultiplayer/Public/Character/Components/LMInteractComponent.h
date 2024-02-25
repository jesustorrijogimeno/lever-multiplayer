// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMInteractComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEVERMULTIPLAYER_API ULMInteractComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Collision Settings")
	float Radius;
	UPROPERTY(EditDefaultsOnly, Category="Collision Settings")
	float Distance;
	UPROPERTY(EditDefaultsOnly, Category="Collision Settings")
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	bool CanInteract() const;
	void ManageFocus();
	void CalculateVectors(FVector& OutStart, FVector& OutEnd) const;
	bool TryCollide(TArray<FHitResult>& OutHits) const;
	void ManageUI(const AActor* Found) const;
	void DebugLine(bool bIsHit, const FVector& Start, const FVector& End) const;
	void DebugHit(bool bIsHit, const FHitResult& Hit) const;

	UFUNCTION(Server, Reliable)
	void ServerInteract(AActor* InteractableActor);
	
	UPROPERTY()
	AActor* CurrentInteractable;
public:
	// Sets default values for this component's properties
	ULMInteractComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Interact();
private:
	UPROPERTY()
	TObjectPtr<AActor> Owner;
};
