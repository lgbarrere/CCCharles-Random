from enum import Flag, auto
from typing import Callable, Union, Dict, Set

from BaseClasses import MultiWorld
from ..generic.Rules import add_rule, set_rule
from .Locations import location_table
from .Options import CCCharlesOptions
from .Regions import CCCharlesAreas
from .Items import useless_items


class RequiredItem(Flag):
    BARN_KEY = auto()
    CANDICE_KEY = auto()
    DEAD_FISH = auto()
    LOCKPICKS = auto()
    ANCIENT_TABLET = auto()
    SOUTH_MINE_KEY = auto()
    BLUE_BOX = auto()
    PAGE_COUNT_8 = auto()
    JOURNAL = auto()
    TIMED_DYNAMITE = auto()
    BOX_OF_ROCKET = auto()
    NORTH_MINE_KEY = auto()
    BREAKER_COUNT_4 = auto()
    REMOTE_EXPLOSIVE_COUNT_8 = auto()
    BROKEN_BOB = auto()
    MOUNTAIN_RUIN_KEY = auto()
    EMPLOYMENT_CONTRACTS = auto()
    MOB_CAMP_KEY = auto()
    JAR_OF_PICKLES = auto()
    TEMPLE_KEY = auto()
    BUG_SPRAY = auto()


class RuleFactory:
    world: MultiWorld
    rule_dict: dict

    def __init__(self, world, options: CCCharlesOptions):
        self.world = world


    def can_place_item_at_location(self, ruled_item: RequiredItem, location: str) -> bool:
        """
        Check if an item useful to access at least one more other item can be placed at a ruled location.
        A required item cannot be placed in a location this item is necessary to access it
        """
        if ruled_item in self.rule_dict[location] :
            return False
        return True


