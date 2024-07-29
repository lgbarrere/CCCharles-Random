// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Runtime/Core/Public/Misc/FileHelper.h>

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SaveFileManager.generated.h"

/**
 * 
 */

UCLASS()
class OBSCURE_API USaveFileManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "File I/O")
		static TArray<FString> LoadFileToStringArray(FString fileName);
};


/*
class SaveFileManager
{
public :
	SaveFileManager()
	{
		ModName = "SaveFileManager";
		ModVersion = "0.0.0";
		ModDescription = "Test of loading locations";
		ModAuthor = "Yaran";
		ModLoaderVersion = "2.0.0";

		ModRef = this;
		CompleteModCreation();
	}

	virtual void InitializeMod() override;
	virtual void InitGameState() override;
	virtual void BeginPlay(UE4::AActor *Actor) override;

};
*/