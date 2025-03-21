/**
 * @file 		GronkUtils.h
 * @brief 		The main module for the GronkUtils plugin.
 * @copyright 	Grant Wilk, all rights reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FGronkUtilsModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};