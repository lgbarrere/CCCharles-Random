from BaseClasses import MultiWorld
from ..generic.Rules import set_rule
from .Options import CCCharlesOptions


def set_rules(world: MultiWorld, options: CCCharlesOptions, player: int) -> None:
    # Tony
    set_rule(world.get_location("scrap_tony_tiddle_1", player),
        lambda state: state.has("Barn Key", player))
    set_rule(world.get_location("scrap_tony_tiddle_2", player),
        lambda state: state.has("Barn Key", player))
    set_rule(world.get_location("scrap_tony_tiddle_3", player),
        lambda state: state.has("Barn Key", player))
    set_rule(world.get_location("scrap_tony_tiddle_4", player),
        lambda state: state.has("Barn Key", player))
    set_rule(world.get_location("scrap_tony_tiddle_5", player),
        lambda state: state.has("Barn Key", player))
    set_rule(world.get_location("scrap_tony_tiddle_6", player),
        lambda state: state.has("Barn Key", player))
    set_rule(world.get_location("scrap_tony_tiddle_7", player),
        lambda state: state.has("Barn Key", player))
    set_rule(world.get_location("scrap_tony_tiddle_8", player),
        lambda state: state.has("Barn Key", player))
    set_rule(world.get_location("scrap_tony_tiddle_9", player),
        lambda state: state.has("Barn Key", player))

    # Candice
    set_rule(world.get_location("scrap_candice_1", player),
        lambda state: state.has("Candice's Key", player))
    set_rule(world.get_location("scrap_candice_2", player),
        lambda state: state.has("Candice's Key", player))
    set_rule(world.get_location("scrap_candice_3", player),
        lambda state: state.has("Candice's Key", player))
    set_rule(world.get_location("scrap_candice_4", player),
        lambda state: state.has("Candice's Key", player))
    set_rule(world.get_location("scrap_candice_5", player),
        lambda state: state.has("Candice's Key", player))
    set_rule(world.get_location("scrap_candice_6", player),
        lambda state: state.has("Candice's Key", player))
    set_rule(world.get_location("scrap_candice_7", player),
        lambda state: state.has("Candice's Key", player))
    set_rule(world.get_location("scrap_candice_8", player),
        lambda state: state.has("Candice's Key", player))
    set_rule(world.get_location("scrap_candice_9", player),
        lambda state: state.has("Candice's Key", player))

    # Lizbeth
    set_rule(world.get_location("lizbeth_murkwater_mission_end", player),
        lambda state: state.has("Dead Fish", player))

    # Daryl
    set_rule(world.get_location("ancient_tablet", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("daryl_mission_end", player),
        lambda state: state.has("Ancient Tablet", player))

    # Dianne
    set_rule(world.get_location("scrap_dianne_chest_1", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_dianne_chest_2", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_dianne_chest_3", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_dianne_chest_4", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_dianne_chest_5", player),
        lambda state: state.has("Lockpicks", player))

    # South Mine
    set_rule(world.get_location("scrap_inside_south_mine_1", player),
        lambda state: state.has("South Mine Key", player))
    set_rule(world.get_location("scrap_inside_south_mine_2", player),
        lambda state: state.has("South Mine Key", player))
    set_rule(world.get_location("scrap_inside_south_mine_3", player),
        lambda state: state.has("South Mine Key", player))
    set_rule(world.get_location("scrap_inside_south_mine_4", player),
        lambda state: state.has("South Mine Key", player))
    set_rule(world.get_location("scrap_inside_south_mine_5", player),
        lambda state: state.has("South Mine Key", player))
    set_rule(world.get_location("scrap_inside_south_mine_6", player),
        lambda state: state.has("South Mine Key", player))
    set_rule(world.get_location("scrap_inside_south_mine_7", player),
        lambda state: state.has("South Mine Key", player))
    set_rule(world.get_location("scrap_inside_south_mine_8", player),
        lambda state: state.has("South Mine Key", player))
    set_rule(world.get_location("scrap_inside_south_mine_9", player),
        lambda state: state.has("South Mine Key", player))
    set_rule(world.get_location("green_paint_can", player),
        lambda state: state.has("South Mine Key", player) and
            state.has("Lockpicks", player))

    # Theodore
    set_rule(world.get_location("theodore_mission_end", player),
        lambda state: state.has("Blue Box", player))

    # Watchtower
    set_rule(world.get_location("pink_paint_can", player),
        lambda state: state.has("Lockpicks", player))

    # Sasha
    set_rule(world.get_location("sasha_mission_end", player),
            lambda state: state.has("Page Drawing", player, 8))

    # Santiago
    set_rule(world.get_location("santiago_mission_end", player),
        lambda state: state.has("Journal", player))

    # Trench House
    set_rule(world.get_location("scrap_trench_house_chest_1", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_trench_house_chest_2", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_trench_house_chest_3", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_trench_house_chest_4", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_trench_house_chest_5", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_trench_house_chest_6", player),
        lambda state: state.has("Lockpicks", player))

    # Far East House
    set_rule(world.get_location("scrap_far_east_house_chest_1", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_far_east_house_chest_2", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_far_east_house_chest_3", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_far_east_house_chest_4", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_far_east_house_chest_5", player),
        lambda state: state.has("Lockpicks", player))

    # Explosive training
    set_rule(world.get_location("scrap_explosive_training_11", player),
        lambda state: state.has("Timed Dynamite", player))
    set_rule(world.get_location("scrap_explosive_training_12", player),
        lambda state: state.has("Timed Dynamite", player))
    set_rule(world.get_location("box_of_rocket", player),
        lambda state: state.has("Timed Dynamite", player))

    # John
    set_rule(world.get_location("john_smith_mission_end", player),
         lambda state: state.has("Box of Rocket", player))

    # Claire
    set_rule(world.get_location("claire_mission_end", player),
        lambda state: state.has("Breaker", player, 4))

    # North Mine
    set_rule(world.get_location("scrap_inside_north_mine_1", player),
        lambda state: state.has("North Mine Key", player))
    set_rule(world.get_location("scrap_inside_north_mine_2", player),
        lambda state: state.has("North Mine Key", player))
    set_rule(world.get_location("scrap_inside_north_mine_3", player),
        lambda state: state.has("North Mine Key", player))
    set_rule(world.get_location("scrap_inside_north_mine_4", player),
        lambda state: state.has("North Mine Key", player))
    set_rule(world.get_location("scrap_inside_north_mine_5", player),
        lambda state: state.has("North Mine Key", player))
    set_rule(world.get_location("scrap_inside_north_mine_6", player),
        lambda state: state.has("North Mine Key", player))
    set_rule(world.get_location("scrap_inside_north_mine_7", player),
        lambda state: state.has("North Mine Key", player))
    set_rule(world.get_location("scrap_inside_north_mine_8", player),
        lambda state: state.has("North Mine Key", player))
    set_rule(world.get_location("scrap_inside_north_mine_9", player),
        lambda state: state.has("North Mine Key", player))
    set_rule(world.get_location("scrap_inside_north_mine_10", player),
        lambda state: state.has("North Mine Key", player))
    set_rule(world.get_location("scrap_inside_north_mine_11", player),
        lambda state: state.has("North Mine Key", player))
    set_rule(world.get_location("scrap_inside_north_mine_12", player),
        lambda state: state.has("North Mine Key", player))
    set_rule(world.get_location("scrap_inside_north_mine_13", player),
        lambda state: state.has("North Mine Key", player))
    set_rule(world.get_location("blue_egg", player),
        lambda state: state.has("North Mine Key", player))
    set_rule(world.get_location("blue_paint_can", player),
        lambda state: state.has("North Mine Key", player) and
            state.has("Lockpicks", player))

    # Paul
    set_rule(world.get_location("paul_mission_end", player),
             lambda state: state.has("Remote Explosive x8", player))
        # lambda state: state.has("Remote Explosive", player, 8)) # TODO : Add an option to split remote explosives

    # Beach
    set_rule(world.get_location("scrap_beach_chest_1", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_beach_chest_2", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_beach_chest_3", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_beach_chest_4", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_beach_chest_5", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_beach_chest_6", player),
        lambda state: state.has("Lockpicks", player))

    # Caravan
    set_rule(world.get_location("scrap_caravan_chest_1", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_caravan_chest_2", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_caravan_chest_3", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_caravan_chest_4", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_caravan_chest_5", player),
        lambda state: state.has("Lockpicks", player))

    # Ronny
    set_rule(world.get_location("ronny_mission_end", player),
        lambda state: state.has("Employment Contracts", player))

    # North Frank Fisher
    set_rule(world.get_location("scrap_north_frank_fisher_chest_1", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_north_frank_fisher_chest_2", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_north_frank_fisher_chest_3", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_north_frank_fisher_chest_4", player),
        lambda state: state.has("Lockpicks", player))

    # Hidden Hole
    set_rule(world.get_location("scrap_hidden_hole_chest_1", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_hidden_hole_chest_2", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_hidden_hole_chest_3", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_hidden_hole_chest_4", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_hidden_hole_chest_5", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_hidden_hole_chest_6", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_hidden_hole_chest_7", player),
        lambda state: state.has("Lockpicks", player))

    # Mob Camp
    set_rule(world.get_location("scrap_mob_camp_17", player),
        lambda state: state.has("Mob Camp Key", player))
    set_rule(world.get_location("scrap_mob_camp_18", player),
        lambda state: state.has("Mob Camp Key", player))
    set_rule(world.get_location("stolen_bob", player),
        lambda state: state.has("Mob Camp Key", player) and
            state.has("Broken Bob", player))

    # Mountain Ruin
    set_rule(world.get_location("scrap_inside_mountain_ruin_1", player),
        lambda state: state.has("Mountain Ruin Key", player))
    set_rule(world.get_location("scrap_inside_mountain_ruin_2", player),
        lambda state: state.has("Mountain Ruin Key", player))
    set_rule(world.get_location("scrap_inside_mountain_ruin_3", player),
        lambda state: state.has("Mountain Ruin Key", player))
    set_rule(world.get_location("scrap_inside_mountain_ruin_4", player),
        lambda state: state.has("Mountain Ruin Key", player))
    set_rule(world.get_location("scrap_inside_mountain_ruin_5", player),
        lambda state: state.has("Mountain Ruin Key", player))
    set_rule(world.get_location("scrap_inside_mountain_ruin_6", player),
        lambda state: state.has("Mountain Ruin Key", player))
    set_rule(world.get_location("scrap_inside_mountain_ruin_7", player),
        lambda state: state.has("Mountain Ruin Key", player))
    set_rule(world.get_location("scrap_inside_mountain_ruin_8", player),
        lambda state: state.has("Mountain Ruin Key", player))
    set_rule(world.get_location("scrap_inside_mountain_ruin_9", player),
        lambda state: state.has("Mountain Ruin Key", player))
    set_rule(world.get_location("scrap_inside_mountain_ruin_10", player),
        lambda state: state.has("Mountain Ruin Key", player))
    set_rule(world.get_location("scrap_inside_mountain_ruin_11", player),
        lambda state: state.has("Mountain Ruin Key", player))
    set_rule(world.get_location("scrap_inside_mountain_ruin_12", player),
        lambda state: state.has("Mountain Ruin Key", player))
    set_rule(world.get_location("scrap_inside_mountain_ruin_13", player),
        lambda state: state.has("Mountain Ruin Key", player))
    set_rule(world.get_location("scrap_inside_mountain_ruin_14", player),
        lambda state: state.has("Mountain Ruin Key", player))
    set_rule(world.get_location("scrap_inside_mountain_ruin_15", player),
        lambda state: state.has("Mountain Ruin Key", player))
    set_rule(world.get_location("scrap_inside_mountain_ruin_16", player),
        lambda state: state.has("Mountain Ruin Key", player))
    set_rule(world.get_location("scrap_inside_mountain_ruin_17", player),
        lambda state: state.has("Mountain Ruin Key", player))
    set_rule(world.get_location("red_egg", player),
        lambda state: state.has("Mountain Ruin Key", player))
    set_rule(world.get_location("red_paint_can", player),
        lambda state: state.has("Mountain Ruin Key", player) and
            state.has("Lockpicks", player))

    # Prism Temple
    set_rule(world.get_location("scrap_prism_temple_chest_1", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_prism_temple_chest_2", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_prism_temple_chest_3", player),
        lambda state: state.has("Lockpicks", player))

    # Pickle
    set_rule(world.get_location("jar_of_pickles", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("pickle_lady_mission_end", player),
         lambda state: state.has("Jar of Pickles", player))

    # Morse Refuge
    set_rule(world.get_location("scrap_morse_refuge_chest_1", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_morse_refuge_chest_2", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_morse_refuge_chest_3", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_morse_refuge_chest_4", player),
        lambda state: state.has("Lockpicks", player))
    set_rule(world.get_location("scrap_morse_refuge_chest_5", player),
        lambda state: state.has("Lockpicks", player))

    # Place "Victory" at "Final Boss" and set collection as win condition
    world.completion_condition[player] = lambda state: state.has("Victory", player)
