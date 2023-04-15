// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Systems/Inventory/InventoryData.h"
#include "GS_InventoryWD.generated.h"


class UScrollBox;
class UButton;
class UGS_CategoryContainerWD;
class UGS_InventoryDataComponent;
class AGS_GameHUD;

/*
	Inventory widget
*/
UCLASS(Abstract)
class GSTEST_API UGS_InventoryWD : public UUserWidget
{
	GENERATED_BODY()

//constructor
public:
	
	UGS_InventoryWD(const FObjectInitializer& ObjectInitializer);

	
//c++ methods
protected:
	
	void InitializeVariantComboBox();

	void UpdateWeightInfo();
	
	void UpdateCategories();
	
	void CreateProgressImage(int32 CategoryWeight, FLinearColor Color);

	UFUNCTION()
		void OnAddButtonClicked();
	
	UFUNCTION()
		void OnInventoryUpdate();
	
	UFUNCTION()
		void OnRemoveButtonClicked();
	
	UGS_CategoryContainerWD* CreateCategory(ECategories NewCategory, const FLinearColor& Color);
	
//>>..........................................................................................................................<<//



//Blueprint methods
public:

	UFUNCTION(BlueprintCallable, Category = "InventoryWD")
		void InitializeInventoryWD(AGS_GameHUD* InGameHUD, UGS_InventoryDataComponent* InventoryDataComponent);

//Blueprint values
public:

	/*
		Contains pointers to all category widgets.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "InventoryWD")
		TMap<ECategories, UGS_CategoryContainerWD*> CategoryWDs;
	/*
		Container class for Inventory Category's.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InventoryWD")
		TSubclassOf<UGS_CategoryContainerWD> CategoryContainerClass = nullptr;

	/*
		Contains colors for categories
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CategoryContainerWD")
		TMap<ECategories, FLinearColor> CategoriesColors;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CategoryContainerWD")
		FLinearColor WeightProgressBackgroundColor;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "InventoryWD | Widgets")
		UScrollBox* CategoriesWDsScrollBox = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "InventoryWD | Widgets")
		class UTextBlock* WeightText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "InventoryWD | Widgets")
		class UComboBoxString* ItemVariantComboBox = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "InventoryWD | Widgets")
		class UHorizontalBox* WeightProgressBox = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "InventoryWD | Widgets")
		UButton* AddItemButton = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "InventoryWD | Widgets")
		UButton* RemoveItemButton = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
		AGS_GameHUD* GameHUD = nullptr;

	UPROPERTY(BlueprintReadOnly)
		UGS_InventoryDataComponent* InventoryComponent;
};


