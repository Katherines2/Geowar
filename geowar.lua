local direct_hits = 0
local hits = 0
local near_hits = 0

local field_size = 30
local num_enemies = 5

local enemy_angles = {}
local enemy_coordinates = {}


print("GEOWAR")
print("CREATIVE COMPUTING")
print("MORRISTOWN, NEW JERSEY")
print("\n\n")
print("Do you want a description of the game? ")
local a = io.read()
if a == "no" then
    return
else
    print("\n     THE FIRST QUADRANT OF A REGULAR COORDINATE GRAPH WILL")
    print(" SERVE AS")
    print("THE BATTLEFIELD.  FIVE ENEMY INSTALLATIONS ARE LOCATED")
    print(" WITHIN A")
    print("30 BY 30 UNIT AREA.  NO TARGET IS INSIDE THE 10 BY 10 ")
    print("UNIT AREA")
    print("ADJACENT TO THE ORIGIN, AS THIS IS THE LOCATION OF OUR ")
    print("BASE. WHEN")
    print("THE MACHINE ASKS FOR THE DEGREE OF THE SHOT, RESPOND ")
    print("WITH A NUMBER")
    print("BETWEEN 1 AND 90.")
    print("\n SCARE**********")
    print("    1. A DIRECT HIT IS A HIT WITHIN 1 DEGREE OF")
    print("*             *")
    print("        THE TARGET.", " " , "*  HIT******  *")
    print("    2. A HIT MUST PASS BETWEEN THE FIRST SET OF")
    print("*  *       *  *")
    print("         INTEGRAL POINTS NW AND SE OF THE TARGET.")
    print("*  *   D   *  *")
    print("    3. A SCARE MUST PASS BETWEEN THE NEXT SET OF")
    print("*  *       *  *")
    print("         INTEGRAL POINTS NW AND SE OF THE TARGET,")
    print("*  ******HIT  *")
    print("         AND CAUSES THE ENEMY TO RELOCATE A ")
    print("*             *")
    print("         MAXIMUM OF 1 UNIT IN ANY DIRECTION.")
    print("**********SCARE\n\n")
    print("\n MISSILES HAVE INFINITE RANGE AND MAY HIT MORE THAN ")
    print("ONE TARGET.")
    print("A MISSILE THAT NEARLY MISSES AN INSTALLATION (A SCARE) ")
    print("WILL BE")
    print("IMMEDIATELY SHOT DOWN.  ANY HITS BEFORE THIS TIME WILL ")
    print("NOT BE COUNTED")
    print("UNLESS A DIRECT HIT WAS MADE.\n\n")
    
end

::start::

print("Ready to go? \n\n")

local b = io.read()
if b == "no" then
    return
end

print("GOOD LUCK!\n\n")

local generate_enemy_coordinates = function ()

    for i = 1,  num_enemies do
        
        local x = math.random(11, field_size - 1)
        local y = math.random(11, field_size - 1)
        enemy_coordinates[i] = {x, y}


    end

end

local calculate_angles = function ()

    for i = 1, #enemy_coordinates do
    
        local x = enemy_coordinates[i][1]
        local y = enemy_coordinates[i][2]
        enemy_angles[i] = math.ceil(math.deg(math.atan2(y, x)))
    end
    
end

generate_enemy_coordinates()
calculate_angles()
local is_hit = function (degree)

    local func_direct = 0
    local func_hits = 0
    local func_near = 0
    local func_miss = 0
    
    for i = 1 , #enemy_coordinates do
      print(i, enemy_angles[i])
      if enemy_coordinates[i] == nil then break end
        local diff = math.abs(enemy_angles[i] - degree)
        if diff == 0 then
            
            direct_hits = direct_hits + 1
            table.remove(enemy_coordinates, i)
            table.remove(enemy_angles, i)
            
            func_direct = func_direct + 1
                
            
        end

        if diff == 1 then

            hits = hits + 1
            table.remove(enemy_coordinates, i)
            table.remove(enemy_angles, i)
            
            func_hits = func_hits + 1
        end

        if diff == 2 then

            near_hits = near_hits + 1

            if math.random(0, 1) < 0.5 then 

                enemy_coordinates[i][1] = enemy_coordinates[i][1] + (math.random(0, 1) < 0.5 and -1 or 1)
            else
                enemy_coordinates[i][2] = enemy_coordinates[i][2] + (math.random(0, 1) < 0.5 and -1 or 1)

            end
            
            func_near = func_near + 1
        end
        
        func_miss = func_miss + 1
    end
    print("Direct Hits : ", func_direct, ", Hits : ", func_hits, ", Scare : ", func_near, ", Missed : ", func_miss)
end

local degree = 0

while (#enemy_coordinates > 0 and degree) do
    
    degree = tonumber(io.read("n"))
    is_hit(degree)


end

print( "Results : ", direct_hits, hits, near_hits, "\n\n")

print("Want to play again???")

local c = io.read()
if c == "no" then
    return
else
    goto start
end


