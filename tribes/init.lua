-- Tribes initialization

set_textdomain("tribes")

-- ===================================
--    Wares
-- ===================================

include "tribes/wares/armor/init.lua"
include "tribes/wares/armor_chain/init.lua"
include "tribes/wares/armor_gilded/init.lua"
include "tribes/wares/armor_helmet/init.lua"
include "tribes/wares/ax/init.lua"
include "tribes/wares/ax_battle/init.lua"
include "tribes/wares/ax_broad/init.lua"
include "tribes/wares/ax_bronze/init.lua"
include "tribes/wares/ax_sharp/init.lua"
include "tribes/wares/ax_warriors/init.lua"
include "tribes/wares/basket/init.lua"
include "tribes/wares/beer/init.lua"
include "tribes/wares/blackroot/init.lua"
include "tribes/wares/blackroot_flour/init.lua"
include "tribes/wares/blackwood/init.lua"
include "tribes/wares/bread_atlanteans/init.lua"
include "tribes/wares/bread_barbarians/init.lua"
include "tribes/wares/bread_empire/init.lua"
include "tribes/wares/bread_paddle/init.lua"
include "tribes/wares/buckets/init.lua"
include "tribes/wares/cloth/init.lua"
include "tribes/wares/coal/init.lua"
include "tribes/wares/corn/init.lua"
include "tribes/wares/cornmeal/init.lua"
include "tribes/wares/diamond/init.lua"
include "tribes/wares/felling_ax/init.lua"
include "tribes/wares/fire_tongs/init.lua"
include "tribes/wares/fish/init.lua"
include "tribes/wares/fishing_net/init.lua"
include "tribes/wares/fishing_rod/init.lua"
include "tribes/wares/flour/init.lua"
include "tribes/wares/gold/init.lua"
include "tribes/wares/gold_ore/init.lua"
include "tribes/wares/gold_thread/init.lua"
include "tribes/wares/granite/init.lua"
include "tribes/wares/grape/init.lua"
include "tribes/wares/grout/init.lua"
include "tribes/wares/hammer/init.lua"
include "tribes/wares/helmet/init.lua"
include "tribes/wares/helmet_mask/init.lua"
include "tribes/wares/helmet_warhelm/init.lua"
include "tribes/wares/hook_pole/init.lua"
include "tribes/wares/hunting_bow/init.lua"
include "tribes/wares/hunting_spear/init.lua"
include "tribes/wares/iron/init.lua"
include "tribes/wares/iron_ore/init.lua"
include "tribes/wares/kitchen_tools/init.lua"
include "tribes/wares/log/init.lua"
include "tribes/wares/marble/init.lua"
include "tribes/wares/marble_column/init.lua"
include "tribes/wares/meal/init.lua"
include "tribes/wares/meat/init.lua"
include "tribes/wares/milking_tongs/init.lua"
include "tribes/wares/pick/init.lua"
include "tribes/wares/planks/init.lua"
include "tribes/wares/quartz/init.lua"
include "tribes/wares/ration/init.lua"
include "tribes/wares/saw/init.lua"
include "tribes/wares/scythe/init.lua"
include "tribes/wares/shield_advanced/init.lua"
include "tribes/wares/shield_steel/init.lua"
include "tribes/wares/shovel/init.lua"
include "tribes/wares/smoked_fish/init.lua"
include "tribes/wares/smoked_meat/init.lua"
include "tribes/wares/snack/init.lua"
include "tribes/wares/spear/init.lua"
include "tribes/wares/spear_advanced/init.lua"
include "tribes/wares/spear_heavy/init.lua"
include "tribes/wares/spear_war/init.lua"
include "tribes/wares/spear_wooden/init.lua"
include "tribes/wares/spidercloth/init.lua"
include "tribes/wares/spider_silk/init.lua"
include "tribes/wares/stout/init.lua"
include "tribes/wares/tabard/init.lua"
include "tribes/wares/tabard_golden/init.lua"
include "tribes/wares/thatch_reed/init.lua"
include "tribes/wares/trident_double/init.lua"
include "tribes/wares/trident_heavy_double/init.lua"
include "tribes/wares/trident_light/init.lua"
include "tribes/wares/trident_long/init.lua"
include "tribes/wares/trident_steel/init.lua"
include "tribes/wares/water/init.lua"
include "tribes/wares/wheat/init.lua"
include "tribes/wares/wine/init.lua"
include "tribes/wares/wool/init.lua"


-- ===================================
--    Workers, Carriers & Soldiers
-- ===================================

-- Adds 6 animations for each walking direction into 'table'. The pictures are
-- searched for in 'dirname'. All files should look like this
-- 'basename'_(e|ne|se|sw|w|nw)_\d+.png. 'hotspot' is the hotspot for blitting.
-- 'animationname' name of the animation, e.g. "walkload"
function add_worker_animations(table, animationname, dirname, basename, hotspot, fps)
   for idx, dir in ipairs{ "ne", "e", "se", "sw", "w", "nw" } do
      table[animationname] = {
         pictures = path.list_directory(dirname, basename .. "_" .. dir .. "_\\d+.png"),
         hotspot = hotspot,
         fps = fps,
      }
   end
end

