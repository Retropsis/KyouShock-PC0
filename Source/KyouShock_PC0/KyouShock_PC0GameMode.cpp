// Copyright Epic Games, Inc. All Rights Reserved.

#include "KyouShock_PC0GameMode.h"
#include "KyouShock_PC0Character.h"
#include "UObject/ConstructorHelpers.h"

AKyouShock_PC0GameMode::AKyouShock_PC0GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
