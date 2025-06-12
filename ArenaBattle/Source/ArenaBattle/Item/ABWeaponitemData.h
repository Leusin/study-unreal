// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ABItemData.h"
#include "ABWeaponitemData.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABWeaponitemData : public UABItemData
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(EditAnywhere, Category = Weapon)
	TSoftObjectPtr<UStaticMesh> WeaponMesh;
};
