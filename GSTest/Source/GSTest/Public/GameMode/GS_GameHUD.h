// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GS_GameHUD.generated.h"



UENUM()
enum class EWidgetFocusType : uint8
{
	GameOnly,
	UIOnly,
	GameAndUI
};


USTRUCT()
struct FWidgetFocusInfo
{
	GENERATED_USTRUCT_BODY()

public:

	FWidgetFocusInfo() {}
	FWidgetFocusInfo(EWidgetFocusType WidgetFocusType, UUserWidget* InWidget) :
		FocusType(WidgetFocusType), Widget(InWidget)
	{

	}

public:

	EWidgetFocusType FocusType;

	UPROPERTY()
	UUserWidget* Widget = nullptr;
};


/**
 * 
 */
UCLASS()
class GSTEST_API AGS_GameHUD : public AHUD
{
	GENERATED_BODY()

	
//Constructor
public:

	AGS_GameHUD();
	

//c++ methods
public:
	
	
	void SetFocusToWidget(EWidgetFocusType WidgetFocusType, UUserWidget* Widget);
	void AddWidgetToFocusStack(EWidgetFocusType WidgetFocusType, UUserWidget* Widget);
	void RemoveWidgetFromFocusStack(UUserWidget* Widget);
	void FocusLastWidgetInStack();
	void ClearWidgetFocusStack();


//c++ methods
protected:

	virtual void BeginPlay() override;

//c++ values
private:

	UPROPERTY()
		TArray<FWidgetFocusInfo> WidgetFocusStack;
	

//>>.................................................................................................................................................<<//

//Blueprint values
public:

	UPROPERTY(BlueprintReadOnly)
		class AGS_PlayerController* MyController = nullptr;

//Blueprint methods
public:

	UFUNCTION(BlueprintCallable, Category = "InventoryWD")
		void CreateInventoryWD();
	UFUNCTION(BlueprintCallable, Category = "InventoryWD")
		void SetFocusToInventoryWD();
	UFUNCTION(BlueprintCallable, Category = "InventoryWD")
		void RemoveInventoryWD();


//Blueprint values
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
		TSoftClassPtr<class UGS_InventoryWD> InventoryWDClass;
	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
		class UGS_InventoryWD* InventoryWD = nullptr;
};
