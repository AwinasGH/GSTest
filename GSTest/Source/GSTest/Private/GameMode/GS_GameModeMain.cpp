// Fill out your copyright notice in the Description page of Project Settings.


#include "GSTest/Public/GameMode/GS_GameModeMain.h"

#include "GSTest/Public/GameMode/GS_GameHUD.h"
#include "GSTest/Public/Player/GS_PlayerController.h"

AGS_GameModeMain::AGS_GameModeMain()
{
	PlayerControllerClass = AGS_PlayerController::StaticClass();
	HUDClass = AGS_GameHUD::StaticClass();
}

