// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PlayerCharacterController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Player/PlayerCharacter.h"

void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Move);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Jump);
	EnhancedInputComponent->BindAction(MainAction, ETriggerEvent::Started, this, &APlayerCharacterController::MainActionButtonPressed);
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();
	
	checkf(CharacterContext, TEXT("Missing CharacterMappingContext, check CharacterPlayerController"));
	if(UEnhancedInputLocalPlayerSubsystem*  Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(CharacterContext, 0);
	}
	PlayerCharacter = Cast<APlayerCharacter>(GetCharacter());
}

void APlayerCharacterController::Move(const FInputActionValue& InputActionValue)
{
	// TODO: Make Additive Attacks instead of pinning
	if(PlayerCharacter->GetCharacterState() != ECharacterState::ECS_Unoccupied) return;
	
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void APlayerCharacterController::Jump()
{
	if (PlayerCharacter) PlayerCharacter->Jump();
}

void APlayerCharacterController::MainActionButtonPressed()
{
	// if (PlayerCharacter) PlayerCharacter->Equip();
	if (PlayerCharacter) PlayerCharacter->TryTalking();
}
