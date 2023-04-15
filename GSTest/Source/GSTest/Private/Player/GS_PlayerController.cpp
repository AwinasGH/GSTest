// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GS_PlayerController.h"

#include "GameMode/GS_GameHUD.h"
#include "Systems/Inventory/InventoryDataComponent/GS_InventoryDataComponent.h"

AGS_PlayerController::AGS_PlayerController()
{
	InventoryData = CreateDefaultSubobject<UGS_InventoryDataComponent>("InventoryData");
}

void AGS_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	MyGameHUD = Cast<AGS_GameHUD>(GetHUD());
}


