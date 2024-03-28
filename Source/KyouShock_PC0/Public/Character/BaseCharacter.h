// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interaction/DialogueInterface.h"
#include "Interaction/InteractionInterface.h"
#include "BaseCharacter.generated.h"

class USphereComponent;
class AAIController;

UCLASS()
class KYOUSHOCK_PC0_API ABaseCharacter : public ACharacter, public IDialogueInterface, public IInteractionInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*
	 * Dialogue
	 */
	//~ Dialogue Interface
	virtual void Talk_Implementation() override;
	//~ Dialogue Interface

	UPROPERTY(VisibleAnywhere, Category="NPC|Dialogue")
	TObjectPtr<USphereComponent> DialogueTriggerSphere;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="NPC|Dialogue")
	TArray<FText> DialogueChain;

	UPROPERTY(BlueprintReadWrite, Category="NPC|Dialogue")
	int32 DialogueIndex;
	
	/*
	 * Navigation
	 */
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AAIController> NPCController;
	
	UPROPERTY(EditInstanceOnly, Category="NPC|Navigation")
	TObjectPtr<AActor> CurrentNavigationPoint;

	UPROPERTY(EditInstanceOnly, Category="NPC|Navigation")
	TArray<TObjectPtr<AActor>> NavigationPoints;

	UPROPERTY(EditAnywhere, Category="NPC|Navigation")
	double NavigationRadius = 180.f;
	
	UPROPERTY(EditAnywhere, Category="NPC|Navigation")
	float NavigationWaitMin = 1.5f;
	float NavigationWaitMax = 5.f;

	FTimerHandle NavigationTimer;
	void NavigationTimerFinished();
	
protected:
	virtual void BeginPlay() override;

	bool WithinRange(const AActor* ToPoint, double Radius);
	void MoveToNavPoint(const AActor* NavPoint);
	AActor* SelectNextNavigationPoint();

public:
	
};
