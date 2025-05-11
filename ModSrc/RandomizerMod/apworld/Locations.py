from BaseClasses import Location
from .BaseID import base_id


class CCCharlesLocation(Location):
    game: str = "Choo-Choo Charles"


loc_start_camp = {
    "start_camp_scraps_1" : base_id + 1000, # (X=24006.348 Y=53777.297 Z=10860.107)
    "start_camp_scraps_2" : base_id + 1001 # (X=23951.754 Y=54897.230 Z=10895.235)
}

loc_tony_tiddle_mission = {
    "barn_tony_tiddle_mission_start" : base_id + 1002,
    "barn_scraps_1" : base_id + 1003, # (X=70582.805 Y=52591.066 Z=11976.719)
    "barn_scraps_2" : base_id + 1004, # (X=70536.641 Y=51890.633 Z=11986.488)
    "barn_scraps_3" : base_id + 1005, # (X=70750.336 Y=52275.828 Z=11994.434)
    "barn_scraps_4" : base_id + 1006, # (X=70937.719 Y=52989.066 Z=12003.523)
    "barn_scraps_5" : base_id + 1007, # (X=71303.508 Y=52232.188 Z=12003.997)
    "barn_scraps_6" : base_id + 1008, # (X=71678.672 Y=52825.531 Z=11977.212)
    "barn_scraps_7" : base_id + 1009, # (X=71506.961 Y=52357.293 Z=12362.159)
    "barn_scraps_8" : base_id + 1010, # (X=71029.875 Y=52384.613 Z=12362.159)
    "barn_scraps_9" : base_id + 1011 # (X=71129.594 Y=52600.262 Z=12364.142)
}

loc_tutorial_candice_mission = {
    "tutorial_candice_mission_start" : base_id + 1012,
    "tutorial_scraps_1" : base_id + 1013, # (X=74745.852 Y=73865.555 Z=11426.619)
    "tutorial_scraps_2" : base_id + 1014, # (X=74864.102 Y=73900.094 Z=11426.619)
    "tutorial_scraps_3" : base_id + 1015, # (X=74877.625 Y=73738.594 Z=11422.057) Existing match 4
    "tutorial_scraps_4" : base_id + 1016, # (X=75068.992 Y=73971.133 Z=11426.619)
    "tutorial_scraps_5" : base_id + 1017, # (X=74923.500 Y=73571.648 Z=11426.619)
    "tutorial_scraps_6" : base_id + 1018, # (X=75194.906 Y=73495.719 Z=11426.619)
    "tutorial_scraps_7" : base_id + 1019, # (X=75320.102 Y=73446.352 Z=11487.376)
    "tutorial_scraps_8" : base_id + 1020, # (X=75298.680 Y=73580.531 Z=11426.619)
    "tutorial_scraps_9" : base_id + 1021 # (X=75310.008 Y=73770.742 Z=11489.709)
}

loc_swamp = {
    "swamp_scraps_1" : base_id + 1022, # (X=81964.398 Y=72167.305 Z=10116.385)
    "swamp_scraps_2" : base_id + 1023, # (X=89674.047 Y=71610.008 Z=9482.095)
    "swamp_scraps_3" : base_id + 1024, # (X=91637.156 Y=73345.672 Z=9492.019)
    "swamp_scraps_4" : base_id + 1025, # (X=94601.117 Y=75064.117 Z=9567.464)
    "swamp_scraps_5" : base_id + 1026, # (X=95536.641 Y=72622.969 Z=9512.531)
    "swamp_scraps_6" : base_id + 1027, # (X=96419.922 Y=65508.676 Z=9838.949)
    "swamp_scraps_7" : base_id + 1028, # (X=98158.680 Y=63191.629 Z=10477.084)
    "swamp_scraps_8" : base_id + 1029, # (X=93421.820 Y=59200.461 Z=9545.312)
    "swamp_scraps_9" : base_id + 1030, # (X=92951.648 Y=56453.527 Z=9560.638)
    "swamp_scraps_10" : base_id + 1031, # (X=96943.297 Y=58754.043 Z=10728.124)
    "swamp_scraps_11" : base_id + 1032, # (X=95000.617 Y=53070.859 Z=10258.078)
    "swamp_scraps_12" : base_id + 1033, # (X=91390.703 Y=53628.707 Z=9498.378)
    "swamp_scraps_13" : base_id + 1034, # (X=87628.742 Y=51614.957 Z=9487.013)
    "swamp_scraps_14" : base_id + 1035, # (X=89785.992 Y=48603.844 Z=9573.859)
    "swamp_scraps_15" : base_id + 1036, # (X=89925.383 Y=46288.707 Z=9499.904)
    "swamp_scraps_16" : base_id + 1037, # (X=90848.938 Y=43133.535 Z=9729.535)
    "swamp_scraps_17" : base_id + 1038, # (X=87382.383 Y=42475.191 Z=9509.929)
    "swamp_scraps_18" : base_id + 1039, # (X=87481.820 Y=39316.820 Z=9757.511)
    "swamp_scraps_19" : base_id + 1040, # (X=86039.180 Y=37135.004 Z=9826.263)
    "swamp_scraps_20" : base_id + 1041, # (X=81798.609 Y=36766.922 Z=9479.318)
    "swamp_scraps_21" : base_id + 1042, # (X=79254.055 Y=40120.293 Z=9879.539)
    "swamp_scraps_22" : base_id + 1043, # (X=82251.773 Y=42454.027 Z=9482.057)
    "swamp_scraps_23" : base_id + 1044, # (X=84903.977 Y=48323.543 Z=9503.382)
    "swamp_scraps_24" : base_id + 1045, # (X=84238.609 Y=51239.547 Z=9529.745)
    "swamp_scraps_25" : base_id + 1046, # (X=84439.063 Y=53501.563 Z=9491.291)
    "swamp_scraps_26" : base_id + 1047, # (X=83025.086 Y=53275.348 Z=9694.177)
    "swamp_scraps_27" : base_id + 1048, # (X=79827.055 Y=54791.504 Z=10121.452)
    "swamp_scraps_28" : base_id + 1049, # (X=82266.461 Y=58126.316 Z=9660.493)
    "swamp_scraps_29" : base_id + 1050, # (X=75911.297 Y=65155.836 Z=10660.832)
    "swamp_scraps_30" : base_id + 1051, # (X=81171.641 Y=66836.125 Z=9673.756)
    "swamp_scraps_31" : base_id + 1052, # (X=95254.992 Y=40910.563 Z=10503.727)
    "swamp_scraps_32" : base_id + 1053 # (X=93992.992 Y=50773.484 Z=10238.064)
}

loc_lizbeth_murkwater_mission = {
    "swamp_shack_scraps_1" : base_id + 1054, # (X=87685.797 Y=69754.008 Z=9629.617)
    "swamp_shack_scraps_2" : base_id + 1055, # (X=87308.883 Y=69096.789 Z=9624.543)
    "swamp_isle_scraps_1" : base_id + 1056, # (X=88101.219 Y=64553.148 Z=9557.692)
    "swamp_isle_scraps_2" : base_id + 1057, # (X=87100.922 Y=63590.965 Z=9582.900)
    "swamp_isle_scraps_3" : base_id + 1058, # (X=86399.656 Y=64290.805 Z=9493.576)
    "swamp_isle_dead_fish" : base_id + 1059, # (X=87288.945 Y=64278.273 Z=9550.320)
    "swamp_lizbeth_murkwater_mission_end" : base_id + 1060
}

loc_daryl_mission = {
    "junkyard_daryl_scraps_1" : base_id + 1061, # (X=94184.391 Y=89760.258 Z=9331.188)
    "junkyard_daryl_scraps_2" : base_id + 1062, # (X=91919.469 Y=89681.602 Z=9407.639)
    "junkyard_daryl_scraps_3" : base_id + 1063, # (X=91696.078 Y=90453.563 Z=9480.997)
    "junkyard_daryl_scraps_4" : base_id + 1064, # (X=92453.719 Y=91142.531 Z=9398.951)
    "junkyard_daryl_scraps_5" : base_id + 1065, # (X=88645.453 Y=90374.930 Z=9507.291)
    "junkyard_daryl_scraps_6" : base_id + 1066, # (X=88461.953 Y=92077.531 Z=9712.173)
    "junkyard_daryl_scraps_7" : base_id + 1067, # (X=91521.555 Y=93773.641 Z=9421.457)
    "junkyard_daryl_scraps_8" : base_id + 1068, # (X=94741.484 Y=92565.938 Z=9221.093)
    "junkyard_daryl_scraps_9" : base_id + 1069, # (X=95256.008 Y=91356.789 Z=9251.082)
    "junkyard_daryl_scraps_10" : base_id + 1070, # (X=94289.664 Y=89951.477 Z=9367.076)
    "junkyard_daryl_mission_start" : base_id + 1071,
    "junkyard_daryl_ancient_tablet" : base_id + 1072, # (X=90715.367 Y=92168.563 Z=9402.729)
    "junkyard_daryl_mission_end" : base_id + 1073
}

loc_south_house = {
    "south_house_scraps_1" : base_id + 1074, # (X=85865.969 Y=103869.656 Z=9453.063)
    "south_house_scraps_2" : base_id + 1075, # (X=84403.742 Y=107229.039 Z=9067.245)
    "south_house_scraps_3" : base_id + 1076, # (X=83389.789 Y=108817.992 Z=8752.255)
    "south_house_scraps_4" : base_id + 1077, # (X=82413.547 Y=109697.477 Z=8637.677)
    "south_house_scraps_5" : base_id + 1078, # (X=83000.359 Y=110323.664 Z=8560.229)
    "south_house_scraps_6" : base_id + 1079, # (X=82072.625 Y=110482.664 Z=8682.441)
    "south_house_scraps_7" : base_id + 1080, # (X=81970.766 Y=111082.117 Z=8647.703)
    "south_house_scraps_8" : base_id + 1081, # (X=80915.375 Y=108689.758 Z=8377.754)
    "south_house_scraps_9" : base_id + 1082, # (X=81762.180 Y=111371.023 Z=7876.312)
    "south_house_scraps_10" : base_id + 1083, # (X=80663.336 Y=113306.695 Z=7226.475)
    "south_house_scraps_11" : base_id + 1084, # (X=80520.367 Y=113747.039 Z=7252.808)
    "south_house_scraps_12" : base_id + 1085, # (X=80830.273 Y=113871.383 Z=7201.687)
    "south_house_chest_scraps_1" : base_id + 1086, # (X=82079.922 Y=110808.602 Z=8739.324)
    "south_house_chest_scraps_2" : base_id + 1087, # (X=82102.664 Y=110813.664 Z=8726.308)
    "south_house_chest_scraps_3" : base_id + 1088, # (X=82091.547 Y=110810.906 Z=8721.354) Existing match 1
    "south_house_chest_scraps_4" : base_id + 1089, # (X=82091.516 Y=110810.898 Z=8701.793) Existing match 3
    "south_house_chest_scraps_5" : base_id + 1090 # (X=82102.664 Y=110813.625 Z=8688.776)
}

