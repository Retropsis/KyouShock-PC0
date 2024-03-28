// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class KYOUSHOCK_PC0_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Chatacter|Input")
	TObjectPtr<UInputMappingContext> CharacterContext;

	UPROPERTY(EditDefaultsOnly, Category="Chatacter|Input")
	TObjectPtr<UInputAction> MoveAction;

	// UPROPERTY(EditDefaultsOnly, Category="Chatacter|Input")
	// TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category="Chatacter|Input")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Chatacter|Input")
	TObjectPtr<UInputAction> MainAction;
	
	// UPROPERTY(EditDefaultsOnly, Category="Chatacter|Input")
	// TObjectPtr<UInputAction> AttackAction;
	//
	// UPROPERTY(EditDefaultsOnly, Category="Chatacter|Input")
	// TObjectPtr<UInputAction> RollAction;
	//
	// UPROPERTY(EditDefaultsOnly, Category="Chatacter|Input")
	// TObjectPtr<UInputAction> LockAction;

protected:
	virtual void BeginPlay() override;

private:
	TObjectPtr<APlayerCharacter> PlayerCharacter;
	
	void Move(const FInputActionValue& InputActionValue);
	void Jump();
	void MainActionButtonPressed();
};
