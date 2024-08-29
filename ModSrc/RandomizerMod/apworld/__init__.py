import typing
import os
import json
from .Items import item_table, scrap_item_table, CCCharlesItem
from .Locations import location_table, CCCharlesLocation
from .Options import CCCharlesOptions
from .Rules import set_rules
from .Regions import create_regions, CCCharlesLevels
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

    item_name_to_id = item_table
    location_name_to_id = location_table

    # Max int : 32767 (necessary for IDs)
    # item_name_to_id = {name: data.code for name, data in item_table.items() if data.code is not None}
    # location_name_to_id = {name: data.code for name, data in location_table.items() if data.code is not None}
    # locked_locations = {name: data for name, data in location_table.items() if data.locked_item}
    # item_name_groups = item_groups

    # this gives the generator all the definitions for our options
    options_dataclass = CCCharlesOptions
    # this gives us typing hints for all the options we defined
    options: CCCharlesOptions

    topology_present = True  # show path to required location checks in spoiler

    def create_item(self, name: str) -> Item:
        item_id = item_table[name]

        match name:
            case "Scraps" :
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
            case "Temple Key" :
                classification = ItemClassification.progression
            case "Bug spray" :
                classification = ItemClassification.progression
            case _:
                classification = ItemClassification.filler

        item = CCCharlesItem(name, classification, item_id, self.player)

        return item

