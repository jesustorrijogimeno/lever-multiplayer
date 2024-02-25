// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\Actors\LMWall.h"

// Sets default values
ALMWall::ALMWall()
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
void ALMWall::BeginPlay()
{
	Super::BeginPlay();
	TargetZ = StartZ;
	TimeElapsed = TimeToComplete;
}

// Called every frame
void ALMWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ManageLocation(DeltaTime);
}

void ALMWall::ManageActivation_Implementation(const bool bIsActive)
{
	InitialZ = bIsActive ? StartZ : FinalZ;
	TargetZ = bIsActive ? FinalZ : StartZ;
	if(TimeElapsed >= TimeToComplete)
	{
		TimeElapsed = 0;
	} else
	{
		TimeElapsed = TimeToComplete - TimeElapsed;
	}
	bInMovement = true;
}

void ALMWall::ManageLocation(const float DeltaTime)
{
	if (!bInMovement) return;
	if (TimeElapsed > TimeToComplete)
	{
		bInMovement = false;
		Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, TargetZ));
		return;
	}
	
	TimeElapsed += DeltaTime;
	
	const float CurrentAlpha = FMath::Clamp(TimeElapsed / TimeToComplete, 0.0f, 1.0f);
	Mesh->SetRelativeLocation(
		FMath::Lerp(
			FVector(0.0f, 0.0f, InitialZ),
			FVector(0.0f, 0.0f, TargetZ),
			CurrentAlpha));
}

