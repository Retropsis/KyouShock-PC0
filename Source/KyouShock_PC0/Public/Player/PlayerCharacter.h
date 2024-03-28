// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class AWorldItem;
class UCharacterAnimInstance;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class KYOUSHOCK_PC0_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void TryTalking();
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TObjectPtr<AWorldItem> OverlappingItem;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> FollowCamera;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;

	TObjectPtr<UCharacterAnimInstance> CharacterAnimInstance;
	
public:
	FORCEINLINE void SetOverlappingItem(AWorldItem* Item) { OverlappingItem = Item; }
};
