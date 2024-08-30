import typing
from enum import Enum

from BaseClasses import MultiWorld, Region, Location
from .Options import CCCharlesOptions
from .Locations import loc_start_camp, loc_tony_tiddle_mission, loc_candice_mission, loc_swamp, \
    loc_lizebth_murkwater_mission, loc_daryl_mission, loc_dianne_house, loc_helen_mission, loc_sgt_flint_mission, \
    loc_south_mine_outside, loc_south_mine_inside, loc_theodore_mission, loc_theodore_canyon, loc_observatory, \
    loc_ghost_boulder_field, loc_sasha_mission, loc_santiago_house, loc_stantiago_mission, loc_trench_house, \
    loc_doll_woods, loc_forest_lost_stairs, loc_far_east_house, loc_explosive_training, loc_john_smith_mission, \
    loc_greg_mission, loc_claire_mission, loc_outside_north_mine, loc_inside_north_mine, loc_wood_bridge, \
    loc_paul_mission, loc_gertrude_mission, loc_beach, loc_church, loc_gale_mission, loc_caravan, \
    loc_abandonned_house, loc_ronny_mission, loc_north_frank_fisher, loc_hidden_hole, loc_mob_camp, \
    loc_mine_elevator_exit, loc_mountain_ruin_outside, loc_mountain_ruin_inside, loc_prism_temple, \
    loc_pickle_lady_mission, loc_temple_shrine, loc_morse_refuge, location_table


class CCCharlesRegion(Region):
    regions = []

    def __init__(self, world: MultiWorld, player: int):
        self.regions.append(Region("Menu", player, world, "Eugene's Boat"))
        self.regions.append(Region("Start Camp", player, world))
        self.regions.append(Region("Tony Tiddle Barn", player, world))
        self.regions.append(Region("Candice House", player, world))
        self.regions.append(Region("Swamp", player, world))
        self.regions.append(Region("Shack", player, world))
        self.regions.append(Region("Junkyard", player, world))
        self.regions.append(Region("Dianne House", player, world))
        self.regions.append(Region("Helen House", player, world))
        self.regions.append(Region("Military Base", player, world))
        self.regions.append(Region("South Mine Outside", player, world))
        self.regions.append(Region("South Mine Inside", player, world))
        self.regions.append(Region("Theodore Station", player, world))
        self.regions.append(Region("Theodore Canyon", player, world))
        self.regions.append(Region("Observation", player, world))
        self.regions.append(Region("Ghost Boulder Field", player, world))
        self.regions.append(Region("Sasha House", player, world))
        self.regions.append(Region("Santiago House", player, world))
        self.regions.append(Region("Santiago PORT", player, world))
        self.regions.append(Region("Trench House", player, world))
        self.regions.append(Region("Doll Woods", player, world))
        self.regions.append(Region("Forest Lost Stairs", player, world))
        self.regions.append(Region("Far East House", player, world))
        self.regions.append(Region("Explosive Training", player, world))
        self.regions.append(Region("John Smith Workshop", player, world))
        self.regions.append(Region("Greg Tower", player, world))
        self.regions.append(Region("Lighthouse", player, world))
        self.regions.append(Region("Outside North Mine", player, world))
        self.regions.append(Region("Inside North Mine", player, world))
        self.regions.append(Region("Wood Bridge", player, world))
        self.regions.append(Region("Paul Museum", player, world))
        self.regions.append(Region("Gertrude Base", player, world))
        self.regions.append(Region("Beach", player, world))
        self.regions.append(Region("Church", player, world))
        self.regions.append(Region("Gale House", player, world))
        self.regions.append(Region("Caravane", player, world))
        self.regions.append(Region("Abandonned House", player, world))
        self.regions.append(Region("Ronny Towers", player, world))
        self.regions.append(Region("North Frank Fisher", player, world))
        self.regions.append(Region("Hidden Hole", player, world))
        self.regions.append(Region("Mob Camp", player, world))
        self.regions.append(Region("Mine Elevator Exit", player, world))
        self.regions.append(Region("Mountain Ruin Outside", player, world))
        self.regions.append(Region("Mountain Ruin Inside", player, world))
        self.regions.append(Region("Prism Temple", player, world))
        self.regions.append(Region("Pickle Lady House", player, world))
        self.regions.append(Region("Temple Shrine", player, world))
        self.regions.append(Region("Morse Refuge", player, world))