loc_helen_mission = {
    "junkyard_helen_mission_start" : base_id + 1091,
    "junkyard_helen_scraps_1" : base_id + 1092, # (X=98303.992 Y=84476.016 Z=9376.540)
    "junkyard_helen_scraps_2" : base_id + 1093, # (X=98174.680 Y=84067.383 Z=9249.197)
    "junkyard_helen_scraps_3" : base_id + 1094, # (X=97948.977 Y=83354.656 Z=9339.430)
    "junkyard_helen_scraps_4" : base_id + 1095, # (X=98208.391 Y=83088.047 Z=9273.632)
    "junkyard_helen_scraps_5" : base_id + 1096, # (X=97757.773 Y=82995.656 Z=9298.597)
    "junkyard_helen_scraps_6" : base_id + 1097, # (X=98776.102 Y=80881.133 Z=9286.782)
    "junkyard_helen_scraps_7" : base_id + 1098, # (X=99198.508 Y=82057.820 Z=9248.227)
    "junkyard_helen_scraps_8" : base_id + 1099 # (X=99208.617 Y=84383.125 Z=9257.880)
}

loc_sgt_flint_mission = {
    "base_sgt_flint_mission_end" : base_id + 1100,
    "base_sgt_flint_scraps_1" : base_id + 1101, # (X=105743.531 Y=83017.492 Z=9423.290)
    "base_sgt_flint_scraps_2" : base_id + 1102, # (X=108495.805 Y=81616.992 Z=9139.340)
    "base_sgt_flint_scraps_3" : base_id + 1103, # (X=108709.219 Y=85981.016 Z=9650.472)
    "base_sgt_flint_scraps_4" : base_id + 1104, # (X=112004.195 Y=83811.313 Z=8887.996)
    "base_sgt_flint_scraps_5" : base_id + 1105, # (X=110904.867 Y=82024.781 Z=9581.007)
    "base_sgt_flint_scraps_6" : base_id + 1106, # (X=112458.563 Y=81967.945 Z=9850.968)
    "base_sgt_flint_scraps_7" : base_id + 1107, # (X=112541.695 Y=81345.875 Z=9896.940)
    "base_sgt_flint_scraps_8" : base_id + 1108, # (X=111943.391 Y=79970.016 Z=10025.820)
    "base_sgt_flint_scraps_9" : base_id + 1109, # (X=112074.063 Y=83533.398 Z=9008.831)
    "base_sgt_flint_scraps_10" : base_id + 1110, # (X=110738.523 Y=85389.852 Z=9082.626)
    "base_sgt_flint_scraps_11" : base_id + 1111, # (X=112962.594 Y=85872.922 Z=8638.805)
    "base_sgt_flint_scraps_12" : base_id + 1112, # (X=116230.563 Y=84357.602 Z=8580.226)
    "base_sgt_flint_paint_can_orange" : base_id + 1113 # (X=111916.102 Y=83066.195 Z=9094.554)
}

loc_south_mine_outside = {
    "south_mine_outside_scraps_1" : base_id + 1114, # (X=114794.375 Y=57211.855 Z=8523.348)
    "south_mine_outside_scraps_2" : base_id + 1115, # (X=112523.438 Y=57693.836 Z=8639.382)
    "south_mine_outside_scraps_3" : base_id + 1116, # (X=112348.586 Y=59174.289 Z=8945.143)
    "south_mine_outside_scraps_4" : base_id + 1117, # (X=110989.156 Y=57840.090 Z=8700.936)
    "south_mine_outside_scraps_5" : base_id + 1118, # (X=110487.281 Y=54528.535 Z=8589.910)
    "south_mine_outside_scraps_6" : base_id + 1119, # (X=113727.297 Y=54791.703 Z=8424.460)
    "south_mine_outside_scraps_7" : base_id + 1120 # (X=113965.211 Y=53289.539 Z=8402.346)
}

loc_south_mine_inside = {
    "south_mine_inside_scraps_1" : base_id + 1121, # (X=108659.945 Y=58712.691 Z=8763.015)
    "south_mine_inside_scraps_2" : base_id + 1122, # (X=104954.602 Y=61540.488 Z=7876.374)
    "south_mine_inside_scraps_3" : base_id + 1123, # (X=104436.758 Y=64091.211 Z=7872.767)
    "south_mine_inside_scraps_4" : base_id + 1124, # (X=101356.625 Y=66110.906 Z=8034.738)
    "south_mine_inside_scraps_5" : base_id + 1125, # (X=96888.820 Y=64458.559 Z=7917.468)
    "south_mine_inside_scraps_6" : base_id + 1126, # (X=95863.180 Y=63252.902 Z=7847.054)
    "south_mine_inside_scraps_7" : base_id + 1127, # (X=97337.219 Y=62921.438 Z=7884.393)
    "south_mine_inside_scraps_8" : base_id + 1128, # (X=96689.203 Y=61880.895 Z=7806.810)
    "south_mine_inside_scraps_9" : base_id + 1129, # (X=98403.227 Y=62812.531 Z=7880.947)
    "south_mine_inside_egg_green" : base_id + 1130, # (X=96753.219 Y=62909.504 Z=8030.018) Existing match 4
    "south_mine_inside_paint_can_green" : base_id + 1131 # (X=108293.281 Y=64192.094 Z=7872.770) Existing match 5
}

loc_theodore_mission = {
    "station_paint_can_white" : base_id + 1132, # (X=34554.141 Y=-7395.408 Z=11897.556) Existing match 5
    "station_theodore_scraps_1" : base_id + 1133, # (X=37710.504 Y=-6462.562 Z=11356.691)
    "station_theodore_scraps_2" : base_id + 1134, # (X=37034.340 Y=-4923.256 Z=11348.328)
    "station_theodore_scraps_3" : base_id + 1135, # (X=36689.164 Y=-3727.466 Z=11353.597)
    "station_theodore_scraps_4" : base_id + 1136, # (X=37207.629 Y=-3393.977 Z=11379.110)
    "station_theodore_scraps_5" : base_id + 1137, # (X=37988.219 Y=-3365.906 Z=11350.225)
    "station_theodore_scraps_6" : base_id + 1138, # (X=36956.242 Y=-2746.948 Z=11353.506)
    "station_theodore_scraps_7" : base_id + 1139, # (X=36638.492 Y=-6410.017 Z=11353.546)
    "station_theodore_scraps_8" : base_id + 1140, # (X=35931.168 Y=-7558.021 Z=11899.232)
    "station_theodore_scraps_9" : base_id + 1141, # (X=35636.855 Y=-7628.500 Z=11903.627)
    "station_theodore_scraps_10" : base_id + 1142, # (X=34894.152 Y=-7537.087 Z=11903.627)
    "station_theodore_scraps_11" : base_id + 1143, # (X=33505.609 Y=-7742.843 Z=11898.971)
    "station_theodore_scraps_12" : base_id + 1144, # (X=37394.004 Y=-8395.084 Z=11389.296)
    "station_theodore_scraps_13" : base_id + 1145, # (X=36040.695 Y=-8068.016 Z=11456.609)
    "station_theodore_scraps_14" : base_id + 1146, # (X=35360.320 Y=-8441.443 Z=11457.823)
    "station_theodore_scraps_15" : base_id + 1147, # (X=36311.324 Y=-9563.938 Z=11468.039)
    "station_theodore_scraps_16" : base_id + 1148, # (X=33335.656 Y=-13872.785 Z=11189.906)
    "station_theodore_scraps_17" : base_id + 1149, # (X=33129.984 Y=-14073.978 Z=11189.906)
    "station_theodore_scraps_18" : base_id + 1150, # (X=33587.488 Y=-7828.651 Z=11529.446)
    "station_theodore_scraps_19" : base_id + 1151, # (X=34007.254 Y=-7749.381 Z=11533.760)
    "station_theodore_scraps_20" : base_id + 1152, # (X=31457.752 Y=-7120.744 Z=11421.197)
    "station_theodore_mission_end" : base_id + 1153
}

loc_canyon_theodore = {
    "canyon_scraps_1" : base_id + 1154, # (X=29432.162 Y=-3164.300 Z=11540.294)
    "canyon_scraps_2" : base_id + 1155, # (X=26331.086 Y=3036.740 Z=11701.688)
    "canyon_scraps_3" : base_id + 1156, # (X=22688.129 Y=3906.730 Z=12249.182)
    "canyon_scraps_4" : base_id + 1157, # (X=20546.193 Y=4371.471 Z=12128.874)
    "canyon_scraps_5" : base_id + 1158, # (X=20006.584 Y=4928.478 Z=12174.837)
    "canyon_scraps_6" : base_id + 1159, # (X=19251.633 Y=3798.014 Z=12170.390)
    "canyon_scraps_7" : base_id + 1160, # (X=18302.678 Y=7323.849 Z=12595.085)
    "canyon_scraps_8" : base_id + 1161, # (X=19019.563 Y=8172.146 Z=12640.462)
    "canyon_scraps_9" : base_id + 1162, # (X=18001.689 Y=11138.320 Z=13035.360)
    "canyon_scraps_10" : base_id + 1163, # (X=16381.525 Y=7191.394 Z=13682.453)
    "canyon_scraps_11" : base_id + 1164, # (X=18294.928 Y=7870.372 Z=14350.015)
    "canyon_scraps_12" : base_id + 1165, # (X=20730.520 Y=8032.158 Z=14439.826)
    "canyon_scraps_13" : base_id + 1166, # (X=24752.658 Y=7959.624 Z=14363.087)
    "canyon_scraps_14" : base_id + 1167, # (X=20181.992 Y=13816.017 Z=14897.407)
    "canyon_scraps_15" : base_id + 1168, # (X=23172.160 Y=2842.120 Z=12954.566)
    "canyon_scraps_16" : base_id + 1169, # (X=22307.621 Y=-1180.840 Z=12451.548)
    "canyon_scraps_17" : base_id + 1170, # (X=28473.596 Y=6741.842 Z=13314.166)
    "canyon_theodore_blue_box" : base_id + 1171 # (X=20338.525 Y=4989.111 Z=12323.649)
}

loc_watchtower = {
    "watchtower_scraps_1" : base_id + 1172, # (X=32760.389 Y=-28814.084 Z=10997.447)
    "watchtower_scraps_2" : base_id + 1173, # (X=32801.668 Y=-31660.041 Z=10643.390)
    "watchtower_scraps_3" : base_id + 1174, # (X=31018.063 Y=-33375.313 Z=11100.126)
    "watchtower_scraps_4" : base_id + 1175, # (X=33308.215 Y=-35928.578 Z=10614.347)
    "watchtower_scraps_5" : base_id + 1176, # (X=34304.262 Y=-33446.063 Z=10674.936)
    "watchtower_scraps_6" : base_id + 1177, # (X=32869.453 Y=-33184.094 Z=10612.040)
    "watchtower_scraps_7" : base_id + 1178, # (X=33210.707 Y=-32097.611 Z=11211.031)
    "watchtower_scraps_8" : base_id + 1179, # (X=33246.262 Y=-32046.697 Z=11851.025)
    "watchtower_scraps_9" : base_id + 1180, # (X=33553.156 Y=-31810.645 Z=11849.521)
    "watchtower_scraps_10" : base_id + 1181, # (X=36151.621 Y=-31791.633 Z=11093.785)
    "watchtower_paint_can_pink" : base_id + 1182 # (X=33069.133 Y=-32168.045 Z=11859.582) Existing match 5
}

