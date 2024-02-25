// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LMCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerStates/LMPlayerStateLever.h"
#include "UI/Lever/LMGameInfoWidget.h"

// Sets default values
ALMCharacter::ALMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetUpCharacter();
	bReplicates = true;
}

void ALMCharacter::SetUpCharacter()
{
	SpringArmComponent	= CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent	= CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	InteractComponent = CreateDefaultSubobject<ULMInteractComponent>("InteractComponent");
}

// Called when the game starts or when spawned
void ALMCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	InitializeInputSystem();
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(InputMove, ETriggerEvent::Triggered, this, &ALMCharacter::Move);
	EnhancedInputComponent->BindAction(InputLookAround, ETriggerEvent::Triggered, this, &ALMCharacter::LookAround);
	EnhancedInputComponent->BindAction(InputInteract, ETriggerEvent::Triggered, this, &ALMCharacter::Interact);
}

void ALMCharacter::InitializeInputSystem() const
{
	const ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	InputSystem->AddMappingContext(InputMapping, 0);
}

void ALMCharacter::Move(const FInputActionInstance& InputActionInstance)
{
	const FVector2D Axis = InputActionInstance.GetValue().Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), Axis.Y);
}

void ALMCharacter::LookAround(const FInputActionValue& InputActionValue)
{
	const FVector2D ActionValue = InputActionValue.Get<FVector2D>();
	AddControllerYawInput(ActionValue.X);
	AddControllerPitchInput(ActionValue.Y);
}

void ALMCharacter::Interact(const FInputActionInstance& InputActionInstance)
{
	InteractComponent->Interact();
}

void ALMCharacter::OnRep_PlayerState()
{
	const FString Name = GetPlayerState<ALMPlayerStateLever>()->GetPlayerName();
	PlayerNameWidgetInstance = CreateWidget<ULMGameInfoWidget>(GetWorld(), PlayerNameWidget);
	PlayerNameWidgetInstance->ToAttach = this;
	PlayerNameWidgetInstance->AddToViewport();
	PlayerNameWidgetInstance->ChangeText(Name);
}