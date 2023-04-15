// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GS_CategoryContainerWD.generated.h"


enum class ECategories : uint8;

struct FItemInfo;

class UTextBlock;

/**
 * 
 */
UCLASS()
class GSTEST_API UGS_CategoryContainerWD : public UUserWidget
{
	GENERATED_BODY()

	friend class UGS_InventoryWD;
	
//constructor
public:
	
	UGS_CategoryContainerWD(const FObjectInitializer& ObjectInitializer);

//c++ methods
public:
	
	UFUNCTION(BlueprintCallable, Category = "CategoryContainerWD")
		void InitializeCategoryContainerWD(ECategories CategoryType, class UGS_InventoryDataComponent* InventoryDataComponent, const FLinearColor& Color);

//c++ values
private:

	ECategories CurrentCategory;

//c++ methods
protected:

	bool UpdateCategory();

//>>..........................................................................................................................<<//


//Blueprint methods
public:

	UFUNCTION(BlueprintCallable, Category = "CategoryContainerWD")
		bool CreateSlotWithInfo(const FItemInfo& NewItemInfo, int32 InRow, int32 InColumn);

//Blueprint values
public:

	/*
		Text block for Slot Items count.
	*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CategoryContainerWD | Widgets")
		UTextBlock* WeightText = nullptr;
	/*
		Text block for Slot Items count.
	*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CategoryContainerWD | Widgets")
		UTextBlock* CategoryNameTextBox = nullptr;
	/*
		Text block for Slot Items count.
	*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CategoryContainerWD | Widgets")
		class UImage* CategoryColor = nullptr;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CategoryContainerWD | Widgets")
		TSubclassOf<class UGS_InventorySlotWD> InventorySlotClass = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CategoryContainerWD")
		int32 MaxColumnsInRow = 5;

	/*
		InventoryPanel - Panel for displaying items in inventory.
	*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CategoryContainerWD | Widgets")
		class UUniformGridPanel* InventoryPanel = nullptr;


	UPROPERTY(BlueprintReadOnly, Category = "CategoryContainerWD | Widgets")
		class UGS_InventoryDataComponent* InventoryComponent = nullptr;
};