include "tribes/workers/atlanteans/armorsmith/init.lua"
include "tribes/workers/atlanteans/baker/init.lua"
include "tribes/workers/atlanteans/blackroot_farmer/init.lua"
include "tribes/workers/atlanteans/builder/init.lua"
include "tribes/workers/atlanteans/carrier/init.lua"
include "tribes/workers/atlanteans/charcoal_burner/init.lua"
include "tribes/workers/atlanteans/farmer/init.lua"
include "tribes/workers/atlanteans/fishbreeder/init.lua"
include "tribes/workers/atlanteans/fisher/init.lua"
include "tribes/workers/atlanteans/forester/init.lua"
include "tribes/workers/atlanteans/geologist/init.lua"
include "tribes/workers/atlanteans/horse/init.lua"
include "tribes/workers/atlanteans/horsebreeder/init.lua"
include "tribes/workers/atlanteans/hunter/init.lua"
include "tribes/workers/atlanteans/miller/init.lua"
include "tribes/workers/atlanteans/sawyer/init.lua"
include "tribes/workers/atlanteans/scout/init.lua"
include "tribes/workers/atlanteans/shipwright/init.lua"
include "tribes/workers/atlanteans/smelter/init.lua"
include "tribes/workers/atlanteans/smoker/init.lua"
include "tribes/workers/atlanteans/soldier/init.lua"
include "tribes/workers/atlanteans/spiderbreeder/init.lua"
include "tribes/workers/atlanteans/stonecutter/init.lua"
include "tribes/workers/atlanteans/toolsmith/init.lua"
include "tribes/workers/atlanteans/trainer/init.lua"
include "tribes/workers/atlanteans/weaponsmith/init.lua"
include "tribes/workers/atlanteans/weaver/init.lua"
include "tribes/workers/atlanteans/woodcutter/init.lua"

include "tribes/workers/barbarians/baker/init.lua"
include "tribes/workers/barbarians/blacksmith/init.lua"
include "tribes/workers/barbarians/blacksmith_master/init.lua"
include "tribes/workers/barbarians/brewer/init.lua"
include "tribes/workers/barbarians/brewer_master/init.lua"
include "tribes/workers/barbarians/builder/init.lua"
include "tribes/workers/barbarians/carrier/init.lua"
include "tribes/workers/barbarians/cattlebreeder/init.lua"
include "tribes/workers/barbarians/charcoal_burner/init.lua"
include "tribes/workers/barbarians/farmer/init.lua"
include "tribes/workers/barbarians/fisher/init.lua"
include "tribes/workers/barbarians/gamekeeper/init.lua"
include "tribes/workers/barbarians/gardener/init.lua"
include "tribes/workers/barbarians/geologist/init.lua"
include "tribes/workers/barbarians/helmsmith/init.lua"
include "tribes/workers/barbarians/hunter/init.lua"
include "tribes/workers/barbarians/innkeeper/init.lua"
include "tribes/workers/barbarians/lime_burner/init.lua"
include "tribes/workers/barbarians/lumberjack/init.lua"
include "tribes/workers/barbarians/miner/init.lua"
include "tribes/workers/barbarians/miner_chief/init.lua"
include "tribes/workers/barbarians/miner_master/init.lua"
include "tribes/workers/barbarians/ox/init.lua"
include "tribes/workers/barbarians/ranger/init.lua"
include "tribes/workers/barbarians/scout/init.lua"
include "tribes/workers/barbarians/shipwright/init.lua"
include "tribes/workers/barbarians/smelter/init.lua"
include "tribes/workers/barbarians/soldier/init.lua"
include "tribes/workers/barbarians/stonemason/init.lua"
include "tribes/workers/barbarians/trainer/init.lua"
include "tribes/workers/barbarians/weaver/init.lua"


-- ===================================
--    Immovables
-- ===================================

include "tribes/immovables/ashes/init.lua"
include "tribes/immovables/blackrootfield_harvested/init.lua"
include "tribes/immovables/blackrootfield_medium/init.lua"
include "tribes/immovables/blackrootfield_ripe/init.lua"
include "tribes/immovables/blackrootfield_small/init.lua"
include "tribes/immovables/blackrootfield_tiny/init.lua"
include "tribes/immovables/cornfield_harvested/init.lua"
include "tribes/immovables/cornfield_medium/init.lua"
include "tribes/immovables/cornfield_ripe/init.lua"
include "tribes/immovables/cornfield_small/init.lua"
include "tribes/immovables/cornfield_tiny/init.lua"
include "tribes/immovables/destroyed_building/init.lua"
include "tribes/immovables/field_harvested/init.lua"
include "tribes/immovables/field_medium/init.lua"
include "tribes/immovables/field_ripe/init.lua"
include "tribes/immovables/field_small/init.lua"
include "tribes/immovables/field_tiny/init.lua"
include "tribes/immovables/grapevine_medium/init.lua"
include "tribes/immovables/grapevine_ripe/init.lua"
include "tribes/immovables/grapevine_small/init.lua"
include "tribes/immovables/grapevine_tiny/init.lua"
include "tribes/immovables/reed_medium/init.lua"
include "tribes/immovables/reed_ripe/init.lua"
include "tribes/immovables/reed_small/init.lua"
include "tribes/immovables/reed_tiny/init.lua"
include "tribes/immovables/resi_coal1/init.lua"
include "tribes/immovables/resi_coal2/init.lua"
include "tribes/immovables/resi_gold1/init.lua"
include "tribes/immovables/resi_gold2/init.lua"
include "tribes/immovables/resi_iron1/init.lua"
include "tribes/immovables/resi_iron2/init.lua"
include "tribes/immovables/resi_none/init.lua"
include "tribes/immovables/resi_stones1/init.lua"
include "tribes/immovables/resi_stones2/init.lua"
include "tribes/immovables/resi_water/init.lua"
include "tribes/immovables/shipconstruction_atlanteans/init.lua"
include "tribes/immovables/shipconstruction_barbarians/init.lua"
include "tribes/immovables/shipconstruction_empire/init.lua"
