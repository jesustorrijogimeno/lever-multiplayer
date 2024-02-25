// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LMLever.h"
#include "Actors/Interfaces/LMActivatable.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ALMLever::ALMLever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(BaseMesh);
	bReplicates = true;
}

// Called when the game starts or when spawned
void ALMLever::BeginPlay()
{
	Super::BeginPlay();
	TargetPitch = StartPitch;
	TimeElapsed = TimeToComplete;
}

// Called every frame
void ALMLever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ManageLeverRotation(DeltaTime);
}

void ALMLever::Interact_Implementation(APawn* OwnerPawn)
{
	bLeverActive = !bLeverActive;
	//For Client as server
	OnRepLeverActive();
}

void ALMLever::OnRepLeverActive()
{
	InitialPitch = bLeverActive ? StartPitch : FinalPitch;
	TargetPitch = bLeverActive ? FinalPitch : StartPitch;
	
	if(TimeElapsed >= TimeToComplete)
	{
		TimeElapsed = 0;
	} else
	{
		TimeElapsed = TimeToComplete - TimeElapsed;
	}
	bLeverInMovement = true;

	const ILMActivatable* Activatable = Cast<ILMActivatable>(TargetActor);
    if(!Activatable) return;
    Activatable->Execute_ManageActivation(TargetActor, bLeverActive);
}

void ALMLever::ManageLeverRotation(const float DeltaTime)
{
	if (!bLeverInMovement) return;
	if (TimeElapsed > TimeToComplete)
	{
		bLeverInMovement = false;
		Mesh->SetRelativeRotation(FRotator(TargetPitch, 0.0f, 0.0f));
		return;
	}
	
	TimeElapsed += DeltaTime;
	
	const float CurrentAlpha = FMath::Clamp(TimeElapsed / TimeToComplete, 0.0f, 1.0f);
	Mesh->SetRelativeRotation(
		FMath::Lerp(
			FQuat(FRotator(InitialPitch, 0.0f, 0.0f)),
			FQuat(FRotator(TargetPitch, 0.0f, 0.0f)),
			CurrentAlpha));
}

void ALMLever::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALMLever, bLeverActive);
}
