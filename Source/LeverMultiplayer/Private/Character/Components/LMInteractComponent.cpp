// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Components/LMInteractComponent.h"
#include "Actors/Interfaces/LMInteractable.h"
#include "Actors/Interfaces/LMUIShow.h"

static TAutoConsoleVariable CVarInteraction(TEXT("lm.InteractionDebug"), false, TEXT("Enable Interaction Debug"));

// Sets default values for this component's properties
ULMInteractComponent::ULMInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostUpdateWork;
	Radius = 20.0f;
	Distance = 200.0f;
	CollisionChannel = ECC_WorldDynamic;
}


// Called when the game starts
void ULMInteractComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
}


// Called every frame
void ULMInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ManageFocus();
}

bool ULMInteractComponent::CanInteract() const
{
	return Cast<APawn>(Owner)->IsLocallyControlled();
}

void ULMInteractComponent::ManageFocus()
{
	if (!CanInteract()) return;
	
	TArray<FHitResult> Hits;
	const bool bIsHit = TryCollide(Hits);
	
	AActor* FoundInteractable = nullptr;
	for (FHitResult Hit : Hits)
	{
		DebugHit(bIsHit, Hit);
		AActor* Actor = Hit.GetActor();
		if (!Actor) continue;
		if(!Actor->Implements<ULMInteractable>()) continue;
		FoundInteractable = Actor;
		break;
	}
	
	ManageUI(FoundInteractable);

	if (FoundInteractable != CurrentInteractable)
	{
		CurrentInteractable = FoundInteractable;
	}
}

void ULMInteractComponent::CalculateVectors(FVector& OutStart, FVector& OutEnd) const
{
	FRotator Rotation;
	Owner->GetActorEyesViewPoint(OutStart, Rotation);
	OutEnd = OutStart + Rotation.Vector() * Distance;
}

bool ULMInteractComponent::TryCollide(TArray<FHitResult>& OutHits) const
{
	FVector Start;
	FVector End;
	CalculateVectors(Start, End);

	FCollisionShape Shape;
	Shape.SetSphere(Radius);
	
	FCollisionObjectQueryParams CollisionQueryParams;
	CollisionQueryParams.AddObjectTypesToQuery(CollisionChannel);
	const bool bIsHit = GetWorld()->SweepMultiByObjectType(OutHits, Start, End, FQuat::Identity, CollisionQueryParams, Shape);
	DebugLine(bIsHit, Start, End);
	return bIsHit;
}

void ULMInteractComponent::ManageUI(const AActor* Found) const
{
	if (!CurrentInteractable) return;
	
	const ILMUIShow* Interactable = Cast<ILMUIShow>(CurrentInteractable);
	if(!Interactable) return;
	
	if (Found == nullptr)
	{
		Interactable->Execute_DisableUI(CurrentInteractable);
		return;
	}
	Interactable->Execute_ShowUI(CurrentInteractable);
}

void ULMInteractComponent::Interact()
{
	ServerInteract(CurrentInteractable);
}

void ULMInteractComponent::DebugLine(const bool bIsHit, const FVector& Start, const FVector& End) const
{
	if (!CVarInteraction.GetValueOnAnyThread()) return;
	DrawDebugLine(GetWorld(), Start, End, bIsHit ? FColor::Green : FColor::Red, false, 1.0f, 0, 2.0);
}

void ULMInteractComponent::DebugHit(const bool bIsHit, const FHitResult& Hit) const
{
	if (!CVarInteraction.GetValueOnAnyThread()) return;
	DrawDebugSphere(GetWorld(),
		Hit.ImpactPoint,
		Radius,
		32,
		bIsHit ? FColor::Green : FColor::Red,
		false,
		1.0f);
}

void ULMInteractComponent::ServerInteract_Implementation(AActor* InteractableActor)
{
	const ILMInteractable* Interactable = Cast<ILMInteractable>(InteractableActor);
	if(!Interactable) return;
	Interactable->Execute_Interact(InteractableActor, Cast<APawn>(GetOwner()));
}
