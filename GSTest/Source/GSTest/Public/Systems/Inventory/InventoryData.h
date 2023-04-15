#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InventoryData.generated.h"


UENUM(BlueprintType)
enum class ECategories : uint8
{
	None = 0,
	
	Drugs UMETA(DisplayName = "Drugs"),
	Food UMETA(DisplayName = "Food"),
};

USTRUCT(BlueprintType)
struct FItemInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	bool operator==(const FItemInfo& Other) const
	{
		return this->Category == Other.Category
			&& this->Weight == Other.Weight
			&& this->ItemImage == Other.ItemImage;
	}

public:
	
	FItemInfo(const FText& InItemName, UTexture2D* ItemImage, const ECategories& InCategory, float InWeight)
		: ItemName(InItemName),
		  ItemImage(ItemImage),
		  Category(InCategory),
		  Weight(InWeight)
	{}

	FItemInfo()
		: ItemName(FText()),
		  ItemImage()
	{}


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default")
		FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default")
		UTexture2D* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default")
		ECategories Category = ECategories::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default")
		int32 Weight = 1.0f;
};



