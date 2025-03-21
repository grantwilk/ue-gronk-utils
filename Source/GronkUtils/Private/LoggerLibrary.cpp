/**
 * @file		LoggerLibrary.cpp
 * @brief		A blueprint function library for logging messages.
 * @copyright	Grant Wilk, all rights reserved.
 */

#include "LoggerLibrary.h"
#include "Engine/Engine.h"
#include "Logging/LogMacros.h"

// Define a static log category for the logger library.
DEFINE_LOG_CATEGORY_STATIC(LogLoggerLibrary, Log, All);

// A static map to associate log levels with on‑screen colors.
static const TMap<ELoggerLevel, FColor> LevelColorMap = {
	{ ELoggerLevel::VeryVerbose, FColor::Purple },
	{ ELoggerLevel::Verbose, FColor::Blue },
	{ ELoggerLevel::Log, FColor::White },
	{ ELoggerLevel::Display, FColor::Cyan },
	{ ELoggerLevel::Warning, FColor::Yellow },
	{ ELoggerLevel::Error, FColor::Red },
	{ ELoggerLevel::Fatal, FColor::Magenta }
};

void ULoggerLibrary::SetDisplayLogLevel(ELoggerLevel NewDisplayLevel)
{
	DisplayLogLevel = NewDisplayLevel;
}

void ULoggerLibrary::LogMessage(UObject* Caller, const FString& Message, ELoggerLevel Level)
{
	// Determine the context name based on whether the caller is a component
	FString ContextName;
	if (UActorComponent* Component = Cast<UActorComponent>(Caller))
	{
		if (AActor* Owner = Component->GetOwner())
		{
			ContextName = FString::Printf(TEXT("%s.%s"), *Owner->GetName(), *Component->GetName());
		}
		else
		{
			ContextName = Component->GetName();
		}
	}
	else
	{
		ContextName = Caller ? Caller->GetName() : TEXT("UnknownContext");
	}

	const FString LogString = FString::Printf(TEXT("[%s]\t%s: %s"), *UEnum::GetValueAsString(Level), *ContextName, *Message);

	switch (Level)
	{
		case ELoggerLevel::VeryVerbose:
			UE_LOG(LogLoggerLibrary, VeryVerbose, TEXT("%s"), *LogString);
			break;
		case ELoggerLevel::Verbose:
			UE_LOG(LogLoggerLibrary, Verbose, TEXT("%s"), *LogString);
			break;
		case ELoggerLevel::Log:
			UE_LOG(LogLoggerLibrary, Log, TEXT("%s"), *LogString);
			break;
		case ELoggerLevel::Display:
			UE_LOG(LogLoggerLibrary, Display, TEXT("%s"), *LogString);
			break;
		case ELoggerLevel::Warning:
			UE_LOG(LogLoggerLibrary, Warning, TEXT("%s"), *LogString);
			break;
		case ELoggerLevel::Error:
			UE_LOG(LogLoggerLibrary, Error, TEXT("%s"), *LogString);
			break;
		case ELoggerLevel::Fatal:
			UE_LOG(LogLoggerLibrary, Fatal, TEXT("%s"), *LogString);
			break;
		default:
			UE_LOG(LogLoggerLibrary, Log, TEXT("%s"), *LogString);
			break;
	}

	if (static_cast<uint8>(Level) >= static_cast<uint8>(DisplayLogLevel))
	{
		if (GEngine)
		{
			FColor TextColor = GetColorForLevel(Level);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, TextColor, LogString);
		}
	}
}

void ULoggerLibrary::LogBool(UObject* Caller, const FString& Message, bool Value, ELoggerLevel Level)
{
	FString FinalMessage = Message + TEXT(": ") + (Value ? TEXT("true") : TEXT("false"));
	LogMessage(Caller, FinalMessage, Level);
}

void ULoggerLibrary::LogInt(UObject* Caller, const FString& Message, int32 Value, ELoggerLevel Level)
{
	FString FinalMessage = Message + TEXT(": ") + FString::FromInt(Value);
	LogMessage(Caller, FinalMessage, Level);
}

void ULoggerLibrary::LogFloat(UObject* Caller, const FString& Message, double Value, ELoggerLevel Level)
{
	FString FinalMessage = Message + TEXT(": ") + FString::SanitizeFloat(Value);
	LogMessage(Caller, FinalMessage, Level);
}

void ULoggerLibrary::LogObject(UObject* Caller, const FString& Message, UObject* Value, ELoggerLevel Level)
{
	FString ObjectName = (Value != nullptr ? Value->GetName() : TEXT("NULL"));
	FString FinalMessage = Message + TEXT(": ") + ObjectName;
	LogMessage(Caller, FinalMessage, Level);
}

void ULoggerLibrary::LogOnValidity(UObject* Caller, UObject* InObject, EValidityOutcome& OutExecs, ELogValidityCondition Condition, const FString& Message, ELoggerLevel Level)
{
	bool bShouldLog = false;

	if (Condition == ELogValidityCondition::LogWhenInvalid)
	{
		bShouldLog = !IsValid(InObject);
	}
	else if (Condition == ELogValidityCondition::LogWhenValid)
	{
		bShouldLog = IsValid(InObject);
	}

	if (bShouldLog)
	{
		LogMessage(Caller, Message, Level);
	}

	OutExecs = IsValid(InObject) ? EValidityOutcome::IsValid : EValidityOutcome::IsNotValid;
}

void ULoggerLibrary::LogOnCondition(UObject* Caller, bool Condition, EConditionOutcome& OutExecs, ELogBooleanCondition LogCondition, const FString& Message, ELoggerLevel Level)
{
	if ((LogCondition == ELogBooleanCondition::LogWhenTrue && Condition) || (LogCondition == ELogBooleanCondition::LogWhenFalse && !Condition))
	{
		LogMessage(Caller, Message, Level);
	}

	OutExecs = Condition ? EConditionOutcome::IsTrue : EConditionOutcome::IsFalse;
}

FColor ULoggerLibrary::GetColorForLevel(ELoggerLevel Level)
{
	if (const FColor* FoundColor = LevelColorMap.Find(Level))
	{
		return *FoundColor;
	}
	return FColor::White;
}
