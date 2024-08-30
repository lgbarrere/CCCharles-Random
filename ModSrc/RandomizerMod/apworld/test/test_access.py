from . import MyGameTestBase


class TestChestAccess(MyGameTestBase):
    def test_sword_chests(self) -> None:
        """Test locations that require 4 Breakers"""
        locations = ["claire_mission_end"]
        items = [["Breaker"], ["Breaker"], ["Breaker"], ["Breaker"]]
        # this will test that each location can't be accessed without 4 "Breaker", but can be accessed once obtained
        self.assertAccessDependency(locations, items)
