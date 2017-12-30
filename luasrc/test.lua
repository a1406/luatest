require "ailib"

function raid_func_1(raid)
    ailib.add_monster(raid, 100, 10001)
    ailib.add_monster(raid, 100, 10002)
    ailib.add_monster(raid, 100, 10003)
    ailib.add_monster(raid, 101, 10004)
    ailib.add_monster(raid, 101, 10005)
    ailib.add_monster(raid, 101, 10006)
    ailib.add_monster(raid, 101, 10007)
    ailib.add_monster(raid, 101, 10008)
    ailib.check_monster_num(raid, 100, 0)
end

raid = ailib.create_raid(raid_func_1)
coroutine.resume(raid.handle, raid)
local r1 = ailib.get_monster_num(raid, 100)
local r = ailib.del_monster(raid, 100, 0)
local r2 = ailib.get_monster_num(raid, 100)
print("r1 = ", r1, "r2 = ", r2, "r = ", r)