loc_boulder_field = {
    "boulder_field_page_drawing_1" : base_id + 1183, # (X=46232.703 Y=-37052.875 Z=9531.116)
    "boulder_field_page_drawing_2" : base_id + 1184, # (X=51854.980 Y=-31332.070 Z=9804.927)
    "boulder_field_page_drawing_3" : base_id + 1185, # (X=47595.750 Y=-29931.740 Z=9308.014)
    "boulder_field_page_drawing_4" : base_id + 1186, # (X=43819.680 Y=-30378.770 Z=9706.599)
    "boulder_field_page_drawing_5" : base_id + 1187, # (X=47494.746 Y=-20884.781 Z=9812.398)
    "boulder_field_page_drawing_6" : base_id + 1188, # (X=43725.148 Y=-21952.570 Z=9744.351)
    "boulder_field_page_drawing_7" : base_id + 1189, # (X=44752.465 Y=-16362.510 Z=10147.004)
    "boulder_field_page_drawing_8" : base_id + 1190, # (X=50496.270 Y=-26090.533 Z=9835.365)
    "boulder_field_scraps_1" : base_id + 1191, # (X=41385.406 Y=-32281.871 Z=10240.781)
    "boulder_field_scraps_2" : base_id + 1192, # (X=46654.969 Y=-38859.254 Z=9920.861)
    "boulder_field_scraps_3" : base_id + 1193, # (X=44765.836 Y=-41675.559 Z=9938.179)
    "boulder_field_scraps_4" : base_id + 1194, # (X=50088.270 Y=-30669.107 Z=9267.371)
    "boulder_field_scraps_5" : base_id + 1195, # (X=48014.609 Y=-28971.115 Z=9199.659)
    "boulder_field_scraps_6" : base_id + 1196, # (X=50190.266 Y=-26243.977 Z=9648.289)
    "boulder_field_scraps_7" : base_id + 1197, # (X=47802.246 Y=-22594.684 Z=9631.879)
    "boulder_field_scraps_8" : base_id + 1198, # (X=44345.996 Y=-23408.535 Z=9659.643)
    "boulder_field_scraps_9" : base_id + 1199, # (X=41620.590 Y=-22982.641 Z=9720.177)
    "boulder_field_scraps_10" : base_id + 1200, # (X=52003.172 Y=-19163.049 Z=9925.105)
    "boulder_field_scraps_11" : base_id + 1201, # (X=51422.176 Y=-22319.322 Z=10663.813)
    "boulder_field_scraps_12" : base_id + 1202, # (X=43527.176 Y=-17952.570 Z=10812.458)
    "boulder_field_scraps_13" : base_id + 1203, # (X=45241.871 Y=-15847.636 Z=9952.198)
    "boulder_field_scraps_14" : base_id + 1204, # (X=46238.027 Y=-18407.420 Z=10199.825)
    "boulder_field_scraps_15" : base_id + 1205, # (X=49835.617 Y=-17379.959 Z=9810.836)
    "boulder_field_scraps_16" : base_id + 1206, # (X=45144.594 Y=-33817.090 Z=10136.658)
    "boulder_field_scraps_17" : base_id + 1207, # (X=44336.184 Y=-37162.367 Z=9789.548)
    "boulder_field_scraps_18" : base_id + 1208 # (X=44490.160 Y=-26442.754 Z=9974.022)
}

loc_house_sasha_mission = {
    "house_sasha_mission_end" : base_id + 1209,
    "house_sasha_scraps_1" : base_id + 1210, # (X=42900.188 Y=-43760.617 Z=9900.531)
    "house_sasha_scraps_2" : base_id + 1211, # (X=43608.078 Y=-44642.434 Z=9922.888)
    "house_sasha_scraps_3" : base_id + 1212, # (X=43992.387 Y=-44259.336 Z=9877.623)
    "house_sasha_scraps_4" : base_id + 1213, # (X=43340.012 Y=-45362.617 Z=9882.796)
    "house_sasha_scraps_5" : base_id + 1214, # (X=45105.383 Y=-45980.879 Z=9854.796)
    "house_sasha_scraps_6" : base_id + 1215 # (X=45888.406 Y=-46050.246 Z=9555.326)
}

loc_house_santiago = {
    "house_santiago_scraps_1" : base_id + 1216, # (X=37271.445 Y=-46075.598 Z=10648.827)
    "house_santiago_scraps_2" : base_id + 1217, # (X=38330.512 Y=-47184.668 Z=10387.618)
    "house_santiago_scraps_3" : base_id + 1218, # (X=35720.422 Y=-49536.328 Z=10098.503)
    "house_santiago_scraps_4" : base_id + 1219, # (X=35466.285 Y=-50363.078 Z=10098.504)
    "house_santiago_scraps_5" : base_id + 1220, # (X=34274.289 Y=-49947.578 Z=10098.501)
    "house_santiago_scraps_6" : base_id + 1221, # (X=35584.359 Y=-48195.172 Z=10323.833)
    "house_santiago_scraps_7" : base_id + 1222, # (X=35019.766 Y=-49904.113 Z=10124.169)
    "house_santiago_scraps_8" : base_id + 1223, # (X=35527.711 Y=-49614.801 Z=10124.016)
    "house_santiago_scraps_9" : base_id + 1224, # (X=34471.707 Y=-49497.000 Z=10199.790)
    "house_santiago_scraps_10" : base_id + 1225, # (X=37920.277 Y=-51867.754 Z=9847.511)
    "house_santiago_journal" : base_id + 1226 # (X=34690.777 Y=-49788.359 Z=10214.353)
}

loc_port_santiago_mission = {
    "port_paint_can_gray" : base_id + 1227, # (X=74641.648 Y=-11320.948 Z=7551.767)
    "port_scraps_1" : base_id + 1228, # (X=67315.281 Y=-13828.055 Z=10101.339)
    "port_scraps_2" : base_id + 1229, # (X=67679.508 Y=-14127.952 Z=10061.037)
    "port_scraps_3" : base_id + 1230, # (X=67062.219 Y=-15626.003 Z=10065.956)
    "port_scraps_4" : base_id + 1231, # (X=66140.914 Y=-16079.730 Z=10092.268)
    "port_scraps_5" : base_id + 1232, # (X=66824.719 Y=-14729.157 Z=10125.234)
    "port_scraps_6" : base_id + 1233, # (X=69777.258 Y=-8371.526 Z=9391.735)
    "port_scraps_7" : base_id + 1234, # (X=70339.695 Y=-11066.703 Z=8912.465)
    "port_scraps_8" : base_id + 1235, # (X=72729.508 Y=-7048.998 Z=8245.522)
    "port_scraps_9" : base_id + 1236, # (X=75896.070 Y=-8705.214 Z=7514.992)
    "port_scraps_10" : base_id + 1237, # (X=74264.211 Y=-10553.446 Z=7520.141)
    "port_scraps_11" : base_id + 1238, # (X=74328.117 Y=-11423.852 Z=7511.827)
    "port_scraps_12" : base_id + 1239, # (X=76753.164 Y=-10744.933 Z=7437.174)
    "port_scraps_13" : base_id + 1240, # (X=77330.414 Y=-11640.151 Z=7189.003)
    "port_scraps_14" : base_id + 1241, # (X=76403.516 Y=-12484.995 Z=7440.368)
    "port_scraps_15" : base_id + 1242, # (X=78651.977 Y=-12233.159 Z=7439.514)
    "port_scraps_16" : base_id + 1243, # (X=80336.297 Y=-12276.590 Z=7436.639)
    "port_scraps_17" : base_id + 1244, # (X=79845.086 Y=-13410.705 Z=7440.597)
    "port_santiago_mission_end" : base_id + 1245
}

loc_trench_house = {
    "trench_house_scraps_1" : base_id + 1246, # (X=76340.328 Y=-42886.191 Z=9567.521)
    "trench_house_scraps_2" : base_id + 1247, # (X=76013.594 Y=-44140.141 Z=9413.147)
    "trench_house_scraps_3" : base_id + 1248, # (X=74408.320 Y=-45424.000 Z=9446.966)
    "trench_house_scraps_4" : base_id + 1249, # (X=75196.344 Y=-48321.504 Z=9453.302)
    "trench_house_scraps_5" : base_id + 1250, # (X=73467.273 Y=-48995.738 Z=9355.070)
    "trench_house_scraps_6" : base_id + 1251, # (X=76418.469 Y=-53239.539 Z=9276.892)
    "trench_house_scraps_7" : base_id + 1252, # (X=70719.875 Y=-54290.117 Z=9357.084)
    "trench_house_scraps_8" : base_id + 1253, # (X=70075.938 Y=-53041.973 Z=9675.481)
    "trench_house_scraps_9" : base_id + 1254, # (X=74745.711 Y=-52304.027 Z=9073.130)
    "trench_house_scraps_10" : base_id + 1255, # (X=74519.750 Y=-53603.063 Z=9078.054)
    "trench_house_scraps_11" : base_id + 1256, # (X=73747.492 Y=-52589.906 Z=9104.748)
    "trench_house_scraps_12" : base_id + 1257, # (X=74333.125 Y=-52847.961 Z=9124.773)
    "trench_house_scraps_13" : base_id + 1258, # (X=74062.195 Y=-52663.043 Z=9122.827)
    "trench_house_scraps_14" : base_id + 1259, # (X=74820.492 Y=-51350.051 Z=7956.387)
    "trench_house_scraps_15" : base_id + 1260, # (X=75286.289 Y=-51164.098 Z=7957.081)
    "trench_house_scraps_16" : base_id + 1261, # (X=68413.258 Y=-56872.816 Z=9349.443)
    "trench_house_scraps_17" : base_id + 1262, # (X=67281.281 Y=-59201.371 Z=9254.457)
    "trench_house_scraps_18" : base_id + 1263, # (X=69064.219 Y=-48796.352 Z=9770.164)
    "trench_house_chest_scraps_1" : base_id + 1264, # (X=75042.141 Y=-50830.891 Z=8005.156)
    "trench_house_chest_scraps_2" : base_id + 1265, # (X=75066.516 Y=-50824.398 Z=7995.000)
    "trench_house_chest_scraps_3" : base_id + 1266, # (X=75072.789 Y=-50818.441 Z=7986.979)
    "trench_house_chest_scraps_4" : base_id + 1267, # (X=75038.656 Y=-50827.566 Z=7973.354)
    "trench_house_chest_scraps_5" : base_id + 1268, # (X=75060.406 Y=-50828.102 Z=7965.915)
    "trench_house_chest_scraps_6" : base_id + 1269 # (X=75056.648 Y=-50818.125 Z=7959.868)
}

