// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

/**
 *
 */
UCLASS()
class HELLOUNREAL_API UPerson : public UObject
{
	GENERATED_BODY()

public:
	UPerson();

	//UFUNCTION()
	//virtual void DoLesson();

	FORCEINLINE const FString& GetName() const { return Name; }
	FORCEINLINE void SetName(const FString& InName) { Name = InName; }

	FORCEINLINE const class UCard* GetCard() const { return Card; }
	FORCEINLINE void SetCard(class UCard* InCard) { Card = InCard; }

	virtual void Serialize(FArchive& Ar) override;

protected:
	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Year;

	UPROPERTY()
	//class UCard* Card; // 원시 포인터 타입 전방 선언
	TObjectPtr<class UCard> Card; // 언리얼5엔 날 포인터 대신 이렇게 사용하는 것 권장

private:


};
