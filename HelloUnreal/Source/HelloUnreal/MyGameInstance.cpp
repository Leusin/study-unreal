// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"
#include "Steff.h"
#include "Card.h"
#include "CourseInfo.h"


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


	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("============================================="));


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

	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("============================================="));

	/*
	* 언리얼 오브젝트 리플렉션 I
	*/

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


	/*
	출력:
		LogTemp: 학교를 담당하는 클래스 이름: MyGameInstance
		LogTemp: 학교 이름: 핵?교
		LogTemp: 학교 이름 기본값: 핵교
	*/


	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("============================================="));


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

	// 리플렉션을 이용한 맴버 함수 호출
	// (현재는 UFUNCTION()로 관리되는 함수라서 호출되지 않는다)
	UFunction* DoLessonFunc = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson"));
	if (DoLessonFunc)
	{
		Teacher->ProcessEvent(DoLessonFunc, nullptr /* 함수에 전달할 매개변수*/);
	}

	/*
	출력:
		LogTemp: 학생의 새 이름: 김핵생
		LogTemp: 선생님의 현재 이름: 김선생
		LogTemp: 선생님의 새 이름: 박슨생
		LogTemp: =============================================
		LogTemp: 1학년 1번 김핵생 님이 수업을 듣습니다.
	*/


	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("============================================="));


	/**
	* 인터페이스
	*/

	TArray<UPerson*> Persons = { NewObject<UStudent>(), NewObject<UTeacher>(), NewObject<USteff>() };

	// 다형적 동작
	for (const UPerson* Person : Persons)
	{
		UE_LOG(LogTemp, Log, TEXT("구성원 이름: %s"), *Person->GetName());
	}

	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("============================================="));

	// 인터페이스를 통해 구현한 매서드
	// 캐스팅을 통해 다형적 동작
	for (UPerson* Person : Persons)
	{
		IDoLesson* LessonInterface = Cast<IDoLesson>(Person);
		if (LessonInterface)
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여할 수 있습니다."), *Person->GetName());
			LessonInterface->DoLesson();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여할 수 없습니다."), *Person->GetName());
		}
	}

	/*
	출력:
		LogTemp: 구성원 이름: 김학생
		LogTemp: 구성원 이름: 김선생
		LogTemp: 구성원 이름: 김직원
		LogTemp: =============================================
		LogTemp: 김학생님은 수업에 참여할 수 있습니다.
		LogTemp: 1학년 1번 김학생 님이 수업을 듣습니다.
		LogTemp: 김선생님은 수업에 참여할 수 있습니다.
		LogTemp: 3년차 선생님 김선생 님이 수업을 진행합니다.
		LogTemp: 김직원님은 수업에 참여할 수 없습니다.
	*/


	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("============================================="));


	/**
	* 언리얼 컴포지션
	*/
	for (UPerson* Person : Persons)
	{
		// UPerson 객체가 가진 UCard 객체 정보 가져오기
		const UCard* OwnCard = Person->GetCard();
		check(OwnCard);
		ECardType CardType = OwnCard->GetCardType();

		// 열거형 ECardType 에 지정된 메타 정보 가져오기
		const UEnum* CardEnumType = FindObject<UEnum>(nullptr, TEXT("/Script/HelloUnreal.ECardType"));
		if (CardEnumType)
		{
			FString CardMetaData = CardEnumType->GetDisplayNameTextByValue((int64)CardType).ToString();
			UE_LOG(LogTemp, Log, TEXT("%s 님이 소유한 카드의 종류: %d (%s)"), *Person->GetName(), CardType, *CardMetaData);
		}

	}

	/*
	출력:
		LogTemp: 김학생 님이 소유한 카드의 종류: 1 (For Student)
		LogTemp: 김선생 님이 소유한 카드의 종류: 2 (For Teacher)
		LogTemp: 김직원 님이 소유한 카드의 종류: 3 (For Staff)
	*/
	

	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("============================================="));


	/**
	* 언리얼 델리게이트
	*/	
	CourseInfo = NewObject<UCourseInfo>(this); // 컴포지션 객체를 NewObject 로 생성할때 매개변수에 Outher(MyGameInstance) 를 지정해야함

	UStudent* Student1 = NewObject<UStudent>();
	Student1->SetName(TEXT("일학생"));
	UStudent* Student2 = NewObject<UStudent>();
	Student2->SetName(TEXT("이학생"));
	UStudent* Student3 = NewObject<UStudent>();
	Student3->SetName(TEXT("삼학생"));

	CourseInfo->OnChanged.AddUObject(Student1, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student2, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student3, &UStudent::GetNotification);

	CourseInfo->ChangeCourseInfo(SchoolName, TEXT("변경된 학사 정보"));

	/*
	출력:
		LogTemp: [CourseInfo] 학사 정보가 변경되어 알림을 발송합니다.
		LogTemp: [Student] 삼학생 님이 핵?교 로부터 받은 메시지 : 변경된 학사 정보
		LogTemp: [Student] 이학생 님이 핵?교 로부터 받은 메시지 : 변경된 학사 정보
		LogTemp: [Student] 일학생 님이 핵?교 로부터 받은 메시지 : 변경된 학사 정보
	*/


	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("============================================="));


	/**
	* 언리얼 컨테이너 TArray
	*/

	const int32 ArrayNum = 10;
	TArray<int32> I32Array;

	// 빈 컨테이너에 원소 추가(1, 2, 3 ... 8, 9, 10)
	for (int32 i = 1; i <= ArrayNum; i++)
	{
		I32Array.Add(i);
	}

	// 원소 지우기 (1, 3, 5, 7, 9)
	I32Array.RemoveAll(
		[](int32 Val)
		{
			return Val % 2 == 0;
		}
	);

	// 원소 추가하기 (1, 3, 5, 7, 9, 2, 4, 6, 8, 10)
	I32Array += { 2, 4, 6, 8, 10 };

	// 메모리 주소를 참고하여 값 넣기
	TArray<int32> I32ArrayCompare;
	int32 CArray[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};

	I32ArrayCompare.AddUninitialized(ArrayNum);
	FMemory::Memcpy(I32ArrayCompare.GetData(), CArray, sizeof(int32) * ArrayNum);

	ensure(I32Array == I32ArrayCompare);

	// 누적곱 구하기
	int32 Sum = 0;
	for (const int32& Elem : I32Array)
	{
		Sum += Elem;
	}

	int32 SumByAlgo = Algo::Accumulate(I32Array, 0);
	ensure(Sum == SumByAlgo);

	/**
	* 언리얼 컨테이너 TSet
	*/

	TSet<int32> I32Set;

	// 빈 컨테이너에 원소 추가(1, 2, 3 ... 8, 9, 10)
	for (int32 i = 1; i < ArrayNum; i++)
	{
		I32Set.Add(i);
	}

	// 원소 지우기 (순서 상관 없이 1, 3, 5, 7, 9)
	I32Set.Remove(2);
	I32Set.Remove(4);
	I32Set.Remove(6);
	I32Set.Remove(8);
	I32Set.Remove(10);

	// 원소 추가하기 (순서 상관 없이 1, 3, 5, 7, 9, 2, 4, 6, 8, 10)
	I32Set.Add(2);
	I32Set.Add(4);
	I32Set.Add(6);
	I32Set.Add(8);
	I32Set.Add(10);


	/**
	* 언리얼 구조체
	*/
	const int32 StudentNum = 300;
	for (int32 i = 0; i < StudentNum; i++)
	{
		StudentsData.Emplace(FStudentData(MakeRandomName(), i));
	}

	TArray<FString> AllStudentsName;
	Algo::Transform(StudentsData, AllStudentsName,
		[](const FStudentData& Val)
		{
			return Val.Name;
		}
	);

	UE_LOG(LogTemp, Log, TEXT("모든 학생 이름의 수 : %d"), AllStudentsName.Num());

	TSet<FString> AllUniqueNames;
	Algo::Transform(StudentsData, AllUniqueNames,
		[](const FStudentData& Val)
		{
			return Val.Name;
		}
	);

	UE_LOG(LogTemp, Log, TEXT("중복 없는 학생 이름의 수 : %d"), AllUniqueNames.Num());

	/*
	출력:
		LogTemp: 모든 학생 이름의 수 : 300
		LogTemp: 중복 없는 학생 이름의 수 : 64
	*/


	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("============================================="));


	/**
	* 언리얼 컨테이너 TMap
	*/

	Algo::Transform(StudentsData, StudentsMap,
		[](const FStudentData& Val)
		{
			return TPair<int32, FString>(Val.Order, Val.Name);
		}
	);

	UE_LOG(LogTemp, Log, TEXT("순번에 따른 학생 맵의 레코드 수 : %d"), StudentsMap.Num());

	TMap<FString, int32> StudentsMapByUniqueName;

	Algo::Transform(StudentsData, StudentsMapByUniqueName,
		[](const FStudentData& Val)
		{
			return TPair<FString, int32>(Val.Name, Val.Order);
		}
	);

	UE_LOG(LogTemp, Log, TEXT("이름에 따른 학생 맵의 레코드 수 : %d"), StudentsMapByUniqueName.Num());

	TMultiMap<FString, int32> StudentsMultiMapByUniqueName;

	Algo::Transform(StudentsData, StudentsMultiMapByUniqueName,
		[](const FStudentData& Val)
		{
			return TPair<FString, int32>(Val.Name, Val.Order);
		}
	);

	UE_LOG(LogTemp, Log, TEXT("이름에 따른 학생 멀티맵의 레코드 수 : %d"), StudentsMultiMapByUniqueName.Num());

	const FString TargetName(TEXT("이혜은"));
	TArray<int32> AllOrders;
	StudentsMultiMapByUniqueName.MultiFind(TargetName, AllOrders);

	UE_LOG(LogTemp, Log, TEXT("이름이 \"%s\"인 학생 수 : % d"), *TargetName, AllOrders.Num());

	TSet<FStudentData> StudentSet;
	for (int32 i = 0; i <= StudentNum; i++)
	{
		StudentSet.Emplace(FStudentData(MakeRandomName(), i));
	}
}