loc_doll_woods = {
    "doll_woods_scraps_1" : base_id + 1270, # (X=60126.234 Y=-49668.906 Z=9970.880)
    "doll_woods_scraps_2" : base_id + 1271, # (X=59854.066 Y=-47313.121 Z=10376.684)
    "doll_woods_scraps_3" : base_id + 1272, # (X=59130.613 Y=-49597.789 Z=9930.675)
    "doll_woods_scraps_4" : base_id + 1273, # (X=59785.973 Y=-51269.684 Z=10180.019)
    "doll_woods_scraps_5" : base_id + 1274, # (X=58226.449 Y=-52660.801 Z=10576.626)
    "doll_woods_scraps_6" : base_id + 1275, # (X=56243.176 Y=-49097.793 Z=10869.889)
    "doll_woods_scraps_7" : base_id + 1276, # (X=59481.672 Y=-45288.137 Z=10897.672)
    "doll_woods_scraps_8" : base_id + 1277, # (X=63807.668 Y=-44674.734 Z=10337.434)
    "doll_woods_scraps_9" : base_id + 1278, # (X=68406.664 Y=-45721.813 Z=10021.356)
    "doll_woods_scraps_10" : base_id + 1279 # (X=62898.469 Y=-47565.703 Z=10744.431)
}

loc_lost_stairs = {
    "lost_stairs_scraps_1" : base_id + 1280, # (X=47087.617 Y=-53476.547 Z=9103.093)
    "lost_stairs_scraps_2" : base_id + 1281 # (X=47162.238 Y=-55318.094 Z=9127.096)
}

loc_east_house = {
    "east_house_scraps_1" : base_id + 1282, # (X=97507.664 Y=-53201.270 Z=9174.678)
    "east_house_scraps_2" : base_id + 1283, # (X=98511.242 Y=-53899.414 Z=9016.314)
    "east_house_scraps_3" : base_id + 1284, # (X=100688.102 Y=-54197.578 Z=8919.432)
    "east_house_scraps_4" : base_id + 1285, # (X=103149.773 Y=-54659.980 Z=9002.535)
    "east_house_scraps_5" : base_id + 1286, # (X=107458.172 Y=-55683.793 Z=9429.004)
    "east_house_scraps_6" : base_id + 1287, # (X=109034.164 Y=-54360.703 Z=9495.910)
    "east_house_scraps_7" : base_id + 1288, # (X=109245.148 Y=-55045.242 Z=9553.601)
    "east_house_scraps_8" : base_id + 1289, # (X=112556.445 Y=-55851.754 Z=10049.954)
    "east_house_scraps_9" : base_id + 1290, # (X=113131.469 Y=-56822.508 Z=10038.047)
    "east_house_scraps_10" : base_id + 1291, # (X=112279.828 Y=-56743.781 Z=10029.549)
    "east_house_scraps_11" : base_id + 1292, # (X=112445.508 Y=-56280.320 Z=10059.164)
    "east_house_scraps_12" : base_id + 1293, # (X=112562.211 Y=-56736.332 Z=10454.907)
    "east_house_scraps_13" : base_id + 1294, # (X=109313.320 Y=-58221.316 Z=9501.283)
    "east_house_scraps_14" : base_id + 1295, # (X=104077.805 Y=-55987.301 Z=9066.847)
    "east_house_chest_scraps_1" : base_id + 1296, # (X=112317.242 Y=-55820.805 Z=10497.336)
    "east_house_chest_scraps_2" : base_id + 1297, # (X=112326.086 Y=-55808.477 Z=10485.685)
    "east_house_chest_scraps_3" : base_id + 1298, # (X=112329.031 Y=-55828.438 Z=10478.107)
    "east_house_chest_scraps_4" : base_id + 1299, # (X=112315.922 Y=-55820.102 Z=10466.683)
    "east_house_chest_scraps_5" : base_id + 1300 # (X=112337.922 Y=-55821.848 Z=10456.924)
}

loc_explosive_training = {
    "explosive_training_timed_dynamite" : base_id + 1301, # (X=76476.609 Y=-65286.738 Z=8303.742)
    "explosive_training_scraps_1" : base_id + 1302, # (X=88925.570 Y=-63375.051 Z=8563.354)
    "explosive_training_scraps_2" : base_id + 1303, # (X=84234.016 Y=-64475.551 Z=8382.108)
    "explosive_training_scraps_3" : base_id + 1304, # (X=79349.438 Y=-64225.480 Z=8384.219)
    "explosive_training_scraps_4" : base_id + 1305, # (X=79831.070 Y=-65847.766 Z=8301.337)
    "explosive_training_scraps_5" : base_id + 1306, # (X=76526.500 Y=-65394.875 Z=8223.883)
    "explosive_training_scraps_6" : base_id + 1307, # (X=76237.977 Y=-67087.414 Z=8361.979)
    "explosive_training_scraps_7" : base_id + 1308, # (X=78857.672 Y=-67802.227 Z=8257.150)
    "explosive_training_scraps_8" : base_id + 1309, # (X=74878.570 Y=-62927.297 Z=8749.549)
    "explosive_training_scraps_9" : base_id + 1310, # (X=74542.641 Y=-61301.082 Z=9493.931)
    "explosive_training_scraps_10" : base_id + 1311, # (X=77020.859 Y=-62031.320 Z=8873.663)
    "explosive_training_scraps_11" : base_id + 1312, # (X=77552.094 Y=-61144.559 Z=8523.195)
    "explosive_training_scraps_12" : base_id + 1313, # (X=77670.227 Y=-62029.941 Z=8570.785)
    "explosive_training_box_of_rocket" : base_id + 1314 # (X=77330.086 Y=-61504.324 Z=8523.195)
}

loc_john_smith_mission = {
    "workshop_scraps_1" : base_id + 1315, # (X=93550.773 Y=-61901.797 Z=8828.551)
    "workshop_scraps_2" : base_id + 1316, # (X=93508.047 Y=-64009.910 Z=8783.468)
    "workshop_scraps_3" : base_id + 1317, # (X=92011.648 Y=-65572.281 Z=8736.709)
    "workshop_scraps_4" : base_id + 1318, # (X=92311.594 Y=-63045.211 Z=8749.977)
    "workshop_scraps_5" : base_id + 1319, # (X=91392.734 Y=-63527.629 Z=8709.268)
    "workshop_scraps_6" : base_id + 1320, # (X=92986.789 Y=-63012.047 Z=9235.383)
    "workshop_john_smith_mission_end" : base_id + 1321
}

loc_greg_mission = {
    "tower_greg_mission_start" : base_id + 1322,
    "tower_greg_scraps_1" : base_id + 1323, # (X=95448.250 Y=-67249.156 Z=8607.896)
    "tower_greg_scraps_2" : base_id + 1324, # (X=96339.242 Y=-66374.828 Z=8650.519)
    "tower_greg_scraps_3" : base_id + 1325, # (X=98540.711 Y=-67173.656 Z=8418.825)
    "tower_greg_scraps_4" : base_id + 1326, # (X=97276.414 Y=-68495.008 Z=8337.229)
    "tower_greg_scraps_5" : base_id + 1327, # (X=96470.820 Y=-66540.859 Z=8953.763)
    "tower_greg_scraps_6" : base_id + 1328 # (X=96141.555 Y=-67013.445 Z=9399.308)
}

loc_claire_mission = {
    "lighthouse_scraps_1": base_id + 1329,  # (X=100072.813 Y=-68645.688 Z=8150.313)
    "lighthouse_scraps_2" : base_id + 1330, # (X=105340.594 Y=-70828.602 Z=8436.780)
    "lighthouse_scraps_3" : base_id + 1331, # (X=103851.688 Y=-73396.625 Z=7973.290)
    "lighthouse_scraps_4" : base_id + 1332, # (X=107040.711 Y=-74021.555 Z=8303.216)
    "lighthouse_scraps_5" : base_id + 1333, # (X=110566.859 Y=-77435.961 Z=7642.565)
    "lighthouse_scraps_6" : base_id + 1334, # (X=111451.352 Y=-77351.117 Z=7633.413)
    "lighthouse_scraps_7" : base_id + 1335, # (X=113078.500 Y=-78618.281 Z=7180.793)
    "lighthouse_scraps_8" : base_id + 1336, # (X=113396.305 Y=-80315.383 Z=7184.260)
    "lighthouse_scraps_9" : base_id + 1337, # (X=114057.484 Y=-81517.836 Z=7245.034)
    "lighthouse_scraps_10" : base_id + 1338, # (X=110915.156 Y=-78376.609 Z=7676.131)
    "lighthouse_scraps_11" : base_id + 1339, # (X=109341.703 Y=-79014.469 Z=8075.679)
    "lighthouse_scraps_12" : base_id + 1340, # (X=107006.578 Y=-81377.711 Z=8821.629)
    "lighthouse_scraps_13" : base_id + 1341, # (X=109240.195 Y=-82951.375 Z=8194.619)
    "lighthouse_scraps_14" : base_id + 1342, # (X=106295.719 Y=-84190.578 Z=8581.896)
    "lighthouse_scraps_15" : base_id + 1343, # (X=104233.883 Y=-84663.328 Z=7806.311)
    "lighthouse_scraps_16" : base_id + 1344, # (X=103209.227 Y=-81564.047 Z=8140.578)
    "lighthouse_scraps_17" : base_id + 1345, # (X=104795.555 Y=-81344.758 Z=8775.158)
    "lighthouse_scraps_18" : base_id + 1346, # (X=100843.914 Y=-78038.539 Z=7197.542)
    "lighthouse_breaker_1" : base_id + 1347, # (X=110781.164 Y=-77296.813 Z=7757.248) Existing match 6
    "lighthouse_breaker_2" : base_id + 1348, # (X=110899.227 Y=-77239.031 Z=7757.134) Existing match 3
    "lighthouse_breaker_3" : base_id + 1349, # (X=110948.547 Y=-77253.336 Z=7757.134) Existing match 2
    "lighthouse_breaker_4" : base_id + 1350, # (X=111001.078 Y=-77205.047 Z=7757.134) Existing match 1
    "lighthouse_claire_mission_end" : base_id + 1351
}

