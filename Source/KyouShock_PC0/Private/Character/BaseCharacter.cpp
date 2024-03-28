// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/BaseCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	DialogueTriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DialogueTriggerSphere"));
	DialogueTriggerSphere->SetupAttachment(GetRootComponent());
	DialogueTriggerSphere->SetSphereRadius(150.f);
	DialogueTriggerSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DialogueTriggerSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	DialogueTriggerSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	NPCController = Cast<AAIController>(GetController());
	MoveToNavPoint(CurrentNavigationPoint);
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(WithinRange(CurrentNavigationPoint, NavigationRadius))
	{
		CurrentNavigationPoint = SelectNextNavigationPoint();
		const float WaitTime = FMath::FRandRange(NavigationWaitMin, NavigationWaitMax);
		GetWorldTimerManager().SetTimer(NavigationTimer, this, &ABaseCharacter::NavigationTimerFinished, WaitTime);
	}
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool ABaseCharacter::WithinRange(const AActor* ToPoint, const double Radius)
{
	if(ToPoint == nullptr) return false;
		
	const double DistanceToPoint = (ToPoint->GetActorLocation() - GetActorLocation()).Size();
	DrawDebugSphere(GetWorld(), GetActorLocation(), 25.f, 12, FColor::White);
	DrawDebugSphere(GetWorld(), ToPoint->GetActorLocation(), 25.f, 12, FColor::Green);
	return DistanceToPoint <= Radius;
}

void ABaseCharacter::MoveToNavPoint(const AActor* NavPoint)
{
	if(NPCController == nullptr || NavPoint == nullptr) return;
	
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(NavPoint);
	MoveRequest.SetAcceptanceRadius(15.f);
	NPCController->MoveTo(MoveRequest);

	// Debug Version:
	// FNavPathSharedPtr NavigationPath;
	// NPCController->MoveTo(MoveRequest, &NavigationPath);
	// TArray<FNavPathPoint>& PathPoints = NavigationPath->GetPathPoints();
	// for (FNavPathPoint& Point : PathPoints)
	// {
	// 	const FVector& Location = Point.Location;
	// 	DrawDebugSphere(GetWorld(), Location, 12.f, 12, FColor::Green, false, 10.f);
	// }
}

AActor* ABaseCharacter::SelectNextNavigationPoint()
{
	TArray<AActor*> ValidPoints;
	for (TObjectPtr<AActor> NavPoint : NavigationPoints)
	{
		if(NavPoint != CurrentNavigationPoint)
		{
			ValidPoints.AddUnique(NavPoint);
		}
	}
			
	const int32 NumPoints = ValidPoints.Num();
	if(NumPoints > 0)
	{
		const int32 Selection = FMath::RandRange(0, NumPoints-1);
		return ValidPoints[Selection];
	}
	
	return nullptr;
}

void ABaseCharacter::NavigationTimerFinished()
{
	MoveToNavPoint(CurrentNavigationPoint);
}

void ABaseCharacter::Talk_Implementation()
{
}