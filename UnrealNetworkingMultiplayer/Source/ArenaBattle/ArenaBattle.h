// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define LOG_NETMODEINFO ((GetNetMode() == ENetMode::NM_Client) ? TEXT("Client") : ((GetNetMode() == ENetMode::NM_Standalone) ? TEXT("StandAlone") : TEXT("Server")))
#define LOG_CALLINFO ANSI_TO_TCHAR(__FUNCTION__) // 매크로가 호출되고 있는 함수 이름 가져옴
// UE_LOG 매크로를 대신함
#define AB_LOG(LogCat, Verbosity, Format, ...) UE_LOG(LogCat, Verbosity, TEXT("[%s] %s %s"), LOG_NETMODEINFO, LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))


DECLARE_LOG_CATEGORY_EXTERN(LogABNetwork, Log, All);