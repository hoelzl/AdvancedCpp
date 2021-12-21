add_executable("rpg_dice_test")

target_sources("rpg_dice_test" PRIVATE
    "rpg_dice_test.cpp")

target_link_libraries("rpg_dice_test"
    "Catch2WithMain"
	"rpg_dice_lib"
)