// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"
#include "Student.h"
#include "Card.h"

UPerson::UPerson()
{
	Name = TEXT("김인간");
	Year = 1;
	Card = CreateDefaultSubobject<UCard>(TEXT("NAME_Card"));
}

//void UPerson::DoLesson()
//{
//	UE_LOG(LogTemp, Log, TEXT("%s님이 수업에 참여합니다."), *Name);
//}