loc_north_mine_outside = {
    "north_mine_outside_scraps_1" : base_id + 1352, # (X=-52376.746 Y=-101857.492 Z=10542.841)
    "north_mine_outside_scraps_2" : base_id + 1353, # (X=-53786.742 Y=-102067.789 Z=10858.948)
    "north_mine_outside_scraps_3" : base_id + 1354, # (X=-57502.777 Y=-105475.336 Z=10609.405)
    "north_mine_outside_scraps_4" : base_id + 1355, # (X=-58102.102 Y=-104007.906 Z=11146.535)
    "north_mine_outside_scraps_5" : base_id + 1356, # (X=-59474.840 Y=-105053.734 Z=11213.524)
    "north_mine_outside_scraps_6" : base_id + 1357, # (X=-55011.750 Y=-104936.359 Z=9935.366)
    "north_mine_outside_scraps_7" : base_id + 1358, # (X=-55594.863 Y=-107667.594 Z=9596.611)
    "north_mine_outside_scraps_8" : base_id + 1359, # (X=-56632.578 Y=-109503.406 Z=9280.788)
    "north_mine_outside_scraps_9" : base_id + 1360, # (X=-54645.418 Y=-110747.602 Z=9553.452)
    "north_mine_outside_scraps_10" : base_id + 1361, # (X=-51561.340 Y=-113574.813 Z=9414.959)
    "north_mine_outside_scraps_11" : base_id + 1362, # (X=-54072.105 Y=-112672.031 Z=10077.665)
    "north_mine_outside_scraps_12" : base_id + 1363, # (X=-58042.758 Y=-108748.656 Z=9693.470)
    "north_mine_outside_scraps_13" : base_id + 1364 # (X=-55717.227 Y=-110610.414 Z=9487.879)
}

loc_north_mine_inside = {
    "north_mine_inside_scraps_1" : base_id + 1365, # (X=-58987.199 Y=-103262.906 Z=9186.494)
    "north_mine_inside_scraps_2" : base_id + 1366, # (X=-58812.801 Y=-99259.570 Z=8847.714)
    "north_mine_inside_scraps_3" : base_id + 1367, # (X=-56634.379 Y=-99529.563 Z=8851.877)
    "north_mine_inside_scraps_4" : base_id + 1368, # (X=-55604.477 Y=-98342.906 Z=8842.766)
    "north_mine_inside_scraps_5" : base_id + 1369, # (X=-54824.535 Y=-98526.492 Z=8852.156)
    "north_mine_inside_scraps_6" : base_id + 1370, # (X=-54887.254 Y=-99047.141 Z=8849.855)
    "north_mine_inside_scraps_7" : base_id + 1371, # (X=-55610.020 Y=-101877.961 Z=9081.042)
    "north_mine_inside_scraps_8" : base_id + 1372, # (X=-56519.340 Y=-101375.008 Z=9001.270)
    "north_mine_inside_scraps_9" : base_id + 1373, # (X=-53329.922 Y=-99469.773 Z=8848.643)
    "north_mine_inside_scraps_10" : base_id + 1374, # (X=-52814.828 Y=-96286.969 Z=8851.372)
    "north_mine_inside_scraps_11" : base_id + 1375, # (X=-52605.957 Y=-96535.156 Z=8940.480)
    "north_mine_inside_scraps_12" : base_id + 1376, # (X=-53237.699 Y=-96609.461 Z=8846.201)
    "north_mine_inside_scraps_13" : base_id + 1377, # (X=-58543.488 Y=-95879.695 Z=8981.646)
    "north_mine_inside_blue_egg" : base_id + 1378, # (X=-53592.195 Y=-99177.500 Z=8975.387)
    "north_mine_inside_paint_can_blue" : base_id + 1379 # (X=-56133.391 Y=-101870.047 Z=9004.720) Existing match 5
}

loc_wood_bridge = {
    "wood_bridge_scraps_1" : base_id + 1380, # (X=-66790.141 Y=-110340.367 Z=10454.417)
    "wood_bridge_scraps_2" : base_id + 1381, # (X=-68364.586 Y=-111691.625 Z=10444.172)
    "wood_bridge_scraps_3" : base_id + 1382, # (X=-69013.555 Y=-112353.977 Z=10399.942)
    "wood_bridge_scraps_4" : base_id + 1383, # (X=-70398.797 Y=-112916.945 Z=10372.192)
    "wood_bridge_scraps_5" : base_id + 1384, # (X=-71336.172 Y=-106966.672 Z=8430.104)
    "wood_bridge_scraps_6" : base_id + 1385, # (X=-72776.086 Y=-107813.102 Z=8305.589)
    "wood_bridge_scraps_7" : base_id + 1386, # (X=-75224.648 Y=-108280.867 Z=7929.499)
    "wood_bridge_scraps_8" : base_id + 1387, # (X=-68112.172 Y=-105119.656 Z=9458.937)
    "wood_bridge_scraps_9" : base_id + 1388, # (X=-71847.625 Y=-103623.203 Z=10707.521)
    "wood_bridge_scraps_10" : base_id + 1389, # (X=-71812.219 Y=-107256.094 Z=10780.134)
    "wood_bridge_scraps_11" : base_id + 1390, # (X=-72011.570 Y=-109054.547 Z=10866.852)
    "wood_bridge_scraps_12" : base_id + 1391, # (X=-72862.430 Y=-106144.852 Z=10329.061)
    "wood_bridge_scraps_13" : base_id + 1392 # (X=-71843.117 Y=-107174.133 Z=10367.116)
}

loc_paul_mission = {
    "museum_scraps_1" : base_id + 1393, # (X=-69687.773 Y=-100002.406 Z=10806.339)
    "museum_scraps_2" : base_id + 1394, # (X=-68035.195 Y=-99480.672 Z=11049.731)
    "museum_scraps_3" : base_id + 1395, # (X=-66912.641 Y=-99976.750 Z=11064.357)
    "museum_scraps_4" : base_id + 1396, # (X=-64901.117 Y=-99624.953 Z=11176.359)
    "museum_scraps_5" : base_id + 1397, # (X=-66082.328 Y=-98105.555 Z=11089.308)
    "museum_scraps_6" : base_id + 1398, # (X=-67402.742 Y=-97735.133 Z=11153.927)
    "museum_scraps_7" : base_id + 1399, # (X=-66716.031 Y=-98282.508 Z=11195.624)
    "museum_scraps_8" : base_id + 1400, # (X=-66582.703 Y=-99092.461 Z=11630.082)
    "museum_scraps_9" : base_id + 1401, # (X=-66798.164 Y=-99550.266 Z=11547.321)
    "museum_scraps_10" : base_id + 1402, # (X=-66850.336 Y=-99682.844 Z=11543.618)
    "museum_scraps_11" : base_id + 1403, # (X=-60156.828 Y=-98516.953 Z=11811.422)
    "museum_scraps_12" : base_id + 1404, # (X=-61195.203 Y=-98262.422 Z=11779.118)
    "museum_paul_mission_start" : base_id + 1405,
    "museum_paul_mission_end" : base_id + 1406
}

loc_gertrude_mission = {
    "refuge_gertrude_mission_start" : base_id + 1407,
    "refuge_gertrude_scraps_1" : base_id + 1408, # (X=-72525.500 Y=-89333.734 Z=9820.663)
    "refuge_gertrude_scraps_2" : base_id + 1409, # (X=-74870.758 Y=-88576.641 Z=9836.814)
    "refuge_gertrude_scraps_3" : base_id + 1410, # (X=-76193.914 Y=-88038.836 Z=9818.776)
    "refuge_gertrude_scraps_4" : base_id + 1411, # (X=-74494.859 Y=-87609.969 Z=9837.866)
    "refuge_gertrude_scraps_5" : base_id + 1412 # (X=-74826.930 Y=-88402.039 Z=9929.854)
}

loc_west_beach = {
    "west_beach_chest_scraps_1" : base_id + 1413, # (X=-85934.047 Y=-89532.547 Z=7383.054)
    "west_beach_chest_scraps_2" : base_id + 1414, # (X=-85933.977 Y=-89532.977 Z=7369.364)
    "west_beach_chest_scraps_3" : base_id + 1415, # (X=-85951.000 Y=-89527.023 Z=7367.054)
    "west_beach_chest_scraps_4" : base_id + 1416, # (X=-85932.461 Y=-89533.148 Z=7354.001)
    "west_beach_chest_scraps_5" : base_id + 1417, # (X=-85950.930 Y=-89527.453 Z=7353.365)
    "west_beach_chest_scraps_6" : base_id + 1418, # (X=-85932.391 Y=-89533.578 Z=7340.312)
    "west_beach_scraps_1" : base_id + 1419, # (X=-84489.945 Y=-91235.977 Z=8360.803)
    "west_beach_scraps_2" : base_id + 1420, # (X=-84386.320 Y=-90391.789 Z=8376.434)
    "west_beach_scraps_3" : base_id + 1421, # (X=-84714.773 Y=-89876.992 Z=7707.064)
    "west_beach_scraps_4" : base_id + 1422, # (X=-85478.672 Y=-90648.414 Z=7708.377)
    "west_beach_scraps_5" : base_id + 1423, # (X=-86276.633 Y=-90674.289 Z=7532.364)
    "west_beach_scraps_6" : base_id + 1424, # (X=-84363.055 Y=-87497.938 Z=7582.647)
    "west_beach_scraps_7" : base_id + 1425, # (X=-86556.266 Y=-89748.484 Z=7297.274)
    "west_beach_scraps_8" : base_id + 1426 # (X=-83210.836 Y=-92551.953 Z=8460.213)
}

loc_church = {
    "church_paint_can_black" : base_id + 1427, # (X=-67628.172 Y=-83801.375 Z=9865.983)
    "church_scraps_1" : base_id + 1428, # (X=-64009.039 Y=-84252.156 Z=10258.335)
    "church_scraps_2" : base_id + 1429, # (X=-66870.719 Y=-85202.180 Z=9843.936)
    "church_scraps_3" : base_id + 1430, # (X=-68588.352 Y=-84041.867 Z=9790.541)
    "church_scraps_4" : base_id + 1431, # (X=-67595.797 Y=-82120.094 Z=9818.303)
    "church_scraps_5" : base_id + 1432, # (X=-67291.000 Y=-83324.836 Z=9774.942)
    "church_scraps_6" : base_id + 1433, # (X=-65849.070 Y=-80676.477 Z=9895.943)
    "church_scraps_7" : base_id + 1434, # (X=-65170.266 Y=-79155.227 Z=9904.275)
    "church_scraps_8" : base_id + 1435, # (X=-64837.563 Y=-80885.305 Z=9906.755)
    "church_scraps_9" : base_id + 1436, # (X=-68248.359 Y=-83578.008 Z=9807.300)
    "church_scraps_10" : base_id + 1437, # (X=-67086.102 Y=-84605.086 Z=9805.521)
    "church_scraps_11" : base_id + 1438, # (X=-67901.930 Y=-83477.625 Z=9812.613)
    "church_scraps_12" : base_id + 1439 # (X=-65834.344 Y=-84192.102 Z=9987.823)
}

loc_refuge_gale_mission = {
    "refuge_gale_mission_start" : base_id + 1440,
    "refuge_gale_scraps_1" : base_id + 1441, # (X=-74407.695 Y=-81781.250 Z=10120.775)
    "refuge_gale_scraps_2" : base_id + 1442, # (X=-73784.695 Y=-79414.359 Z=10128.285)
    "refuge_gale_scraps_3" : base_id + 1443, # (X=-73992.391 Y=-78600.094 Z=10162.495)
    "refuge_gale_scraps_4" : base_id + 1444, # (X=-71623.000 Y=-75998.023 Z=10275.477)
    "refuge_gale_scraps_5" : base_id + 1445 # (X=-72626.453 Y=-79391.070 Z=10211.037)
}

