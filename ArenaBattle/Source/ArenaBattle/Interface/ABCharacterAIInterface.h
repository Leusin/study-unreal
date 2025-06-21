// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ABCharacterAIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UABCharacterAIInterface : public UInterface
{
	GENERATED_BODY()
};

DECLARE_DELEGATE(FAICharacterAttackFinished);
/**
 *
 */
class ARENABATTLE_API IABCharacterAIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float GetAIPatrolRadius() abstract;
	virtual float GetAIDetectRange() abstract;
	virtual float GetAIAttackRange() abstract;
	virtual float GetAITurnSpeed() abstract;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) abstract;
	virtual void AttackByAI() abstract;
};