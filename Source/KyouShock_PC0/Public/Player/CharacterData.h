#pragma once

#include "CoreMinimal.h"
#include "CharacterData.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Unoccupied UMETA(DisplayName="Unoccupied"),
	ECS_Talking UMETA(DisplayName="Talking")
};
