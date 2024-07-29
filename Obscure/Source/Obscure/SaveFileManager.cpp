// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveFileManager.h"

#include <Runtime/Core/Public/Misc/Paths.h>
#include <Runtime/Core/Public/HAL/PlatformFilemanager.h>

TArray<FString> USaveFileManager::LoadFileToStringArray(FString fileName)
{
	TArray<FString> result;
	FString directory = FPaths::ProjectContentDir();
	IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();

	if (file.CreateDirectory(*directory))
	{
		FString myFile = directory + "/" + fileName;
		FFileHelper::LoadFileToStringArray(result, *myFile);
	}

	return result;
}
