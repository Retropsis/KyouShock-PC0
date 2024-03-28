// Fill out your copyright notice in the Description page of Project Settings.

#include "World/WorldItem.h"

#include "Components/SphereComponent.h"
#include "Player/PlayerCharacter.h"

AWorldItem::AWorldItem()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	OverlapSphere->SetupAttachment(GetRootComponent());
}

void AWorldItem::BeginPlay()
{
	Super::BeginPlay();
	
	OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &AWorldItem::OnBeginOverlap);
	OverlapSphere->OnComponentEndOverlap.AddDynamic(this, &AWorldItem::OnEndOverlap);
}

void AWorldItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWorldItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		PlayerCharacter->SetOverlappingItem(this);
	}
}

void AWorldItem::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		PlayerCharacter->SetOverlappingItem(nullptr);
	}
}

