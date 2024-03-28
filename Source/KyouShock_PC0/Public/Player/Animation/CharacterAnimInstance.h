// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

class APlayerCharacter;
/**
 * 
 */
UCLASS()
class KYOUSHOCK_PC0_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UPROPERTY(BlueprintReadOnly, Category="Character|Movement")
	TObjectPtr<APlayerCharacter> PlayerCharacter;

	UPROPERTY(BlueprintReadOnly, Category="Character|Movement")
	float GroundSpeed = 0.f;

	UPROPERTY(BlueprintReadOnly, Category="Character|Movement")
	bool bAirborne = false;

	UPROPERTY(BlueprintReadOnly, Category="Character|Movement")
	bool bIsAccelerating = false;
	
	UPROPERTY(BlueprintReadOnly, Category="Character|Movement")
	bool bIsCrouched = false;
};
