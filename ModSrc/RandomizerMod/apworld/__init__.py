import typing
import os
import json
from .Items import unique_item_dict, full_item_list, item_groups, CCCharlesItem
from .Locations import location_table, CCCharlesLocation
from .Options import CCCharlesOptions
from .Rules import set_rules
from .Regions import CCCharlesRegion
from BaseClasses import Item, Tutorial, ItemClassification, Region
from AutoWorld import World, WebWorld


class CCCharlesWeb(WebWorld):
    """
    Choo-Choo Charles is an horror game.
    A devil spider train from hell called Charles chases any person it finds on an island.
    The goal is to gather scraps to upgrade a train to fight Charles and travel with this train to find 3 eggs
    to lead Charles to a brutal death and save the island.
    """

    theme = "stone"

    tutorials = [Tutorial(
        "Multiworld Setup Guide",
        "A guide to setup Choo-Choo Charles for MultiWorld.",
        "English",
        "setup_en.md",
        "setup/en",
        ["Yaranorgoth"]
    )]

    game_info_languages = ["en", "fr"]


class CCCharlesWorld(World):
    """ 
    An independant 3D horror game, taking place on an island.
    The main gameplay is composed of 2 phases :
    > Traveling and fighting a monster on board a train
    > Walking disarmed to gather resources
    """

    game = "Choo-Choo Charles"

    web = CCCharlesWeb()

    item_name_to_id = unique_item_dict
    location_name_to_id = location_table
    item_name_groups = item_groups

    # this gives the generator all the definitions for our options
    options_dataclass = CCCharlesOptions
    # this gives us typing hints for all the options we defined
    options: CCCharlesOptions

    topology_present = True  # show path to required location checks in spoiler

    def create_regions(self) -> None :
        cccregion = CCCharlesRegion(self.multiworld, self.player)
        self.multiworld.regions += [cccregion.regions]

    def create_item(self, name: str) -> CCCharlesItem:
        item_id = unique_item_dict[name]

        match name:
            case "Scraps" :
                classification = ItemClassification.useful
            case "30 Scraps Reward" :
                classification = ItemClassification.useful
            case "25 Scraps Reward" :
                classification = ItemClassification.useful
            case "35 Scraps Reward" :
                classification = ItemClassification.useful
            case "40 Scraps Reward" :
                classification = ItemClassification.useful
            case "South Mine Key" :
                classification = ItemClassification.progression
            case "North Mine Key" :
                classification = ItemClassification.progression
            case "Mountain Ruin Key" :
                classification = ItemClassification.progression
            case "Barn Key" :
                classification = ItemClassification.progression
            case "Candice's Key" :
                classification = ItemClassification.progression
            case "Dead Fish" :
                classification = ItemClassification.progression
            case "Lockpicks" :
                classification = ItemClassification.progression
            case "Ancient Tablet" :
                classification = ItemClassification.progression
            case "Blue Box" :
                classification = ItemClassification.progression
            case "Page Drawing" :
                classification = ItemClassification.progression
            case "Journal" :
                classification = ItemClassification.progression
            case "Timed Dynamite" :
                classification = ItemClassification.progression
            case "Box of Rocket" :
                classification = ItemClassification.progression
            case "Breaker" :
                classification = ItemClassification.progression
            case "Broken Bob" :
                classification = ItemClassification.progression
            case "Employment Contracts" :
                classification = ItemClassification.progression
            case "Mob Camp Key" :
                classification = ItemClassification.progression
            case "Jar of Pickles" :
                classification = ItemClassification.progression
            case "Orange Paint Can" :
                classification = ItemClassification.filler
            case "Green Paint Can" :
                classification = ItemClassification.filler
            case "White Paint Can" :
                classification = ItemClassification.filler
            case "Pink Paint Can" :
                classification = ItemClassification.filler
            case "Gray Paint Can" :
                classification = ItemClassification.filler
            case "Blue Paint Can" :
                classification = ItemClassification.filler
            case "Black Paint Can" :
                classification = ItemClassification.filler
            case "Lime Paint Can" :
                classification = ItemClassification.filler
            case "Light Blue Paint Can" :
                classification = ItemClassification.filler
            case "Red Paint Can" :
                classification = ItemClassification.filler
            case "Purple Paint Can" :
                classification = ItemClassification.filler
            case "The Boomer" :
                classification = ItemClassification.filler
            case "Bob" :
                classification = ItemClassification.filler
            case "Green Egg" :
                classification = ItemClassification.progression
            case "Blue Egg" :
                classification = ItemClassification.progression
            case "Red Egg" :
                classification = ItemClassification.progression
            case "Remote Explosive" :
                classification = ItemClassification.progression
            case "Remote Explosive x8" :
                classification = ItemClassification.progression
            case "Temple Key" :
                classification = ItemClassification.progression
            case "Bug spray" :
                classification = ItemClassification.progression
            case _:
                classification = ItemClassification.filler

        return CCCharlesItem(name, classification, item_id, self.player)
    
    def create_items(self) -> None:
        self.multiworld.itempool += [self.create_item(item) for item in full_item_list]

        # Include Boss Beaten event
        victory_loc = CCCharlesLocation(self.player, "Boss Beaten", None)
        victory_loc.place_locked_item(CCCharlesItem("Boss Beaten", ItemClassification.progression, None, self.player))
    
    def set_rules(self) -> None:
        set_rules(self.multiworld, self.options, self.player)