loc_caravan = {
    "caravan_scraps_1" : base_id + 1446, # (X=-52638.109 Y=-43924.395 Z=10579.809)
    "caravan_scraps_2" : base_id + 1447, # (X=-50203.695 Y=-42865.672 Z=10778.871)
    "caravan_scraps_3" : base_id + 1448, # (X=-48467.738 Y=-42018.488 Z=10818.758)
    "caravan_scraps_4" : base_id + 1449, # (X=-46325.219 Y=-41707.512 Z=11003.229)
    "caravan_scraps_5" : base_id + 1450, # (X=-44557.043 Y=-40652.930 Z=11076.221)
    "caravan_scraps_6" : base_id + 1451, # (X=-43380.664 Y=-38207.152 Z=11165.370)
    "caravan_scraps_7" : base_id + 1452, # (X=-42919.410 Y=-38797.738 Z=11265.633)
    "caravan_scraps_8" : base_id + 1453, # (X=-42787.523 Y=-38601.820 Z=11254.003)
    "caravan_scraps_9" : base_id + 1454, # (X=-42711.363 Y=-39141.523 Z=11173.905)
    "caravan_chest_scraps_1" : base_id + 1455, # (X=-42910.668 Y=-38297.309 Z=11233.402)
    "caravan_chest_scraps_2" : base_id + 1456, # (X=-42904.344 Y=-38307.332 Z=11219.678)
    "caravan_chest_scraps_3" : base_id + 1457, # (X=-42904.965 Y=-38280.383 Z=11208.191)
    "caravan_chest_scraps_4" : base_id + 1458, # (X=-42911.680 Y=-38315.254 Z=11204.225)
    "caravan_chest_scraps_5" : base_id + 1459 # (X=-42905.090 Y=-38279.828 Z=11192.738)
}

loc_trailer_house = {
    "trailer_house_scraps_1" : base_id + 1460, # (X=-50702.449 Y=-38850.020 Z=10810.316)
    "trailer_house_scraps_2" : base_id + 1461, # (X=-51365.684 Y=-38502.379 Z=10875.761)
    "trailer_house_scraps_3" : base_id + 1462, # (X=-52397.570 Y=-37530.145 Z=10873.624)
    "trailer_house_scraps_4" : base_id + 1463, # (X=-50625.746 Y=-37916.758 Z=10886.909)
    "trailer_house_scraps_5" : base_id + 1464, # (X=-51201.051 Y=-37467.137 Z=10910.795)
    "trailer_house_scraps_6" : base_id + 1465 # (X=-51891.320 Y=-40549.492 Z=10675.211)
}

loc_ronny_mission = {
    "towers_ronny_scraps_1" : base_id + 1466, # (X=-24434.766 Y=-25708.373 Z=11200.865)
    "towers_ronny_scraps_2" : base_id + 1467, # (X=-20970.262 Y=-25678.754 Z=11731.241)
    "towers_ronny_scraps_3" : base_id + 1468, # (X=-19812.230 Y=-27768.301 Z=12051.623)
    "towers_ronny_scraps_4" : base_id + 1469, # (X=-19940.912 Y=-25411.576 Z=12035.366)
    "towers_ronny_scraps_5" : base_id + 1470, # (X=-18596.791 Y=-25100.035 Z=12290.350)
    "towers_ronny_scraps_6" : base_id + 1471, # (X=-23302.396 Y=-23270.324 Z=12036.164)
    "towers_ronny_scraps_7" : base_id + 1472, # (X=-22955.039 Y=-27576.859 Z=11211.258)
    "towers_ronny_scraps_8" : base_id + 1473, # (X=-21485.520 Y=-29634.893 Z=11787.103)
    "towers_ronny_scraps_9" : base_id + 1474, # (X=-23667.957 Y=-29825.240 Z=12035.269)
    "towers_ronny_scraps_10" : base_id + 1475, # (X=-25361.008 Y=-29794.301 Z=12026.073)
    "towers_ronny_scraps_11" : base_id + 1476, # (X=-26549.584 Y=-32768.133 Z=12289.732)
    "towers_ronny_scraps_12" : base_id + 1477, # (X=-27240.127 Y=-27404.748 Z=12027.208)
    "towers_ronny_scraps_13" : base_id + 1478, # (X=-23231.639 Y=-27799.158 Z=11829.792)
    "towers_ronny_scraps_14" : base_id + 1479, # (X=-22949.568 Y=-26146.012 Z=11702.730)
    "towers_ronny_scraps_15" : base_id + 1480, # (X=-19726.715 Y=-32464.682 Z=12118.678)
    "towers_ronny_scraps_16" : base_id + 1481, # (X=-23495.104 Y=-27644.689 Z=11872.844)
    "towers_ronny_scraps_17" : base_id + 1482, # (X=-23512.971 Y=-27493.051 Z=12218.543)
    "towers_ronny_scraps_18" : base_id + 1483, # (X=-22731.439 Y=-26331.393 Z=12102.758)
    "towers_ronny_scraps_19" : base_id + 1484, # (X=-22599.641 Y=-26454.590 Z=11752.040)
    "towers_ronny_scraps_20" : base_id + 1485, # (X=-22589.721 Y=-26397.414 Z=12571.282)
    "towers_ronny_scraps_21" : base_id + 1486, # (X=-22163.268 Y=-26775.938 Z=13107.048)
    "towers_ronny_scraps_22" : base_id + 1487, # (X=-21996.184 Y=-26754.393 Z=13105.997)
    "towers_ronny_scraps_23" : base_id + 1488, # (X=-24068.221 Y=-27874.443 Z=12819.666)
    "towers_ronny_scraps_24" : base_id + 1489, # (X=-23525.330 Y=-27770.035 Z=12612.871)
    "towers_ronny_scraps_25" : base_id + 1490, # (X=-23472.215 Y=-27617.404 Z=13213.256)
    "towers_ronny_scraps_26" : base_id + 1491, # (X=-23981.588 Y=-27984.385 Z=13219.854)
    "towers_ronny_scraps_27" : base_id + 1492, # (X=-18696.230 Y=-34511.277 Z=12704.238)
    "towers_ronny_paint_can_lime" : base_id + 1493, # (X=-22288.555 Y=-26022.281 Z=11835.892) Existing match 5
    "towers_ronny_employment_contracts" : base_id + 1494, # (X=-24081.414 Y=-27637.459 Z=13679.163)
    "towers_ronny_mission_end" : base_id + 1495
}

loc_north_beach = {
    "north_beach_chest_scraps_1" : base_id + 1496, # (X=-74444.648 Y=-130627.672 Z=8793.757)
    "north_beach_chest_scraps_2" : base_id + 1497, # (X=-74426.539 Y=-130626.547 Z=8781.948)
    "north_beach_chest_scraps_3" : base_id + 1498, # (X=-74448.852 Y=-130632.367 Z=8772.555)
    "north_beach_chest_scraps_4" : base_id + 1499, # (X=-74425.523 Y=-130622.875 Z=8755.526)
    "north_beach_scraps_1" : base_id + 1500, # (X=-75003.078 Y=-131084.016 Z=8729.731)
    "north_beach_scraps_2" : base_id + 1501, # (X=-75477.758 Y=-129413.750 Z=9082.617)
    "north_beach_scraps_3" : base_id + 1502, # (X=-75608.453 Y=-130483.430 Z=8909.659)
    "north_beach_scraps_4" : base_id + 1503, # (X=-74143.469 Y=-131117.953 Z=8752.130)
    "north_beach_scraps_5" : base_id + 1504, # (X=-80847.078 Y=-135628.719 Z=7915.444)
    "north_beach_scraps_6" : base_id + 1505, # (X=-84044.789 Y=-137591.000 Z=7359.172)
    "north_beach_scraps_7" : base_id + 1506, # (X=-83992.836 Y=-132933.531 Z=7941.225)
    "north_beach_scraps_8" : base_id + 1507, # (X=-87355.734 Y=-134216.438 Z=7237.310)
    "north_beach_scraps_9" : base_id + 1508, # (X=-89213.844 Y=-134625.922 Z=7185.133)
    "north_beach_scraps_10" : base_id + 1509, # (X=-88423.430 Y=-135922.969 Z=7290.801)
    "north_beach_scraps_11" : base_id + 1510, # (X=-87668.977 Y=-136850.359 Z=7275.346)
    "north_beach_scraps_12" : base_id + 1511, # (X=-90241.328 Y=-136381.000 Z=7199.622)
    "north_beach_scraps_13" : base_id + 1512, # (X=-91728.680 Y=-135288.203 Z=7319.699)
    "north_beach_scraps_14" : base_id + 1513, # (X=-88789.039 Y=-135461.719 Z=7305.800)
    "north_beach_scraps_15" : base_id + 1514, # (X=-88572.078 Y=-135970.734 Z=7302.674)
    "north_beach_paint_can_teal" : base_id + 1515 # (X=-91706.805 Y=-134988.453 Z=7347.827) Existing match 5
}

loc_mine_shaft = {
    "mine_shaft_chest_scraps_1" : base_id + 1516, # (X=-17360.789 Y=-74064.367 Z=8038.313)
    "mine_shaft_chest_scraps_2" : base_id + 1517, # (X=-17360.814 Y=-74064.367 Z=8024.187)
    "mine_shaft_chest_scraps_3" : base_id + 1518, # (X=-17361.059 Y=-74049.234 Z=8015.940)
    "mine_shaft_chest_scraps_4" : base_id + 1519, # (X=-17336.465 Y=-74087.063 Z=8009.707)
    "mine_shaft_chest_scraps_5" : base_id + 1520, # (X=-17349.941 Y=-74075.484 Z=8004.179)
    "mine_shaft_chest_scraps_6" : base_id + 1521, # (X=-17361.084 Y=-74049.234 Z=8001.814)
    "mine_shaft_chest_scraps_7" : base_id + 1522, # (X=-17349.967 Y=-74075.484 Z=7990.054)
    "mine_shaft_scraps_1" : base_id + 1523, # (X=-16985.645 Y=-70377.273 Z=10837.127)
    "mine_shaft_scraps_2" : base_id + 1524, # (X=-18292.045 Y=-71003.563 Z=10975.308)
    "mine_shaft_scraps_3" : base_id + 1525, # (X=-16150.797 Y=-72075.289 Z=10609.141)
    "mine_shaft_scraps_4" : base_id + 1526, # (X=-18404.480 Y=-71894.367 Z=10968.230)
    "mine_shaft_scraps_5" : base_id + 1527, # (X=-17777.268 Y=-71467.172 Z=10441.745)
    "mine_shaft_scraps_6" : base_id + 1528, # (X=-17630.971 Y=-72800.641 Z=8842.322)
    "mine_shaft_scraps_7" : base_id + 1529, # (X=-17979.719 Y=-73413.563 Z=8118.260)
    "mine_shaft_scraps_8" : base_id + 1530, # (X=-16554.467 Y=-74139.781 Z=7892.738)
    "mine_shaft_scraps_9" : base_id + 1531, # (X=-16343.033 Y=-74617.555 Z=7298.177)
    "mine_shaft_scraps_10" : base_id + 1532, # (X=-12390.332 Y=-77620.320 Z=7324.504)
    "mine_shaft_scraps_11" : base_id + 1533, # (X=-10969.702 Y=-77961.477 Z=7297.171)
    "mine_shaft_scraps_12" : base_id + 1534, # (X=-9888.596 Y=-78208.930 Z=7269.473)
    "mine_shaft_scraps_13" : base_id + 1535, # (X=-8865.696 Y=-79063.977 Z=7247.677)
    "mine_shaft_scraps_14" : base_id + 1536 # (X=-8143.984 Y=-79764.617 Z=7222.096)
}

