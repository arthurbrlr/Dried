
plain = {biomeName = "plain", biomeID = 1, 
         offsetX = 10, offsetZ = 150, 
         frequencyX = 100, frequencyZ = 100, 
         heightOffset = 0, multiplier = 6, 
         preprocessing = 2, topBlockID = 1, underBlockID = 2}

desert = {biomeName = "desert", biomeID = 2, 
          offsetX = 40, offsetZ = -20, 
          frequencyX = 80, frequencyZ = 70, 
          heightOffset = 5, multiplier = 9, 
          preprocessing = 1, topBlockID = 5, underBlockID = 5}


ocean = {biomeName = "ocean", biomeID = 3,
         offsetX = 380, offsetZ = - 2000,
         frequencyX = 30, frequencyZ = 30,
         heightOffset = -10, multiplier = -20,
         preprocessing = 2, topBlockID = 2, underBlockID = 2}

mountain = {biomeName = "mountain", biomeID = 4,
            offsetX = 380, offsetZ = - 2000,
            frequencyX = 30, frequencyZ = 30,
            heightOffset = -10, multiplier = -20,
            preprocessing = 1, topBlockID = 3, underBlockID = 3}

biomes = {plain, desert, ocean, mountain}

function GetBiomeNumber ()
    c = 0
    for Index, Value in pairs(biomes) do
        c = c + 1
    end

    return c
end

function GetBiome (n)
    return biomes[n]
end