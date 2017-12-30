ailib = {}
function ailib.get_monster_num(raid, monster_id)
    local ret = 0
    for i,v in pairs(raid.all_monster) do
	if v.id == monster_id then
	    ret = ret + 1
	end    
    end
    return ret
end

function ailib.check_monster_num(raid, monster_id, monster_num)
    print("enter check monster raid = ", raid)
    while (true) do
	local num = ailib.get_monster_num(raid, monster_id)
	print("num = ", num)
	if (num <= monster_num) then
	    print("finish check monster num")
	    return 0	
	end
	coroutine.yield()
    end
    print("bug, you should not be here")
end

all_raid = {}
function ailib.create_raid(raid_func)
    raid = {}
    raid.handle = coroutine.create(raid_func)
    raid.all_monster = {}
    table.insert(all_raid, raid)
    return raid
end

function ailib.add_monster(raid, monster_id, uuid)
    monster = {}
    monster.id = monster_id
    monster.uuid = uuid
    raid.all_monster[uuid] = monster
end
function ailib.del_monster(raid, monster_id, uuid)
    if (uuid ~= 0) then
	raid.all_monster[uuid] = nil
	return 0
    end
    
    for i,v in pairs(raid.all_monster) do
	if v.id == monster_id then
	    raid.all_monster[v.uuid] = nil
	    return 0
	end    
    end
    return -1
end
return ailib
