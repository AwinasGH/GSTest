// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GS_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GSTEST_API AGS_PlayerController : public APlayerController
{
	GENERATED_BODY()

	
//constructor
public:

	AGS_PlayerController();

//c++ methods
protected:

	virtual void BeginPlay() override;

//>>...........................................................................................................................................<<//

//Blueprint values
public:
	
	UPROPERTY(BlueprintReadOnly, Category = "PlayerController")
		class AGS_GameHUD* MyGameHUD = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerController|Components")
		class UGS_InventoryDataComponent* InventoryData;
};




