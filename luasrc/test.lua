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
    print("100 dead all")
--    ailib.check_monster_num(raid, 101, 0)
--    print("101 dead all")
end

raid = ailib.create_raid(raid_func_1)


while (true) do
    local r = coroutine.resume(raid.handle, raid)
    if (not r) then
	break
    end
    r = ailib.del_monster(raid, 100, 0)
--    local r2 = ailib.get_monster_num(raid, 100)
--    print("r2 = ", r2, "r = ", r)
end




