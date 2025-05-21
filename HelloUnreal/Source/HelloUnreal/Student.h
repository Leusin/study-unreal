// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.h"
#include "DoLesson.h"
#include "Student.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUNREAL_API UStudent : public UPerson, public IDoLesson
{
	GENERATED_BODY()

public:
	UStudent();

	virtual void DoLesson() override;

	void GetNotification(const FString& School, const FString& NewCourseInfo);

	virtual void Serialize(FArchive& Ar) override;

	FORCEINLINE void SetOrder(const int32& InOrder)
	{
		Order = InOrder;
	}

	FORCEINLINE const int32& GetOrder() const
	{
		return Order;
	}

protected:


private:
	UPROPERTY()
	int32 Id;

	UPROPERTY()
	int32 Order;

};
