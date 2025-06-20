// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ABCharacterStat.h"
#include "ABGameSingleton.generated.h"

// Get 호출 객체가 불러오지 않을 경우를 위한 로그 
DECLARE_LOG_CATEGORY_EXTERN(LogABGameSingleton, Error, All);

/**
 * -에디터에서 싱글턴 클래스로 등록하면 엔진이 초기화 할 때 바로 활성화 할 것을 보장받는다. 
 * - 캐릭터 스탯들에 대한 테이블을 내부적으로 보관하고, 필요한 게임 객체들에게 제공
 * 
 */
UCLASS()
class ARENABATTLE_API UABGameSingleton : public UObject
{
	GENERATED_BODY()

public:
	UABGameSingleton();
	static UABGameSingleton& Get();

// Character Stat Data Section
	FORCEINLINE FABCharacterStat GetCharacterStat(int32 InLevel) const { return CharacterStatTable.IsValidIndex(InLevel - 1) ? CharacterStatTable[InLevel - 1] : FABCharacterStat(); }

	UPROPERTY()
	int32 CharacterMaxLevel;

private:
	TArray<FABCharacterStat> CharacterStatTable;

};