loc_mob_camp = {
    "mob_camp_key" : base_id + 1537, # (X=-29114.480 Y=-53608.520 Z=12839.528)
    "mob_camp_scraps_1" : base_id + 1538, # (X=-27373.525 Y=-53008.668 Z=12706.465)
    "mob_camp_scraps_2" : base_id + 1539, # (X=-28786.941 Y=-53009.762 Z=12760.727)
    "mob_camp_scraps_3" : base_id + 1540, # (X=-29650.207 Y=-53328.070 Z=12724.598)
    "mob_camp_scraps_4" : base_id + 1541, # (X=-31515.057 Y=-55533.324 Z=12344.274)
    "mob_camp_scraps_5" : base_id + 1542, # (X=-31847.229 Y=-55152.352 Z=11574.255)
    "mob_camp_scraps_6" : base_id + 1543, # (X=-31323.533 Y=-55432.871 Z=11245.139)
    "mob_camp_scraps_7" : base_id + 1544, # (X=-31583.443 Y=-55475.805 Z=11234.112)
    "mob_camp_scraps_8" : base_id + 1545, # (X=-32925.406 Y=-57157.605 Z=11086.322)
    "mob_camp_scraps_9" : base_id + 1546, # (X=-33052.488 Y=-58560.098 Z=11101.021)
    "mob_camp_scraps_10" : base_id + 1547, # (X=-32422.406 Y=-60145.063 Z=11203.182)
    "mob_camp_scraps_11" : base_id + 1548, # (X=-30891.457 Y=-60046.465 Z=11237.567)
    "mob_camp_scraps_12" : base_id + 1549, # (X=-31888.428 Y=-59222.645 Z=11179.302)
    "mob_camp_scraps_13" : base_id + 1550, # (X=-31161.750 Y=-57410.789 Z=11279.820)
    "mob_camp_scraps_14" : base_id + 1551, # (X=-31256.545 Y=-59865.809 Z=11904.155)
    "mob_camp_scraps_15" : base_id + 1552, # (X=-31757.953 Y=-57179.258 Z=11295.150)
    "mob_camp_scraps_16" : base_id + 1553, # (X=-29137.043 Y=-54824.797 Z=12418.673)
    "mob_camp_scraps_17" : base_id + 1554, # (X=-31736.459 Y=-59761.465 Z=11211.379)
    "mob_camp_scraps_18" : base_id + 1555, # (X=-32150.889 Y=-59879.594 Z=11297.058)
    "mob_camp_stolen_bob" : base_id + 1556 # (X=-31771.172 Y=-59892.449 Z=11323.562)
}

loc_mine_elevator_exit = {
    "mine_elevator_exit_scraps_1" : base_id + 1557, # (X=-29587.271 Y=-42650.797 Z=12515.042)
    "mine_elevator_exit_scraps_2" : base_id + 1558, # (X=-30727.555 Y=-42715.438 Z=12485.763)
    "mine_elevator_exit_scraps_3" : base_id + 1559, # (X=-29814.680 Y=-43722.777 Z=12518.878)
    "mine_elevator_exit_scraps_4" : base_id + 1560, # (X=-30983.000 Y=-42943.754 Z=12474.396)
    "mine_elevator_exit_scraps_5" : base_id + 1561, # (X=-31824.576 Y=-43997.270 Z=12345.908)
    "mine_elevator_exit_scraps_6" : base_id + 1562, # (X=-32553.924 Y=-44761.855 Z=12341.698)
    "mine_elevator_exit_scraps_7" : base_id + 1563, # (X=-33598.023 Y=-44369.297 Z=12438.430)
    "mine_elevator_exit_scraps_8" : base_id + 1564, # (X=-31947.459 Y=-42017.137 Z=12384.311)
    "mine_elevator_exit_scraps_9" : base_id + 1565 # (X=-30127.123 Y=-46004.891 Z=12229.104)
}

loc_mountain_ruin_outside = {
    "mountain_ruin_outside_scraps_1" : base_id + 1566, # (X=-2218.456 Y=-43914.789 Z=11238.952)
    "mountain_ruin_outside_scraps_2" : base_id + 1567, # (X=-2402.206 Y=-45494.766 Z=11244.650)
    "mountain_ruin_outside_scraps_3" : base_id + 1568, # (X=-2781.385 Y=-47365.313 Z=11235.389)
    "mountain_ruin_outside_scraps_4" : base_id + 1569, # (X=-2961.431 Y=-45445.973 Z=11255.289)
    "mountain_ruin_outside_scraps_5" : base_id + 1570, # (X=-5873.435 Y=-46300.633 Z=11228.667)
    "mountain_ruin_outside_scraps_6" : base_id + 1571, # (X=-1823.357 Y=-47071.813 Z=11161.523)
    "mountain_ruin_outside_scraps_7" : base_id + 1572, # (X=-3478.155 Y=-49094.965 Z=11083.230)
    "mountain_ruin_outside_scraps_8" : base_id + 1573, # (X=-4606.678 Y=-50246.180 Z=11613.938)
    "mountain_ruin_outside_scraps_9" : base_id + 1574, # (X=-5454.638 Y=-53508.004 Z=12062.944)
    "mountain_ruin_outside_scraps_10" : base_id + 1575, # (X=-8192.042 Y=-53726.535 Z=11947.394)
    "mountain_ruin_outside_scraps_11" : base_id + 1576, # (X=-9409.834 Y=-53970.621 Z=11923.256)
    "mountain_ruin_outside_scraps_12" : base_id + 1577, # (X=-8977.424 Y=-57134.637 Z=12232.596)
    "mountain_ruin_outside_scraps_13" : base_id + 1578, # (X=-10449.292 Y=-56481.938 Z=12274.706)
    "mountain_ruin_outside_scraps_14" : base_id + 1579, # (X=-10490.690 Y=-56584.301 Z=12281.096)
    "mountain_ruin_outside_scraps_15" : base_id + 1580, # (X=-11600.937 Y=-55831.191 Z=12388.329)
    "mountain_ruin_outside_scraps_16" : base_id + 1581, # (X=-3307.077 Y=-49973.461 Z=11282.041)
    "mountain_ruin_outside_scraps_17" : base_id + 1582 # (X=-8878.345 Y=-49816.922 Z=13700.768)
}

loc_mountain_ruin_inside = {
    "mountain_ruin_inside_scraps_1" : base_id + 1583, # (X=-10647.446 Y=-52039.848 Z=11925.344)
    "mountain_ruin_inside_scraps_2" : base_id + 1584, # (X=-12834.990 Y=-48683.176 Z=10200.083)
    "mountain_ruin_inside_scraps_3" : base_id + 1585, # (X=-15748.594 Y=-44925.523 Z=10199.975)
    "mountain_ruin_inside_scraps_4" : base_id + 1586, # (X=-15312.152 Y=-43957.055 Z=10350.783)
    "mountain_ruin_inside_scraps_5" : base_id + 1587, # (X=-16709.586 Y=-44997.316 Z=10198.888)
    "mountain_ruin_inside_scraps_6" : base_id + 1588, # (X=-17412.561 Y=-46041.977 Z=10349.650)
    "mountain_ruin_inside_scraps_7" : base_id + 1589, # (X=-17452.596 Y=-43804.941 Z=10201.436)
    "mountain_ruin_inside_scraps_8" : base_id + 1590, # (X=-18119.473 Y=-42001.453 Z=10198.855)
    "mountain_ruin_inside_scraps_9" : base_id + 1591, # (X=-18975.068 Y=-42906.488 Z=10279.690)
    "mountain_ruin_inside_scraps_10" : base_id + 1592, # (X=-19727.902 Y=-41581.039 Z=10199.614)
    "mountain_ruin_inside_scraps_11" : base_id + 1593, # (X=-19187.891 Y=-40516.941 Z=10201.049)
    "mountain_ruin_inside_scraps_12" : base_id + 1594, # (X=-22470.986 Y=-41602.875 Z=10073.847)
    "mountain_ruin_inside_scraps_13" : base_id + 1595, # (X=-23717.383 Y=-42597.141 Z=7455.452)
    "mountain_ruin_inside_scraps_14" : base_id + 1596, # (X=-24494.582 Y=-44598.086 Z=7433.633)
    "mountain_ruin_inside_scraps_15" : base_id + 1597, # (X=-26783.293 Y=-42331.145 Z=7446.357)
    "mountain_ruin_inside_scraps_16" : base_id + 1598, # (X=-28636.996 Y=-46745.340 Z=7430.463)
    "mountain_ruin_inside_scraps_17" : base_id + 1599, # (X=-27752.643 Y=-47453.973 Z=7445.047)
    "mountain_ruin_inside_red_egg" : base_id + 1600, # (X=-28254.400 Y=-45702.844 Z=7551.568)
    "mountain_ruin_inside_paint_can_red" : base_id + 1601 # (X=-31391.293 Y=-44953.223 Z=7448.648) Existing match 5
}

