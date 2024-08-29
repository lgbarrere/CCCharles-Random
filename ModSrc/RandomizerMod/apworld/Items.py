from BaseClasses import Item
from BaseID import base_id


class CCCharlesItem(Item):
    game = "Choo-Choo Charles"


optional_items = {
    "Scraps" : base_id + 1,
    "South Mine Key" : base_id + 2,
    "North Mine Key" : base_id + 3,
    "Mountain Ruin Key" : base_id + 4,
    "Barn Key" : base_id + 5,
    "Candice's Key" : base_id + 6,
    "Dead Fish" : base_id + 7,
    "Lockpicks" : base_id + 8,
    "Ancient Tablet" : base_id + 9,
    "Blue Box" : base_id + 10,
    "Page Drawing" : base_id + 11,
    "Journal" : base_id + 12,
    "Timed Dynamite" : base_id + 13,
    "Box of Rocket" : base_id + 14,
    "Breaker" : base_id + 15,
    "Broken Bob" : base_id + 16,
    "Employment Contracts" : base_id + 17,
    "Mob Camp Key" : base_id + 18,
    "Jar of Pickles" : base_id + 19
}

useless_items = {
    "Orange Paint Can" : base_id + 20,
    "Green Paint Can" : base_id + 21,
    "White Paint Can" : base_id + 22,
    "Pink Paint Can" : base_id + 23,
    "Gray Paint Can" : base_id + 24,
    "Blue Paint Can" : base_id + 25,
    "Black Paint Can" : base_id + 26,
    "Lime Paint Can" : base_id + 27,
    "Light Blue Paint Can" : base_id + 28,
    "Red Paint Can" : base_id + 29,
    "Purple Paint Can" : base_id + 30,
    "The Boomer" : base_id + 31,
    "Bob" : base_id + 32
}

progression_items = {
    "Green Egg" : base_id + 33,
    "Blue Egg" : base_id + 34,
    "Red Egg" : base_id + 35,
    "Remote Explosive" : base_id + 36,
    "Temple Key" : base_id + 37,
    "Bug spray" : base_id + 38
}

item_table = {**optional_items, **useless_items, **progression_items}
