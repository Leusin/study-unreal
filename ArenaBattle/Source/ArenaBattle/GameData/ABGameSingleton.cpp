// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameSingleton.h"

DEFINE_LOG_CATEGORY(LogABGameSingleton);

UABGameSingleton::UABGameSingleton()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Script/Engine.DataTable'/Game/ArenaBattle/GameData/ABCharacterStat.ABCharacterStat'"));
	if (nullptr != DataTableRef.Object)
	{
		const UDataTable* DataTable = DataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, CharacterStatTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FABCharacterStat*>(Value);
			}
		);
	}

	CharacterMaxLevel = CharacterStatTable.Num();
	ensure(CharacterMaxLevel > 0); // 하나라도 불러와지지 않을 경우 컴파일 에러 발생
}

UABGameSingleton& UABGameSingleton::Get()
{
	// CastChecked - 타입 변환이 잘 되었는지 강력하게 검사 
	UABGameSingleton* Singleton = CastChecked< UABGameSingleton>(GEngine->GameSingleton);
	if (Singleton)
	{
		return *Singleton;
	}

	UE_LOG(LogABGameSingleton, Error, TEXT("유효하지 않은 싱글턴 객체 Invalid Game Singleton"));
	return *NewObject<UABGameSingleton>();
}