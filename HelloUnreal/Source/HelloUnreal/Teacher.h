// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.h"
#include "DoLesson.h"
#include "Teacher.generated.h"

/**
 *
 */
UCLASS()
class HELLOUNREAL_API UTeacher : public UPerson, public IDoLesson
{
	GENERATED_BODY()

public:
	UTeacher();

	virtual void DoLesson() override;

protected:


private:
	UPROPERTY()
	int32 Id;

};
