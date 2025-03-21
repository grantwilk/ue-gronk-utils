/**
 * @file		LoggerLibrary.h
 * @brief		A blueprint function library for logging messages.
 * @copyright	Grant Wilk, all rights reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LoggerLibrary.generated.h"

/**
 * @enum ELoggerLevel
 * @brief Custom logging levels for Blueprint usage.
 */
UENUM(BlueprintType)
enum class ELoggerLevel : uint8
{
	VeryVerbose UMETA(DisplayName = "VeryVerbose"),
	Verbose		UMETA(DisplayName = "Verbose"),
	Log			UMETA(DisplayName = "Log"),
	Display		UMETA(DisplayName = "Display"),
	Warning		UMETA(DisplayName = "Warning"),
	Error		UMETA(DisplayName = "Error"),
	Fatal		UMETA(DisplayName = "Fatal")
};

/**
 * @enum ELogValidityCondition
 * @brief Determines the condition under which logging occurs during validity checks.
 */
UENUM(BlueprintType)
enum class ELogValidityCondition : uint8
{
	LogWhenValid   UMETA(DisplayName = "Log When Valid"),
	LogWhenInvalid UMETA(DisplayName = "Log When Invalid")
};

/**
 * @enum ELogBooleanCondition
 * @brief Determines the condition under which logging occurs during boolean checks.
 */
UENUM(BlueprintType)
enum class ELogBooleanCondition : uint8
{
	LogWhenTrue	 UMETA(DisplayName = "Log When True"),
	LogWhenFalse UMETA(DisplayName = "Log When False")
};

/**
 * @enum EValidityOutcome
 * @brief Determines which exec pin is triggered in the "Log On Validity" function.
 */
UENUM(BlueprintType)
enum class EValidityOutcome : uint8
{
	IsValid	   UMETA(DisplayName = "Is Valid"),
	IsNotValid UMETA(DisplayName = "Is Not Valid")
};

/**
 * @enum EConditionOutcome
 * @brief Determines which exec pin is triggered in the "Log On Condition" function.
 */
UENUM(BlueprintType)
enum class EConditionOutcome : uint8
{
	IsTrue	UMETA(DisplayName = "True"),
	IsFalse UMETA(DisplayName = "False")
};

/**
 * @class ULoggerLibrary
 * @brief A blueprint‑accessible function library for logging.
 */
