// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GS_InventorySlotWD.generated.h"

struct FItemInfo;

/**
 * 
 */
UCLASS()
class GSTEST_API UGS_InventorySlotWD : public UUserWidget
{
	GENERATED_BODY()
	
//Constructor
public:

	UGS_InventorySlotWD(const FObjectInitializer& ObjectInitializer);

//>>..........................................................................................................................<<//


//Blueprint methods
public:

	UFUNCTION(BlueprintCallable, Category = "InventoryWD")
		void InitializeInventorySlotWD(const FItemInfo& ItemInfo);

//Blueprint values
public:
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CategoryContainerWD | Widgets")
		class UImage* SlotImage = nullptr;
};
