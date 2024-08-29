import typing
from dataclasses import dataclass
from Options import DefaultOnToggle, Range, Toggle, DeathLink, Choice, PerGameCommonOptions, OptionSet
from .Items import useless_items


@dataclass
class CCCharlesOptions(PerGameCommonOptions):
    death_link: DeathLink