UCLASS()
class GRONKUTILS_API ULoggerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * @brief Sets the global log level threshold for on‑screen display.
	 *
	 * @param NewDisplayLevel The new minimum log level required for on‑screen display.
	 */
	UFUNCTION(BlueprintCallable, Category = "GronkUtils|Logging")
	static void SetDisplayLogLevel(ELoggerLevel NewDisplayLevel);

	/**
	 * @brief Logs a message to the output log.
	 *
	 * @param Caller	The calling object.
	 * @param Message	The message to log.
	 * @param Level		Log level of the message.
	 */
	UFUNCTION(BlueprintCallable, Category = "GronkUtils|Logging", meta = (DisplayName = "Log Message", DefaultToSelf = "Caller"))
	static void LogMessage(UObject* Caller, const FString& Message, ELoggerLevel Level = ELoggerLevel::Display);

	/**
	 * @brief Logs a message with a boolean value appended to it.
	 *
	 * @param Caller	The calling object.
	 * @param Message	The message to log.
	 * @param Value		The boolean value to append.
	 * @param Level		Log level of the message.
	 */
	UFUNCTION(BlueprintCallable, Category = "GronkUtils|Logging", meta = (DisplayName = "Log Message with Bool", DefaultToSelf = "Caller"))
	static void LogBool(UObject* Caller, const FString& Message, bool Value, ELoggerLevel Level = ELoggerLevel::Display);

	/**
	 * @brief Logs a message with an integer value appended to it.
	 *
	 * @param Caller	The calling object.
	 * @param Message	The message to log.
	 * @param Value		The integer value to append.
	 * @param Level		Log level of the message.
	 */
	UFUNCTION(BlueprintCallable, Category = "GronkUtils|Logging", meta = (DisplayName = "Log Message with Int", DefaultToSelf = "Caller"))
	static void LogInt(UObject* Caller, const FString& Message, int32 Value, ELoggerLevel Level = ELoggerLevel::Display);

	/**
	 * @brief Logs a message with a float value appended to it.
	 *
	 * @param Caller	The calling object.
	 * @param Message	The message to log.
	 * @param Value		The float value to append.
	 * @param Level		Log level of the message.
	 */
	UFUNCTION(BlueprintCallable, Category = "GronkUtils|Logging", meta = (DisplayName = "Log Message with Float", DefaultToSelf = "Caller"))
	static void LogFloat(UObject* Caller, const FString& Message, double Value, ELoggerLevel Level = ELoggerLevel::Display);

	/**
	 * @brief Logs a message with a vector value appended to it.
	 *
	 * @param Caller	The calling object.
	 * @param Message	The message to log.
	 * @param Value		The vector value to append.
	 * @param Level		Log level of the message.
	 */
	UFUNCTION(BlueprintCallable, Category = "GronkUtils|Logging", meta = (DisplayName = "Log Message with Vector", DefaultToSelf = "Caller"))
	static void LogVector(UObject* Caller, const FString& Message, const FVector& Value, ELoggerLevel Level = ELoggerLevel::Display);

	/**
	 * @brief Logs a message with a rotator value appended to it.
	 *
	 * @param Caller	The calling object.
	 * @param Message	The message to log.
	 * @param Value		The rotator value to append.
	 * @param Level		Log level of the message.
	 */
	UFUNCTION(BlueprintCallable, Category = "GronkUtils|Logging", meta = (DisplayName = "Log Message with Rotator", DefaultToSelf = "Caller"))
	static void LogRotator(UObject* Caller, const FString& Message, const FRotator& Value, ELoggerLevel Level = ELoggerLevel::Display);

	/**
	 * @brief Logs a message with an object value appended to it.
	 *
	 * @param Caller	The calling object.
	 * @param Message	The message to log.
	 * @param Value		The object value to append.
	 * @param Level		Log level of the message.
	 */
	UFUNCTION(BlueprintCallable, Category = "GronkUtils|Logging", meta = (DisplayName = "Log Message with Object", DefaultToSelf = "Caller"))
	static void LogObject(UObject* Caller, const FString& Message, UObject* Value, ELoggerLevel Level = ELoggerLevel::Display);

	/**
	 * @brief Checks an object for validity and logs a message based on the specified validity condition.
	 *
	 * @param Caller		The calling object.
	 * @param InObject		The object to validate.
	 * @param OutExecs		Outputs either "Is Valid" or "Is Not Valid".
	 * @param LogCondition	Determines whether to log when the object is valid or invalid.
	 * @param Message		The message to log if the condition is met.
	 * @param Level			The log level to use when logging.
	 */
	UFUNCTION(BlueprintCallable, Category = "GronkUtils|Logging", meta = (DisplayName = "Log On Validity", ExpandEnumAsExecs = "OutExecs", DefaultToSelf = "Caller"))
	static void LogOnValidity(UObject* Caller, UObject* InObject, EValidityOutcome& OutExecs, ELogValidityCondition LogCondition, const FString& Message, ELoggerLevel Level = ELoggerLevel::Display);

	/**
	 * @brief Checks a boolean condition and logs a message based on the condition's value.
	 *
	 * @param Caller 		The calling object.
	 * @param Condition 	The condition to check.
	 * @param OutExecs 		Outputs either "True" or "False".
	 * @param LogCondition	Determines whether to log when the condition is true or false.
	 * @param Message 		The message to log if the condition is met.
	 * @param Level 		The log level to use when logging.
	 */
	UFUNCTION(BlueprintCallable, Category = "GronkUtils|Logging", meta = (DisplayName = "Log On Condition", ExpandEnumAsExecs = "OutExecs", DefaultToSelf = "Caller"))
	static void LogOnCondition(UObject* Caller, bool Condition, EConditionOutcome& OutExecs, ELogBooleanCondition LogCondition, const FString& Message, ELoggerLevel Level = ELoggerLevel::Display);

private:
	/**
	 * @brief The global minimum log level required for on‑screen display.
	 *
	 * This static member is shared across all calls to the logging functions.
	 */
	inline static ELoggerLevel DisplayLogLevel = ELoggerLevel::Display;

	/**
	 * @brief Gets an on‑screen text color for the given log level.
	 *
	 * @param Level The logging level.
	 * @return The FColor to use for on‑screen text.
	 */
	static FColor GetColorForLevel(ELoggerLevel Level);
};