def set_rules(world, options: CCCharlesOptions):
    rf = RuleFactory(world, options)

    # Tony
    rf.rule_dict["scrap_tony_tiddle_1"] = RequiredItem.BARN_KEY
    rf.rule_dict["scrap_tony_tiddle_2"] = RequiredItem.BARN_KEY
    rf.rule_dict["scrap_tony_tiddle_3"] = RequiredItem.BARN_KEY
    rf.rule_dict["scrap_tony_tiddle_4"] = RequiredItem.BARN_KEY
    rf.rule_dict["scrap_tony_tiddle_5"] = RequiredItem.BARN_KEY
    rf.rule_dict["scrap_tony_tiddle_6"] = RequiredItem.BARN_KEY
    rf.rule_dict["scrap_tony_tiddle_7"] = RequiredItem.BARN_KEY
    rf.rule_dict["scrap_tony_tiddle_8"] = RequiredItem.BARN_KEY
    rf.rule_dict["scrap_tony_tiddle_9"] = RequiredItem.BARN_KEY

    # Candice
    rf.rule_dict["scrap_candice_1"] = RequiredItem.CANDICE_KEY
    rf.rule_dict["scrap_candice_2"] = RequiredItem.CANDICE_KEY
    rf.rule_dict["scrap_candice_3"] = RequiredItem.CANDICE_KEY
    rf.rule_dict["scrap_candice_4"] = RequiredItem.CANDICE_KEY
    rf.rule_dict["scrap_candice_5"] = RequiredItem.CANDICE_KEY
    rf.rule_dict["scrap_candice_6"] = RequiredItem.CANDICE_KEY
    rf.rule_dict["scrap_candice_7"] = RequiredItem.CANDICE_KEY
    rf.rule_dict["scrap_candice_8"] = RequiredItem.CANDICE_KEY
    rf.rule_dict["scrap_candice_9"] = RequiredItem.CANDICE_KEY

    # Lizbeth
    rf.rule_dict["lizbeth_murkwater_mission_end"] = RequiredItem.DEAD_FISH

    # Daryl
    rf.rule_dict["ancient_tablet"] = RequiredItem.LOCKPICKS
    rf.rule_dict["daryl_mission_end"] = RequiredItem.ANCIENT_TABLET

    # Dianne
    rf.rule_dict["scrap_dianne_chest_1"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_dianne_chest_2"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_dianne_chest_3"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_dianne_chest_4"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_dianne_chest_5"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_dianne_chest_6"] = RequiredItem.LOCKPICKS

    # South Mine
    rf.rule_dict["scrap_south_mine_inside_1"] = RequiredItem.SOUTH_MINE_KEY
    rf.rule_dict["scrap_south_mine_inside_2"] = RequiredItem.SOUTH_MINE_KEY
    rf.rule_dict["scrap_south_mine_inside_3"] = RequiredItem.SOUTH_MINE_KEY
    rf.rule_dict["scrap_south_mine_inside_4"] = RequiredItem.SOUTH_MINE_KEY
    rf.rule_dict["scrap_south_mine_inside_5"] = RequiredItem.SOUTH_MINE_KEY
    rf.rule_dict["scrap_south_mine_inside_6"] = RequiredItem.SOUTH_MINE_KEY
    rf.rule_dict["scrap_south_mine_inside_7"] = RequiredItem.SOUTH_MINE_KEY
    rf.rule_dict["scrap_south_mine_inside_8"] = RequiredItem.SOUTH_MINE_KEY
    rf.rule_dict["scrap_south_mine_inside_9"] = RequiredItem.SOUTH_MINE_KEY
    rf.rule_dict["green_paint_can"] = RequiredItem.SOUTH_MINE_KEY | RequiredItem.LOCKPICKS

    # Theodore
    rf.rule_dict["theodore_mission_end"] = RequiredItem.BLUE_BOX

    # Observatory
    rf.rule_dict["pink_paint_can"] = RequiredItem.LOCKPICKS

    # Sasha
    rf.rule_dict["sasha_mission_end"] = RequiredItem.PAGE_COUNT_8

    # Santiago
    rf.rule_dict["santiago_mission_end"] = RequiredItem.JOURNAL

    # Trench House
    rf.rule_dict["scrap_trench_house_1"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_trench_house_2"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_trench_house_3"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_trench_house_4"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_trench_house_5"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_trench_house_6"] = RequiredItem.LOCKPICKS

    # Far East House
    rf.rule_dict["scrap_far_east_house_15"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_far_east_house_16"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_far_east_house_17"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_far_east_house_18"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_far_east_house_19"] = RequiredItem.LOCKPICKS

    # Explosive training
    rf.rule_dict["scrap_explosive_training_11"] = RequiredItem.TIMED_DYNAMITE
    rf.rule_dict["scrap_explosive_training_12"] = RequiredItem.TIMED_DYNAMITE
    rf.rule_dict["box_of_rocket"] = RequiredItem.TIMED_DYNAMITE

    # John
    rf.rule_dict["john_smith_mission_end"] = RequiredItem.BOX_OF_ROCKET

    # Claire
    rf.rule_dict["claire_mission_end"] = RequiredItem.BREAKER_COUNT_4

    # North Mine
    rf.rule_dict["scrap_inside_north_mine_1"] = RequiredItem.NORTH_MINE_KEY
    rf.rule_dict["scrap_inside_north_mine_2"] = RequiredItem.NORTH_MINE_KEY
    rf.rule_dict["scrap_inside_north_mine_3"] = RequiredItem.NORTH_MINE_KEY
    rf.rule_dict["scrap_inside_north_mine_4"] = RequiredItem.NORTH_MINE_KEY
    rf.rule_dict["scrap_inside_north_mine_5"] = RequiredItem.NORTH_MINE_KEY
    rf.rule_dict["scrap_inside_north_mine_6"] = RequiredItem.NORTH_MINE_KEY
    rf.rule_dict["scrap_inside_north_mine_7"] = RequiredItem.NORTH_MINE_KEY
    rf.rule_dict["scrap_inside_north_mine_8"] = RequiredItem.NORTH_MINE_KEY
    rf.rule_dict["scrap_inside_north_mine_9"] = RequiredItem.NORTH_MINE_KEY
    rf.rule_dict["scrap_inside_north_mine_10"] = RequiredItem.NORTH_MINE_KEY
    rf.rule_dict["scrap_inside_north_mine_11"] = RequiredItem.NORTH_MINE_KEY
    rf.rule_dict["scrap_inside_north_mine_12"] = RequiredItem.NORTH_MINE_KEY
    rf.rule_dict["scrap_inside_north_mine_13"] = RequiredItem.NORTH_MINE_KEY
    rf.rule_dict["blue_egg"] = RequiredItem.NORTH_MINE_KEY
    rf.rule_dict["blue_paint_can"] = RequiredItem.NORTH_MINE_KEY | RequiredItem.LOCKPICKS

    # Paul
    rf.rule_dict["paul_mission_end"] = RequiredItem.REMOTE_EXPLOSIVE_COUNT_8

    # Beach
    rf.rule_dict["scrap_beach_1"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_beach_2"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_beach_3"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_beach_4"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_beach_5"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_beach_6"] = RequiredItem.LOCKPICKS

    # Caravan
    rf.rule_dict["scrap_caravan_10"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_caravan_11"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_caravan_12"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_caravan_13"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_caravan_14"] = RequiredItem.LOCKPICKS

    # Ronny
    rf.rule_dict["ronny_mission_end"] = RequiredItem.EMPLOYMENT_CONTRACTS

    # North Frank Fisher
    rf.rule_dict["scrap_north_frank_fisher_1"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_north_frank_fisher_2"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_north_frank_fisher_3"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_north_frank_fisher_4"] = RequiredItem.LOCKPICKS

    # Hidden Hole
    rf.rule_dict["scrap_hidden_hole_1"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_hidden_hole_2"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_hidden_hole_3"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_hidden_hole_4"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_hidden_hole_5"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_hidden_hole_6"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_hidden_hole_7"] = RequiredItem.LOCKPICKS

    # Mob Camp
    rf.rule_dict["scrap_mob_camp_17"] = RequiredItem.MOB_CAMP_KEY
    rf.rule_dict["scrap_mob_camp_18"] = RequiredItem.MOB_CAMP_KEY
    rf.rule_dict["stolen_bob"] = RequiredItem.MOB_CAMP_KEY | RequiredItem.BROKEN_BOB

    # Mountain Ruin
    rf.rule_dict["scrap_mountain_ruin_inside_1"] = RequiredItem.MOUNTAIN_RUIN_KEY
    rf.rule_dict["scrap_mountain_ruin_inside_2"] = RequiredItem.MOUNTAIN_RUIN_KEY
    rf.rule_dict["scrap_mountain_ruin_inside_3"] = RequiredItem.MOUNTAIN_RUIN_KEY
    rf.rule_dict["scrap_mountain_ruin_inside_4"] = RequiredItem.MOUNTAIN_RUIN_KEY
    rf.rule_dict["scrap_mountain_ruin_inside_5"] = RequiredItem.MOUNTAIN_RUIN_KEY
    rf.rule_dict["scrap_mountain_ruin_inside_6"] = RequiredItem.MOUNTAIN_RUIN_KEY
    rf.rule_dict["scrap_mountain_ruin_inside_7"] = RequiredItem.MOUNTAIN_RUIN_KEY
    rf.rule_dict["scrap_mountain_ruin_inside_8"] = RequiredItem.MOUNTAIN_RUIN_KEY
    rf.rule_dict["scrap_mountain_ruin_inside_9"] = RequiredItem.MOUNTAIN_RUIN_KEY
    rf.rule_dict["scrap_mountain_ruin_inside_10"] = RequiredItem.MOUNTAIN_RUIN_KEY
    rf.rule_dict["scrap_mountain_ruin_inside_11"] = RequiredItem.MOUNTAIN_RUIN_KEY
    rf.rule_dict["scrap_mountain_ruin_inside_12"] = RequiredItem.MOUNTAIN_RUIN_KEY
    rf.rule_dict["scrap_mountain_ruin_inside_13"] = RequiredItem.MOUNTAIN_RUIN_KEY
    rf.rule_dict["scrap_mountain_ruin_inside_14"] = RequiredItem.MOUNTAIN_RUIN_KEY
    rf.rule_dict["scrap_mountain_ruin_inside_15"] = RequiredItem.MOUNTAIN_RUIN_KEY
    rf.rule_dict["scrap_mountain_ruin_inside_16"] = RequiredItem.MOUNTAIN_RUIN_KEY
    rf.rule_dict["scrap_mountain_ruin_inside_17"] = RequiredItem.MOUNTAIN_RUIN_KEY
    rf.rule_dict["red_egg"] = RequiredItem.MOUNTAIN_RUIN_KEY
    rf.rule_dict["red_paint_can"] = RequiredItem.MOUNTAIN_RUIN_KEY | RequiredItem.LOCKPICKS

    # Prism Temple
    rf.rule_dict["scrap_prism_temple_1"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_prism_temple_2"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_prism_temple_3"] = RequiredItem.LOCKPICKS
    
    # Pickle
    rf.rule_dict["jar_of_pickles"] = RequiredItem.LOCKPICKS
    rf.rule_dict["pickle_lady_mission_end"] = RequiredItem.JAR_OF_PICKLES
    rf.rule_dict["scrap_pickle_lady_21"] = RequiredItem.JAR_OF_PICKLES
    rf.rule_dict["scrap_pickle_lady_22"] = RequiredItem.JAR_OF_PICKLES

    # Morse Refuge
    rf.rule_dict["scrap_morse_refuge_1"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_morse_refuge_2"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_morse_refuge_3"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_morse_refuge_4"] = RequiredItem.LOCKPICKS
    rf.rule_dict["scrap_morse_refuge_5"] = RequiredItem.LOCKPICKS
