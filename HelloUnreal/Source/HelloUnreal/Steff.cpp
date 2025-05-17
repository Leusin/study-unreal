// Fill out your copyright notice in the Description page of Project Settings.


#include "Steff.h"
#include "Card.h"

USteff::USteff()
{
	Name = TEXT("김직원");
	Card->SetCardType(ECardType::Staff);
}