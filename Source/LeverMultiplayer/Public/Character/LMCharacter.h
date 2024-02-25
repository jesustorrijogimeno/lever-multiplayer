// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Components/LMInteractComponent.h"
#include "UI/Lever/LMGameInfoWidget.h"
#include "LMCharacter.generated.h"


UCLASS()
class LEVERMULTIPLAYER_API ALMCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ULMInteractComponent> InteractComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom Inputs")
	TObjectPtr<UInputMappingContext> InputMapping;
	UPROPERTY(EditDefaultsOnly, Category="Custom Inputs")
	TObjectPtr<UInputAction> InputMove;
	UPROPERTY(EditDefaultsOnly, Category="Custom Inputs")
	TObjectPtr<UInputAction> InputLookAround;
	UPROPERTY(EditDefaultsOnly, Category="Custom Inputs")
	TObjectPtr<UInputAction> InputInteract;
	
	void Move(const FInputActionInstance& InputActionInstance);
	void LookAround(const FInputActionValue& InputActionValue);
	void Interact(const FInputActionInstance& InputActionInstance);

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<ULMGameInfoWidget> PlayerNameWidget;
	UPROPERTY()
	TObjectPtr<ULMGameInfoWidget> PlayerNameWidgetInstance;
	void InitializeInputSystem() const;
	void SetUpCharacter();
public:
	// Sets default values for this character's properties
	ALMCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnRep_PlayerState() override;
};
