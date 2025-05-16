// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"

UMyGameInstance::UMyGameInstance()
{
	// 언리얼 오브젝트의 초기화. 
	// 이 정보는 CDO 라는 템플릿에 저장이 된다.
	SchoolName = TEXT("핵교");
}

void UMyGameInstance::Init()
{
	Super::Init();

	/*
	* Hello Unreal
	*/

	// 언리얼 로그 남기는 법
	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("Hello Unreal"));

	/*
	출력: 
		LogTemp: Hello Unreal
	*/


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

	/*
	출력:
		LogTemp: Hey Unreal
		LogTemp: Hey Unreal
		LogTemp: Find Test: Unreal
		LogTemp: Split Test: Hey / Unreal
		LogTemp: Int: 32, Float: 3.141592
		LogTemp: Int: 32, Float: 3.141592
		LogTemp: FName 비교 결과: 같음
	*/


	/*
	* 언리얼 오브젝트 리플렉션 I
	*/

	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("============================================="));

	// 클래스 정보 가져오기
	UClass* ClassRuntime = GetClass();
	UClass* ClassCompile = UMyGameInstance::StaticClass();

	// 검증 코드
	//check(ClassRuntime == ClassCompile); // assertion 이 발생하지 않으면 두 객체는 동일한 클래스를 가르킨다는 뜻.
	//ensure(ClassRuntime == ClassCompile);
	//ensureMsgf(ClassRuntime == ClassCompile, TEXT("두 객체는 같지 않다"));

	UE_LOG(LogTemp, Log, TEXT("학교를 담당하는 클래스 이름: %s"), *ClassRuntime->GetName());

	// 언리얼 오브젝트의 맴버 값
	SchoolName = TEXT("핵?교"); // 생성자에(CDO에) 저장된 값과 별개로 저장
	UE_LOG(LogTemp, Log, TEXT("학교 이름: %s"), *SchoolName);
	UE_LOG(LogTemp, Log, TEXT("학교 이름 기본값: %s"), *GetClass()->GetDefaultObject<UMyGameInstance>()->SchoolName);

	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("============================================="));

	/*
	출력:
		LogTemp: =============================================
		LogTemp: 학교를 담당하는 클래스 이름: MyGameInstance
		LogTemp: 학교 이름: 핵?교
		LogTemp: 학교 이름 기본값: 핵교
		LogTemp: =============================================
	*/

	/*
	* 언리얼 오브젝트 리플렉션 II
	*/

	// 언리얼 오브젝트 생성
	UStudent* Student = NewObject<UStudent>();
	UTeacher* Teacher = NewObject<UTeacher>();

	// 언리얼 오브젝트 초기화
	Student->SetName(TEXT("김핵생"));
	UE_LOG(LogTemp, Log, TEXT("학생의 새 이름: %s"), *Student->GetName());

	// 언리얼 리플렉션을 이용한 데이터 접근
	FString CurrentTeacherName;
	FString NewTeacherName(TEXT("박슨생"));
	FProperty* NameProp = UTeacher::StaticClass()->FindPropertyByName(TEXT("Name"));
	if (NameProp)
	{
		// 데이터 가져오기
		NameProp->GetValue_InContainer(Teacher, &CurrentTeacherName);
		UE_LOG(LogTemp, Log, TEXT("선생님의 현재 이름: %s"), *CurrentTeacherName);

		// 데이터 쓰기
		NameProp->SetValue_InContainer(Teacher, &NewTeacherName);
		UE_LOG(LogTemp, Log, TEXT("선생님의 새 이름: %s"), *Teacher->GetName());
	}

	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("============================================="));

	// 일반적인 맴버 함수 호출
	Student->DoLesson();

	//리플렉션을 이용한 맴버 함수 호출
	UFunction* DoLessonFunc = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson"));
	if (DoLessonFunc)
	{
		Teacher->ProcessEvent(DoLessonFunc, nullptr /* 함수에 전달할 매개변수*/);
	}

	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("============================================="));

	/*
	출력:
		LogTemp: 학생의 새 이름: 김핵생
		LogTemp: 선생님의 현재 이름: 김선생
		LogTemp: 선생님의 새 이름: 박슨생
		LogTemp: =============================================
		LogTemp: 김핵생님이 수업에 참여합니다.
		LogTemp: 1학년 1번 김핵생 님이 수업을 듣습니다.
		LogTemp: 박슨생님이 수업에 참여합니다.
		LogTemp: 3년차 선생님 박슨생 님이 수업을 듣습니다.
		LogTemp: =============================================
	*/
}