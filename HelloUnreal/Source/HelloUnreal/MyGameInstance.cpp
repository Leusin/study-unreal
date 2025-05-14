// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();

	/*
	* Hello Unreal
	*/

	// 언리얼 로그 남기는 법
	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("Hello Unreal"));

	/*
	* Unreal String
	*/

	TCHAR LogCharArray[] = TEXT("Hey Unreal");
	UE_LOG(LogTemp, Log, TEXT("%s"), LogCharArray);

	FString LogCharString = LogCharArray;
	UE_LOG(LogTemp, Log, TEXT("%s"), *LogCharString);

	// FString 을 CHAR* 로 변환 
	const TCHAR* LongCharPtr = *LogCharString;
	TCHAR* LogCharDataPtr = LogCharString.GetCharArray().GetData();

	// FString 을 CHAR 배열로 변환 
	TCHAR LogCharArrayWithSize[100];
	FCString::Strcpy(LogCharArrayWithSize, LogCharString.Len(), *LogCharString);

	// 대소 구분 없이 포함된 문자열 찾기
	if (LogCharString.Contains(TEXT("unreal"), ESearchCase::IgnoreCase))
	{
		int32 Index = LogCharString.Find(TEXT("unreal"), ESearchCase::IgnoreCase);
		FString EndString = LogCharString.Mid(Index);
		UE_LOG(LogTemp, Log, TEXT("Find Test: %s"), *EndString);
	}

	// 문자열 나누기
	FString Left, Right;
	if (LogCharString.Split(TEXT(" "), &Left, &Right))
	{
		UE_LOG(LogTemp, Log, TEXT("Split Test: %s / %s"), *Left, *Right); // Split Test: Hey / Unreal
	}

	int32 IntValue = 32;
	float FloatValue = 3.141592f;

	// 숫자 변수를 문자열로 변환
	FString FloatIntString = FString::Printf(TEXT("Int: %d, Float: %f"), IntValue, FloatValue);
	FString FloatString = FString::SanitizeFloat(FloatValue);
	FString IntString = FString::FromInt(IntValue);

	// 숫자 변수 출력
	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntString); // Int: 32, Float: 3.141592
	UE_LOG(LogTemp, Log, TEXT("Int: %d, Float: %f"), IntValue, FloatValue); // Int: 32, Float: 3.141592

	// 문자열을 숫자 변수로 변환
	int32 IntValueFromString = FCString::Atoi(*IntString);
	float FloatValueFromString = FCString::Atof(*FloatString);

	// FName는 대소문자를 구분하지 않음
	FName key1(TEXT("LEVEL"));
	FName key2(TEXT("level"));
	UE_LOG(LogTemp, Log, TEXT("FName 비교 결과: %s"), key1 == key2 ? TEXT("같음") : TEXT("다름")); // FName 비교 결과: 같음

	// 루프에서 매번 FName를 생성하면 반복적으로  name pool 접근 및 비교 연산이 일어나 오버헤드 발생
	for (int i = 0; i < 10000; i++)
	{
		FName SearchInNamePool = FName(TEXT("level")); // 이 경우보다
		const static FName StaticOnlyOnce(TEXT("level")); // 이와 같이 처리하는 게 나음
	}
}