loc_field_pickle_lady_mission = {
    "field_pickle_lady_scraps_1" : base_id + 1602, # (X=60402.582 Y=25252.434 Z=11151.982)
    "field_pickle_lady_scraps_2" : base_id + 1603, # (X=58717.516 Y=24457.180 Z=11343.938)
    "field_pickle_lady_scraps_3" : base_id + 1604, # (X=56455.688 Y=22324.875 Z=11655.192)
    "field_pickle_lady_scraps_4" : base_id + 1605, # (X=52888.387 Y=22541.955 Z=12428.012)
    "field_pickle_lady_scraps_5" : base_id + 1606, # (X=50374.863 Y=22073.027 Z=12591.468)
    "field_pickle_lady_scraps_6" : base_id + 1607, # (X=45985.988 Y=23063.826 Z=13043.497)
    "field_pickle_lady_scraps_7" : base_id + 1608, # (X=45533.469 Y=24876.168 Z=13015.539)
    "field_pickle_lady_scraps_8" : base_id + 1609, # (X=44928.848 Y=30913.396 Z=14273.230)
    "field_pickle_lady_scraps_9" : base_id + 1610, # (X=41572.684 Y=37403.539 Z=13527.379)
    "field_pickle_lady_scraps_10" : base_id + 1611, # (X=42266.566 Y=30556.238 Z=13584.196)
    "field_pickle_lady_scraps_11" : base_id + 1612, # (X=43356.219 Y=29465.746 Z=13449.486)
    "field_pickle_lady_scraps_12" : base_id + 1613, # (X=40893.461 Y=30669.398 Z=13465.039)
    "field_pickle_lady_scraps_13" : base_id + 1614, # (X=41276.863 Y=32313.068 Z=13480.846)
    "field_pickle_lady_scraps_14" : base_id + 1615, # (X=38630.031 Y=30471.996 Z=13571.207)
    "field_pickle_lady_scraps_15" : base_id + 1616, # (X=38596.938 Y=30050.293 Z=13559.574)
    "field_pickle_lady_scraps_16" : base_id + 1617, # (X=42042.520 Y=25136.820 Z=13077.339)
    "field_pickle_lady_scraps_17" : base_id + 1618, # (X=43770.914 Y=23307.234 Z=12374.002)
    "field_pickle_lady_scraps_18" : base_id + 1619, # (X=44672.641 Y=20936.520 Z=12198.017)
    "field_pickle_lady_scraps_19" : base_id + 1620, # (X=42844.730 Y=22869.387 Z=12832.900)
    "field_pickle_lady_scraps_20" : base_id + 1621, # (X=43397.758 Y=26367.248 Z=13005.097)
    "field_pickle_lady_scraps_21" : base_id + 1622, # (X=39352.430 Y=32668.316 Z=14494.778)
    "field_pickle_lady_paint_can_purple" : base_id + 1623, # (X=40394.855 Y=31546.465 Z=13472.573)
    "field_pickle_lady_jar_of_pickles" : base_id + 1624, # (X=38227.535 Y=30234.848 Z=13593.506)
    "field_pickle_lady_mission_end" : base_id + 1625,
    "field_pickle_lady_scraps_22" : base_id + 1626, # (X=59688.781 Y=25266.756 Z=11425.324)
    "field_pickle_lady_scraps_23" : base_id + 1627 # (X=59197.871 Y=24760.773 Z=11425.324)
}

loc_shrine_near_temple = {
    "shrine_near_temple_scraps_1" : base_id + 1628, # (X=-4675.183 Y=-21143.846 Z=11984.782)
    "shrine_near_temple_scraps_2" : base_id + 1629, # (X=-4994.117 Y=-20496.621 Z=11874.112)
    "shrine_near_temple_scraps_3" : base_id + 1630 # (X=-4196.896 Y=-20477.025 Z=11882.833)
}

loc_morse_bunker = {
    "morse_bunker_chest_scraps_1" : base_id + 1631, # (X=-47961.078 Y=-85433.031 Z=10615.777)
    "morse_bunker_chest_scraps_2" : base_id + 1632, # (X=-47958.617 Y=-85444.805 Z=10604.365)
    "morse_bunker_chest_scraps_3" : base_id + 1633, # (X=-47953.637 Y=-85426.172 Z=10592.347)
    "morse_bunker_chest_scraps_4" : base_id + 1634, # (X=-47958.691 Y=-85444.805 Z=10587.060)
    "morse_bunker_chest_scraps_5" : base_id + 1635, # (X=-47953.617 Y=-85426.172 Z=10574.149)
    "morse_bunker_scraps_1" : base_id + 1636, # (X=-48336.863 Y=-85458.453 Z=10574.537)
    "morse_bunker_scraps_2" : base_id + 1637, # (X=-48253.844 Y=-84944.609 Z=10573.793)
    "morse_bunker_scraps_3" : base_id + 1638, # (X=-47272.422 Y=-84549.945 Z=10543.671)
    "morse_bunker_scraps_4" : base_id + 1639, # (X=-47080.836 Y=-85268.281 Z=10564.355)
    "morse_bunker_scraps_5" : base_id + 1640, # (X=-47913.855 Y=-85234.258 Z=10819.314)
    "morse_bunker_scraps_6" : base_id + 1641, # (X=-46410.227 Y=-83293.742 Z=10361.746)
    "morse_bunker_scraps_7" : base_id + 1642, # (X=-45204.199 Y=-84841.211 Z=10329.200)
    "morse_bunker_scraps_8" : base_id + 1643, # (X=-43895.801 Y=-83794.750 Z=10265.661)
    "morse_bunker_scraps_9" : base_id + 1644, # (X=-45163.078 Y=-80832.828 Z=10090.777)
    "morse_bunker_scraps_10" : base_id + 1645, # (X=-46782.027 Y=-82284.805 Z=10289.180)
    "morse_bunker_scraps_11" : base_id + 1646, # (X=-49240.047 Y=-83654.961 Z=10898.540)
    "morse_bunker_scraps_12" : base_id + 1647, # (X=-46571.930 Y=-85962.773 Z=10697.339)
    "morse_bunker_scraps_13" : base_id + 1648, # (X=-43472.793 Y=-85983.805 Z=10310.322)
}

loc_prism_temple = {
    "prism_temple_chest_scraps_1" : base_id + 1649, # (X=12659.641 Y=-27827.016 Z=10930.621)
    "prism_temple_chest_scraps_2" : base_id + 1650, # (X=12648.021 Y=-27825.189 Z=10916.296)
    "prism_temple_chest_scraps_3" : base_id + 1651, # (X=12665.557 Y=-27836.633 Z=10905.999)
    "prism_temple_scraps_1" : base_id + 1652, # (X=5281.087 Y=-16620.387 Z=10520.609)
    "prism_temple_scraps_2" : base_id + 1653, # (X=15032.147 Y=-16788.352 Z=10992.200)
    "prism_temple_scraps_3" : base_id + 1654, # (X=16591.920 Y=-18725.771 Z=11004.751)
    "prism_temple_scraps_4" : base_id + 1655, # (X=17940.854 Y=-20726.746 Z=10999.944)
    "prism_temple_scraps_5" : base_id + 1656, # (X=18187.346 Y=-21390.066 Z=11025.650)
    "prism_temple_scraps_6" : base_id + 1657, # (X=19218.670 Y=-24017.619 Z=10906.966)
    "prism_temple_scraps_7" : base_id + 1658, # (X=7710.977 Y=-23469.254 Z=11012.888)
    "prism_temple_scraps_8" : base_id + 1659, # (X=8160.002 Y=-22335.266 Z=11016.638)
    "prism_temple_scraps_9" : base_id + 1660, # (X=8637.903 Y=-24295.850 Z=10929.299)
    "prism_temple_scraps_10" : base_id + 1661, # (X=7923.367 Y=-25204.055 Z=10832.877)
    "prism_temple_scraps_11" : base_id + 1662, # (X=10694.420 Y=-27246.365 Z=10569.074)
    "prism_temple_scraps_12" : base_id + 1663, # (X=12892.631 Y=-26743.068 Z=10868.578)
    "prism_temple_scraps_13" : base_id + 1664, # (X=12483.535 Y=-27253.867 Z=10876.461)
    "prism_temple_scraps_14" : base_id + 1665, # (X=13259.813 Y=-27092.033 Z=10887.968)
    "prism_temple_scraps_15" : base_id + 1666, # (X=9303.245 Y=-25057.908 Z=10943.273)
    "prism_temple_scraps_16" : base_id + 1667, # (X=11750.875 Y=-22999.371 Z=12426.734)
    "prism_temple_scraps_17" : base_id + 1668, # (X=12966.615 Y=-23568.324 Z=12519.387)
    "prism_temple_scraps_18" : base_id + 1669, # (X=14093.343 Y=-22393.182 Z=12426.847)
    "prism_temple_scraps_19" : base_id + 1670, # (X=13767.980 Y=-21269.568 Z=12425.791)
    "prism_temple_scraps_20" : base_id + 1671, # (X=12882.754 Y=-20027.527 Z=12516.095)
    "prism_temple_scraps_21" : base_id + 1672, # (X=11883.399 Y=-20801.344 Z=12428.452)
    "prism_temple_scraps_22" : base_id + 1673, # (X=13281.792 Y=-21302.344 Z=12902.728)
    "prism_temple_scraps_23" : base_id + 1674, # (X=14190.678 Y=-23671.621 Z=11781.533)
    "prism_temple_scraps_24" : base_id + 1675, # (X=14311.736 Y=-22347.758 Z=11765.781)
    "prism_temple_scraps_25" : base_id + 1676, # (X=13826.154 Y=-19923.131 Z=11755.189)
    "prism_temple_scraps_26" : base_id + 1677, # (X=12443.228 Y=-18577.926 Z=11240.455)
    "prism_temple_scraps_27" : base_id + 1678, # (X=10993.180 Y=-23783.047 Z=11754.121)
    "prism_temple_scraps_28" : base_id + 1679, # (X=16762.963 Y=-23634.342 Z=11031.588)
    "prism_temple_scraps_29" : base_id + 1680, # (X=17804.979 Y=-23512.395 Z=11066.884)
    "prism_temple_scraps_30" : base_id + 1681, # (X=16998.229 Y=-23241.652 Z=11055.539)
    "prism_temple_scraps_31" : base_id + 1682, # (X=17613.518 Y=-23799.813 Z=11057.277)
    "prism_temple_scraps_32" : base_id + 1683, # (X=15342.375 Y=-24807.357 Z=11024.192)
    "prism_temple_scraps_33" : base_id + 1684, # (X=15963.284 Y=-24834.156 Z=11021.444)
    "prism_temple_scraps_34" : base_id + 1685 # (X=21563.559 Y=-23705.184 Z=10895.696)
}


## All locations
location_table: dict[str, int] = {
    **loc_start_camp,
    **loc_tony_tiddle_mission,
    **loc_tutorial_candice_mission,
    **loc_swamp,
    **loc_lizbeth_murkwater_mission,
    **loc_daryl_mission,
    **loc_south_house,
    **loc_helen_mission,
    **loc_sgt_flint_mission,
    **loc_south_mine_outside,
    **loc_south_mine_inside,
    **loc_theodore_mission,
    **loc_canyon_theodore,
    **loc_watchtower,
    **loc_boulder_field,
    **loc_house_sasha_mission,
    **loc_house_santiago,
    **loc_port_santiago_mission,
    **loc_trench_house,
    **loc_doll_woods,
    **loc_lost_stairs,
    **loc_east_house,
    **loc_explosive_training,
    **loc_john_smith_mission,
    **loc_greg_mission,
    **loc_claire_mission,
    **loc_north_mine_outside,
    **loc_north_mine_inside,
    **loc_wood_bridge,
    **loc_paul_mission,
    **loc_gertrude_mission,
    **loc_west_beach,
    **loc_church,
    **loc_refuge_gale_mission,
    **loc_caravan,
    **loc_trailer_house,
    **loc_ronny_mission,
    **loc_north_beach,
    **loc_mine_shaft,
    **loc_mob_camp,
    **loc_mine_elevator_exit,
    **loc_mountain_ruin_outside,
    **loc_mountain_ruin_inside,
    **loc_prism_temple,
    **loc_field_pickle_lady_mission,
    **loc_shrine_near_temple,
    **loc_morse_bunker
}
