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


class CCCharlesAreas(Enum):
    START_CAMP = 10000,
    TONY_TIDDLE_BARN = 100001,
    CANDICE_HOUSE = 100002,
    SWAMP = 100003,
    SHACK = 100004,
    JUNKYARD = 100005,
    DIANNE_HOUSE = 100006,
    HELEN_HOUSE = 100007,
    MILITARY_BASE = 100008,
    SOUTH_MINE_OUTSIDE = 100009,
    SOUTH_MINE_INSIDE = 100010,
    THEODORE_STATION = 100011,
    THEODORE_CANYON = 100012,
    OBSERVATORY = 100013,
    GHOST_BOULDER_FIELD = 100014,
    SASHA_HOUSE = 100015,
    SANTIAGO_HOUSE = 100016,
    SANTIAGO_PORT = 100017,
    TRENCH_HOUSE = 100018,
    DOLL_WOODS = 100019,
    FOREST_LOST_STAIRS = 100020,
    FAR_EAST_HOUSE = 100021,
    EXPLOSIVE_TRAINING = 100022,
    JOHN_SMITH_WORKSHOP = 100023,
    GREG_TOWER = 100024,
    LIGHTHOUSE = 100025,
    OUTSIDE_NORTH_MINE = 100026,
    INSIDE_NORTH_MINE = 100027,
    WOOD_BRIDGE = 100028,
    PAUL_MUSEUM = 100029,
    GERTRUDE_BASE = 100030,
    BEACH = 100031,
    CHRUCH = 100032,
    GALE_HOUSE = 100033,
    CARAVAN = 100034,
    ABANDONNED_HOUSE = 100035,
    RONNY_TOWERS = 100036,
    NORTH_FRANK_FISHER = 100037,
    HIDDEN_HOLE = 100038,
    MOB_CAMP = 100039,
    MINE_ELEVATOR_EXIT = 100040,
    MOUNTAIN_RUIN_OUTSIDE = 100041,
    MOUNTAIN_RUIN_INSIDE = 100042,
    PRISM_TEMPLE = 100043,
    PICKLE_LADY_HOUSE = 100044,
    TEMPLE_SHRINE = 100045,
    MORSE_REFUGE = 100046


class CCCharlesRegion(Region):
    subregions: typing.List[Region] = []

